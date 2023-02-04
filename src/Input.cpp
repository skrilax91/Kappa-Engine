//
// Created by leo_b on 29/01/2023.
//

#include "KappaEngine/Input.hpp"

namespace KappaEngine {
    std::vector<const sf::Event *> Input::_events;
    std::map<sf::Keyboard::Key, bool> Input::_keysPressed;

    void Input::setEvents(const std::vector<const sf::Event *>& events) {
        _events = events;

        for (auto &event : _events) {
            if (event->type == sf::Event::KeyPressed) {
                _keysPressed[event->key.code] = true;
            } else if (event->type == sf::Event::KeyReleased) {
                _keysPressed[event->key.code] = false;
            }
        }

    }
}
