#include "ConsoleLogger.hpp"
#include "Continent.hpp"

void ConsoleLogger::notify(const Continent& c,
                            std::uint64_t oldPop,
                            std::uint64_t newPop) const {
    std::cout << "[LOG] Populatia continentului "
              << c.name()
              << " s-a schimbat: " << oldPop
              << " -> " << newPop << '\n';
}

std::unique_ptr<PopulationObserver> ConsoleLogger::clone() const {
    return std::make_unique<ConsoleLogger>(*this);
}

