#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <cstdint>
#include <numeric>
#include <algorithm>
#include <sstream>

class PopulationObserver;
#include "Exceptions.hpp"

class Continent {
public:
    struct Country {
        std::string   name;
        std::uint64_t population;
        double        area;
        double        gdp;
        double        life_quality;
        double        health_index;
        double        education_index;
        double        environment_index;

        double density() const { return population / area; }
    };

    static int get_total_continents();

    Continent(const Continent&) = default;
    Continent& operator=(const Continent&) = default;
    virtual ~Continent() = default;
    virtual std::unique_ptr<Continent> clone() const = 0;

    virtual std::string major_characteristic() const = 0;

    std::string describe() const;
    const std::string& name() const { return m_name_; }

    std::size_t   country_count()        const { return countries_.size(); }
    std::uint64_t total_population()     const;
    double        total_area()           const;
    double        population_density()   const;
    double        total_gdp()            const;
    double        average_life_quality() const;
    const Country& best_life_quality()   const;

    std::vector<Country> top_by_gdp(std::size_t n) const;
    std::vector<Country> top_by_qol(std::size_t n) const;

    const std::vector<Country>& countries() const { return countries_; }

    void add_country(Country c);
    void remove_country(std::string_view name);

    void add_observer(std::shared_ptr<PopulationObserver>);
    void remove_expired_observers();

protected:
    explicit Continent(std::string name, std::vector<Country> countries = {});

private:
    std::string                                        m_name_;
    std::vector<Country>                               countries_;
    inline static int                                  total_{0};
    std::vector<std::weak_ptr<PopulationObserver>>     observers_;

    static void validate_country(const Country&);
    void notify_population_change(std::uint64_t oldPop,
                                  std::uint64_t newPop) const;
};
