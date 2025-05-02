#pragma once
#include <cstdint>
#include <memory>
#include <string>

class Continent;

class PopulationObserver {
public:
    virtual ~PopulationObserver() = default;
    virtual void notify(const Continent&,
                        std::uint64_t oldPop,
                        std::uint64_t newPop) const = 0;
    virtual std::unique_ptr<PopulationObserver> clone() const = 0;
};

