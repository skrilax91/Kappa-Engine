//
// Created by leo_b on 29/01/2023.
//

#ifndef KAPPA_ENGINE_INPUT_HPP
#define KAPPA_ENGINE_INPUT_HPP

#include <SFML/Graphics.hpp>
#include <utility>
#include <vector>

namespace KappaEngine {
    /*
     * @brief The Input class is used to manage the input of the user
     */
    class Input {
        public:

            /*
             * @brief IsKeyPressed Check if a key is pressed
             * @tparam T The key to check
             * @return True if the key is pressed, false otherwise
             */
            template<sf::Keyboard::Key T>
            static bool IsKeyPressed() {
                return sf::Keyboard::isKeyPressed(T);
            }

            /*
             * @brief IsKeyJustPressed Check if a key is just pressed
             * @tparam T The key to check
             * @return True if the key is just pressed, false otherwise
             */
            template<sf::Keyboard::Key T>
            static bool IsKeyJustPressed() {
                for (auto &event : _events) {
                    if (event->type == sf::Event::KeyPressed && event->key.code == T) {
                        return true;
                    }
                }
                return false;
            }

            /*
             * @brief IsKeyReleased Check if a key is released
             * @tparam T The key to check
             * @return True if the key is released, false otherwise
             */
            template<sf::Keyboard::Key T>
            static bool IsKeyReleased() {
                for (auto &event : _events) {
                    if (event->type == sf::Event::KeyReleased && event->key.code == T) {
                        return true;
                    }
                }
                return false;
            }

            /*
             * @brief Set the events of the input
             */
            static void setEvents(const std::vector<const sf::Event *>& events);

        private:
            static std::vector<const sf::Event *> _events;
    };
}

#endif //KAPPA_ENGINE_INPUT_HPP
