//
// Created by leo_b on 25/01/2023.
//

#ifndef KAPPA_ENGINE_TIME_HPP
#define KAPPA_ENGINE_TIME_HPP

#include <SFML/System.hpp>
#include <functional>

namespace KappaEngine {
    /**
     * @brief Time class
     * @details This class is used to get the delta time
     * @details It is used to get the fixed delta time
     * @details It is used to run a function on a fixed environment
     */
    class Time {
        public:

        /**
         * @brief Get the delta time
         * @details This function is used to get the delta time
         * @details The delta time is the time between two frames
         * @details It is used to make the game framerate independent
         * @return The delta time
         */
        static sf::Time DeltaTime() {
            return _deltaTime;
        };

        /**
         * @brief Update the delta time
         * @details This function is used to update the delta time
         * @details It is used to make the game framerate independent
         * @return The delta time
         */
        static sf::Time UpdateDeltaTime() {
            _deltaTime = _deltaClock.restart();
            return _deltaTime;
        };

        /**
         * @brief Get the fixed delta time
         * @details This function is used to get the fixed delta time
         * @details The fixed delta time is a fixed time used to update the game logic (physics, ...)
         * @details It is used to make the game framerate independent
         * @return The fixed delta time
         */
        static double FixedDeltaTime() {
            return _fixedDeltaTime;
        };

        /**
         * @brief Reset the time library
         * @details This function is used to reset the time library
         */
        static void resetTimeLib() {
            _deltaClock.restart();
            _deltaTime = sf::Time::Zero;
            _fixedDeltaTime = 0.01;
            _lags = 0.0;
        }

        /**
         * @brief Run a function on a fixed environment
         * @details This function is used to run a function on a fixed environment
         * @details It is used to make the game framerate independent
         * @param func The function to run
         */
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
}

#endif //KAPPA_ENGINE_TIME_HPP
