#pragma once
#include "Continent.hpp"

class Asia final : public Continent {
public:
    Asia();
    std::unique_ptr<Continent> clone() const override;
    std::string major_characteristic() const override;
};

