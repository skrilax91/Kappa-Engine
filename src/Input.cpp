//
// Created by leo_b on 29/01/2023.
//

#include "KappaEngine/Input.hpp"
#include "KappaEngine/GameManager.hpp"
#include "KappaEngine/Network/MessageDefine.hpp"

namespace KappaEngine {
    std::vector<const sf::Event *> Input::_events;
    std::map<sf::Keyboard::Key, bool> Input::_keysPressed;

    void Input::setEvents(const std::vector<const sf::Event *>& events) {
        _events = events;

        for (auto &event : _events) {
            if (event->type == sf::Event::KeyPressed) {
                _keysPressed[event->key.code] = true;
                if (GameManager::isNetworked() && GameManager::GetClient()) {

                    Network::Message msg;
                    msg.header.id = Network::NetworkMsg::InputPressed;

                    msg << event->key.code;

                    GameManager::GetClient()->Send(msg);
                }
            } else if (event->type == sf::Event::KeyReleased) {
                _keysPressed[event->key.code] = false;
                if (GameManager::isNetworked() && GameManager::GetClient()) {

                    Network::Message msg;
                    msg.header.id = Network::NetworkMsg::InputReleased;

                    msg << event->key.code;

                    GameManager::GetClient()->Send(msg);
                }
            }
        }

    }
}
