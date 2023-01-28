//
// Created by leo_b on 28/01/2023.
//

#include "KappaEngine/Time.hpp"

namespace KappaEngine {
    sf::Time Time::_deltaTime = sf::Time::Zero;
    double Time::_fixedDeltaTime = 0.01;
    double Time::_lags = 0.0;
    sf::Clock Time::_deltaClock = sf::Clock();
}