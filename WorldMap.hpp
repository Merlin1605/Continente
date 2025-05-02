#pragma once
#include <memory>
#include <vector>
#include <algorithm>
#include "Continent.hpp"
#include "Exceptions.hpp"

class WorldMap {
public:
    WorldMap() = default;
    WorldMap(const WorldMap&);
    WorldMap& operator=(WorldMap); // copy-and-swap

    void add(std::unique_ptr<Continent> c);     // poate arunca DuplicateContinent
    const Continent& at(std::size_t idx) const; // poate arunca std::out_of_range

    // demonstreaza apelul prin pointer la baza
    void overview() const;

private:
    std::vector<std::unique_ptr<Continent>> continents_;
    friend void swap(WorldMap&, WorldMap&) noexcept;
};
