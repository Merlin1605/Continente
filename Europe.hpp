#pragma once
#include "Continent.hpp"

class Europe final : public Continent {
public:
    Europe();
    Europe(const Europe&) = default;
    Europe& operator=(const Europe&) = default;

    std::unique_ptr<Continent> clone() const override;
    std::string major_characteristic() const override;
};

