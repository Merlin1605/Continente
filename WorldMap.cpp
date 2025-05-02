#include "WorldMap.hpp"
#include <iostream>

WorldMap::WorldMap(const WorldMap& other) {
    for (const auto& c : other.continents_) {
        continents_.push_back(c->clone());
    }
}
void swap(WorldMap& a, WorldMap& b) noexcept { std::swap(a.continents_, b.continents_); }
WorldMap& WorldMap::operator=(WorldMap rhs) {
    swap(*this, rhs);
    return *this;
}

void WorldMap::add(std::unique_ptr<Continent> c) {
    auto already = std::find_if(
        continents_.begin(), continents_.end(),
        [&c](const auto& ptr) { return ptr->describe() == c->describe(); });

    if (already != continents_.end())
        throw DuplicateContinent("Continent deja existent!");
    continents_.push_back(std::move(c));
}

const Continent& WorldMap::at(std::size_t idx) const { return *continents_.at(idx); }

void WorldMap::overview() const {
    std::cout << "=== WORLD OVERVIEW ===\n";
    for (const auto& c : continents_) std::cout << c->describe() << '\n';
    std::cout << '\n';
}
