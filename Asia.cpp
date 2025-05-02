#include "Asia.hpp"

Asia::Asia()
    : Continent("Asia",
      { {"China",      1420000000, 9596961, 18000, 6.5, 6.5, 6.4, 5.8},
        {"India",      1410000000, 3287263,  3600, 6.0, 6.0, 6.0, 5.5},
        {"Japan",       125000000,  377975,  5000, 8.2, 8.7, 8.6, 8.1},
        {"Indonesia",    279000000, 1904569, 1300, 6.2, 6.3, 6.1, 5.9} })
{}
std::unique_ptr<Continent> Asia::clone() const { return std::make_unique<Asia>(*this); }
std::string Asia::major_characteristic() const { return "cel mai intins si populat continent"; }
