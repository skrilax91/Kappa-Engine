//
// Created by leo_b on 25/01/2023.
//

#ifndef KAPPA_ENGINE_TIME_HPP
#define KAPPA_ENGINE_TIME_HPP

#include <SFML/System.hpp>
#include <functional>

namespace KappaEngine {
    class Time {
        public:
        static sf::Time DeltaTime() {
            return _deltaTime;
        };

        static sf::Time UpdateDeltaTime() {
            _deltaTime = _deltaClock.restart();
            return _deltaTime;
        };

        static double FixedDeltaTime() {
            return _fixedDeltaTime;
        };

        static void resetTimeLib() {
            _deltaClock.restart();
            _deltaTime = sf::Time::Zero;
            _fixedDeltaTime = 0.01;
            _lags = 0.0;
        }

        static void RunOnFixedEnv(const std::function<void()>& func) {
            _lags += _deltaTime.asSeconds();
            while (_lags >= _fixedDeltaTime) {
                func();
                _lags -= _fixedDeltaTime;
            }
        }

        static sf::Clock _deltaClock;
        static sf::Time _deltaTime;
        static double _fixedDeltaTime;
        static double _lags;
    };


    sf::Time Time::_deltaTime = sf::Time::Zero;
    double Time::_fixedDeltaTime = 0.01;
    double Time::_lags = 0.0;
    sf::Clock Time::_deltaClock = sf::Clock();
}

#endif //KAPPA_ENGINE_TIME_HPP
