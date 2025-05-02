#include "Continent.hpp"
#include "PopulationObserver.hpp"
#include <algorithm>
#include <numeric>
#include <sstream>

void Continent::validate_country(const Country& c) {
    if (c.population == 0)
        throw InvalidCountryData("Population zero: " + c.name);
    if (c.area <= 0.0)
        throw InvalidCountryData("Area <= 0: " + c.name);
    if (c.gdp < 0.0)
        throw InvalidCountryData("GDP negative: " + c.name);

    auto out_of_range = [](double v) { return v < 0.0 || v > 10.0; };
    if (out_of_range(c.life_quality))
        throw InvalidCountryData("Life quality out of range: " + c.name);
    if (out_of_range(c.health_index))
        throw InvalidCountryData("Health index out of range: " + c.name);
    if (out_of_range(c.education_index))
        throw InvalidCountryData("Education index out of range: " + c.name);
    if (out_of_range(c.environment_index))
        throw InvalidCountryData("Environment index out of range: " + c.name);
}


Continent::Continent(std::string name, std::vector<Country> countries)
    : m_name_{std::move(name)} {
    for (const auto& c : countries) validate_country(c);
    countries_ = std::move(countries);
    ++total_;
}

int Continent::get_total_continents() { return total_; }


std::uint64_t Continent::total_population() const {
    return std::accumulate(countries_.begin(), countries_.end(), 0ULL,
        [](auto acc, const Country& c) { return acc + c.population; });
}

double Continent::total_area() const {
    return std::accumulate(countries_.begin(), countries_.end(), 0.0,
        [](double acc, const Country& c) { return acc + c.area; });
}

double Continent::population_density() const {
    double area = total_area();
    return area ? total_population() / area : 0.0;
}

double Continent::total_gdp() const {
    return std::accumulate(countries_.begin(), countries_.end(), 0.0,
        [](double acc, const Country& c) { return acc + c.gdp; });
}

double Continent::average_life_quality() const {
    if (countries_.empty()) return 0.0;
    double sum = std::accumulate(countries_.begin(), countries_.end(), 0.0,
        [](double acc, const Country& c) { return acc + c.life_quality; });
    return sum / countries_.size();
}

const Continent::Country& Continent::best_life_quality() const {
    return *std::max_element(countries_.begin(), countries_.end(),
        [](const Country& a, const Country& b) { return a.life_quality < b.life_quality; });
}


void Continent::add_country(Country c) {
    validate_country(c);

    // verificare duplicat
    auto it = std::find_if(countries_.begin(), countries_.end(),
        [&](const Country& x) { return x.name == c.name; });
    if (it != countries_.end())
        throw CountryAlreadyExists("Country already exists: " + c.name);

    // calculeaza populatia veche, adauga tara, notifica
    std::uint64_t oldPop = total_population();
    countries_.push_back(std::move(c));
    notify_population_change(oldPop, total_population());
}


void Continent::remove_country(std::string_view name) {
    auto it = std::find_if(countries_.begin(), countries_.end(),
        [&](const Country& x) { return x.name == name; });
    if (it == countries_.end())
        throw CountryNotFound("Country not found: " + std::string{name});
    countries_.erase(it);
}

// Top N help
std::vector<Continent::Country> Continent::top_by_gdp(std::size_t n) const {
    if (n == 0 || countries_.empty()) return {};
    if (n > countries_.size()) n = countries_.size();
    std::vector<Country> copy = countries_;
    std::partial_sort(copy.begin(), copy.begin() + n, copy.end(),
        [](const Country& a, const Country& b) { return a.gdp > b.gdp; });
    copy.resize(n);
    return copy;
}

std::vector<Continent::Country> Continent::top_by_qol(std::size_t n) const {
    if (n == 0 || countries_.empty()) return {};
    if (n > countries_.size()) n = countries_.size();
    std::vector<Country> copy = countries_;
    std::partial_sort(copy.begin(), copy.begin() + n, copy.end(),
        [](const Country& a, const Country& b) { return a.life_quality > b.life_quality; });
    copy.resize(n);
    return copy;
}


std::string Continent::describe() const {
    std::ostringstream oss;
    oss << "Continentul " << m_name_
        << " | tari: " << country_count()
        << " | pop: " << total_population()
        << " | GDP: " << total_gdp() << " mld USD"
        << " | densitate: " << population_density() << " loc/km2"
        << " | " << major_characteristic();
    return oss.str();
}


void Continent::add_observer(std::shared_ptr<PopulationObserver> obs) {
    observers_.push_back(obs);
}

void Continent::remove_expired_observers() {
    auto end = std::remove_if(observers_.begin(), observers_.end(),
                [](const auto& wk){ return wk.expired(); });
    observers_.erase(end, observers_.end());
}

void Continent::notify_population_change(std::uint64_t oldPop,
                                         std::uint64_t newPop) const {
    for (const auto& wk : observers_) {
        if (auto sp = wk.lock()) {
            sp->notify(*this, oldPop, newPop);
        }
    }
}
