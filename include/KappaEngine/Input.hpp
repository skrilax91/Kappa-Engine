//
// Created by leo_b on 29/01/2023.
//

#ifndef KAPPA_ENGINE_INPUT_HPP
#define KAPPA_ENGINE_INPUT_HPP

#include <SFML/Graphics.hpp>
#include <utility>
#include <vector>

#include "KappaEngine/GameManager.hpp"

namespace KappaEngine {
    /*
     * @brief The Input class is used to manage the input of the user
     */
    class Input {
        public:

            /*
             * @brief InitNetworkKeys Initialize the network keys
             */
            static void InitNetworkKeys();

            /*
             * @brief IsKeyPressed Check if a key is pressed.
             *
             * @network SERVER If the key is pressed on the network for the given id
             *
             * @tparam T The key to check
             * @param id The id of the player to check (only for server)
             *
             * @return True if the key is pressed, false otherwise (or if the id is invalid)
             */
            template<sf::Keyboard::Key T>
            static bool IsKeyPressed(uint32_t id = -1) {
                if (GameManager::GetServer()) {
                    if (id == -1)
                        return false;
                    return _networkKeysPressed[id][T];
                }

                return _keysPressed[T];
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

            /*
             * @brief Get pressed keys
             */
            static std::vector<sf::Keyboard::Key> getKeysPressed();

            /*
             * @brief Add a function to call when a key is pressed
             * @tparam T The key to check
             * @param func The function to call
             */
            template<sf::Keyboard::Key T>
            static void AddKeyPressedEvent(std::string id, std::function<void()> func) {
                if (_keyPressedEvents.find(id) != _keyPressedEvents.end())
                    return;

                _keyPressedEvents[id] = std::make_pair(T, func);
            }

            /*
             * @brief Remove a function to call when a key is pressed
             * @param id The id of the function to remove
             */
            static void RemoveKeyPressedEvent(std::string id) {
                if (_keyPressedEvents.find(id) == _keyPressedEvents.end())
                    return;

                _keyPressedEvents.erase(id);
            }

        private:
            static std::vector<const sf::Event *> _events;
            static std::map<sf::Keyboard::Key, bool> _keysPressed;
            static std::map<uint32_t, std::map<sf::Keyboard::Key, bool>> _networkKeysPressed;
            static std::map<std::string, std::pair<sf::Keyboard::Key, std::function<void()>>> _keyPressedEvents;
    };
}

#endif //KAPPA_ENGINE_INPUT_HPP
