//
// Created by leo_b on 25/01/2023.
//

#ifndef KAPPA_ENGINE_TIME_HPP
#define KAPPA_ENGINE_TIME_HPP

#include <SFML/System.hpp>
#include <functional>

namespace KappaEngine {

    /**
     * @brief The Time class allows some parts of the program to run on its own environnement, with a fixed time.
     */
    class Time {
        public:

        /**
         * @brief DeltaTime gets the amount of time per frame in seconds.
         * 
         * @return * sf::Time, the amount of time that a frame takes in seconds.
         */
        static sf::Time DeltaTime() {
            return _deltaTime;
        };

        /**
         * @brief UpdateDeltaTime restarts the deltaClock and updates deltaTime with the time elapsed since it was last updated.
         * 
         * @return sf::Time, the time elapsed since the clock was last restarted.
         */
        static sf::Time UpdateDeltaTime() {
            _deltaTime = _deltaClock.restart();
            return _deltaTime;
        };

        /**
         * @brief FixedDeltaTime is an attribute of the engine Time class that allows the systems to run their methods on a fixed amount of time.
         * 
         * @return double, the attribute _fixedDeltaTime.
         */
        static double FixedDeltaTime() {
            return _fixedDeltaTime;
        };

        /**
         * @brief resetTimeLib resets all attributes of KappaEngine::Time.
         * 
         */
        static void resetTimeLib() {
            _deltaClock.restart();
            _deltaTime = sf::Time::Zero;
            _fixedDeltaTime = 0.01;
            _lags = 0.0;
        }

        /**
         * @brief RunOnFixedEnv allows the systems to run a method several times to complete an action on a fixed amount of time.
         * 
         * For example, it can be used to handle the movement of a bullet or that of a jumping character.
         * 
         * @param func The function to be executed several times on a fixed amount of time.
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
