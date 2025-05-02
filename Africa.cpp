#include "Africa.hpp"

Africa::Africa()
    : Continent("Africa",
      { {"Nigeria",      227000000,  923768,  510, 5.2, 4.9, 4.8, 4.5},
        {"Ethiopia",     129000000, 1104300,  150, 5.0, 4.7, 4.6, 4.4},
        {"Egypt",        112000000, 1001450,  400, 5.6, 5.5, 5.2, 4.9},
        {"South Africa",  61500000, 1221037,  420, 6.3, 6.0, 6.2, 5.8} })
{}
std::unique_ptr<Continent> Africa::clone() const { return std::make_unique<Africa>(*this); }
std::string Africa::major_characteristic() const { return "continentul cu cea mai rapida crestere demografica"; }
