//
// Created by leo_b on 29/01/2023.
//

#include "KappaEngine/Input.hpp"
#include "KappaEngine/GameManager.hpp"
#include "KappaEngine/Network/MessageDefine.hpp"

namespace KappaEngine {
    std::vector<const sf::Event *> Input::_events;
    std::map<sf::Keyboard::Key, bool> Input::_keysPressed;
    std::map<uint32_t, std::map<sf::Keyboard::Key, bool>> Input::_networkKeysPressed;


    void Input::InitNetworkKeys() {
        GameManager::RegisterServerMessageHandler(Network::NetworkMsg::InputPressed, [](std::shared_ptr<Network::Connection> client, Network::Message &msg) {

            while (!msg.body.empty()) {
                sf::Keyboard::Key key;
                msg >> key;
                _networkKeysPressed[client->GetID()][key] = true;
            }
        });

        GameManager::RegisterServerMessageHandler(Network::NetworkMsg::InputReleased, [](std::shared_ptr<Network::Connection> client, Network::Message &msg) {

            while (!msg.body.empty()) {
                sf::Keyboard::Key key;
                msg >> key;
                _networkKeysPressed[client->GetID()][key] = false;
            }
        });
    }

    void Input::setEvents(const std::vector<const sf::Event *>& events) {
        _events = events;

        if (GameManager::isNetworked() && GameManager::GetClient()) {
            Network::Message msg;
            msg.header.id = Network::NetworkMsg::InputPressed;

            bool isPressed = false;

            for (auto &event : _events) {
                if (event->type == sf::Event::KeyPressed) {
                    isPressed = true;
                    msg << event->key.code;
                }
            }

            if (isPressed)
                GameManager::GetClient()->Send(msg);
        }

        for (auto &event : _events) {
            if (event->type == sf::Event::KeyPressed) {
                _keysPressed[event->key.code] = true;
            } else if (event->type == sf::Event::KeyReleased) {
                _keysPressed[event->key.code] = false;
            }
        }

    }
}
