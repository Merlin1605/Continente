#pragma once
#include "Continent.hpp"

class Africa final : public Continent {
public:
    Africa();
    std::unique_ptr<Continent> clone() const override;
    std::string major_characteristic() const override;
};

