#pragma once
#include "PopulationObserver.hpp"
#include <iostream>

class ConsoleLogger : public PopulationObserver {
public:
    void notify(const Continent& c,
                std::uint64_t oldPop,
                std::uint64_t newPop) const override;

    std::unique_ptr<PopulationObserver> clone() const override;
};

