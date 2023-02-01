//
// Created by leo_b on 29/01/2023.
//

#include "KappaEngine/Input.hpp"

namespace KappaEngine {
    std::vector<const sf::Event *> Input::_events;

    void Input::setEvents(const std::vector<const sf::Event *>& events) {
        _events = events;
    }
}
