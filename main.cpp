#include <iostream>
#include <iomanip>
#include <memory>

#include "WorldMap.hpp"
#include "Europe.hpp"
#include "Asia.hpp"
#include "Africa.hpp"
#include "ConsoleLogger.hpp"          // observer concret

int main() {
    try {
        WorldMap earth;

        // ---- instantiem si atasam un observer unic pentru toate continentele
        auto logger = std::make_shared<ConsoleLogger>();

        auto eu = std::make_unique<Europe>();
        eu->add_observer(logger);

        auto as = std::make_unique<Asia>();
        as->add_observer(logger);

        auto af = std::make_unique<Africa>();
        af->add_observer(logger);

        earth.add(std::move(eu));
        earth.add(std::move(as));
        earth.add(std::move(af));

        // ---- overview initial
        earth.overview();

        // ---- top GDP Asia
        const Continent& asia = earth.at(1);
        std::cout << "\nTop 3 GDP in Asia:\n";
        for (const auto& c : asia.top_by_gdp(3))
            std::cout << "  " << c.name << " - " << c.gdp << " mld USD\n";

        // ---- top QoL Europe
        const Continent& europe = earth.at(0);
        std::cout << "\nTop 2 QoL in Europe:\n";
        for (const auto& c : europe.top_by_qol(2))
            std::cout << "  " << c.name << " - " << c.life_quality << '\n';

        // ---- demonstram Observer: adaugam si stergem tari
        Continent& eu_ref = const_cast<Continent&>(earth.at(0));
        eu_ref.add_country({ "Norway", 5400000, 385207, 480,
                             8.0, 8.6, 8.3, 8.1 });          // logger afiseaza schimbarea

        Continent& as_ref = const_cast<Continent&>(earth.at(1));
        as_ref.remove_country("Japan");                       // logger afiseaza schimbarea

        // ---- dynamic_cast cu sens
        const Continent& c0 = earth.at(0);
        if (auto ptr = dynamic_cast<const Europe*>(&c0))
            std::cout << "\nDowncast reusit: continentul 0 este Europa\n";

        // ---- recapitulare statistici
        std::cout << "\nPopulatia totala Asia: " << asia.total_population() << '\n';
        std::cout << "GDP total Europa: "      << europe.total_gdp()      << " mld USD\n";
        std::cout << "Media QoL Africa: "      << earth.at(2).average_life_quality() << '\n';

        std::cout << "\nTotal continente create: "
                  << Continent::get_total_continents() << '\n';
    }
    catch (const ContinentError& ex) {
        std::cerr << "Eroare tematica: " << ex.what() << '\n';
    }
    catch (const std::exception& ex) {
        std::cerr << "Eroare neasteptata: " << ex.what() << '\n';
    }
}
