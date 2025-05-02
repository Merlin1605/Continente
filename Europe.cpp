#include "Europe.hpp"

Europe::Europe()
    : Continent("Europa",
      { {"Germany",  83100000, 357022, 4300, 7.8, 8.5, 8.2, 7.6},
        {"France",   68000000, 551695, 2800, 7.5, 8.3, 7.9, 7.2},
        {"Italy",    59000000, 301340, 2100, 7.2, 8.0, 7.6, 7.0},
        {"Spain",    48000000, 505990, 1600, 7.4, 8.1, 7.7, 7.3},
        {"Portugal", 10300000,  92212,  250, 7.3, 8.0, 7.5, 7.4} })
{}
std::unique_ptr<Continent> Europe::clone() const { return std::make_unique<Europe>(*this); }
std::string Europe::major_characteristic() const {
    return "cea mai mare densitate de state suverane pe suprafata mica";
}
