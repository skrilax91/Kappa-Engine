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

        auto *keys = &_networkKeysPressed;

        GameManager::RegisterServerMessageHandler(Network::NetworkMsg::InputPressed, [keys](std::shared_ptr<Network::Connection> client, Network::Message &msg) {
            std::cout << "InputPressed from client[" << client->GetID() << "] : ";
            while (!msg.body.empty()) {
                sf::Keyboard::Key key;
                msg >> key;
                std::cout << key << " ";
                (*keys)[client->GetID()][key] = true;
            }
            std::cout << std::endl;
        });

        GameManager::RegisterServerMessageHandler(Network::NetworkMsg::InputReleased, [keys](std::shared_ptr<Network::Connection> client, Network::Message &msg) {
            std::cout << "InputRelease from client[" << client->GetID() << "] : ";
            while (!msg.body.empty()) {
                sf::Keyboard::Key key;
                msg >> key;
                std::cout << key << " ";
                (*keys)[client->GetID()][key] = false;
            }
            std::cout << std::endl;
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

            Network::Message msg2;
            msg2.header.id = Network::NetworkMsg::InputReleased;

            bool isReleased = false;

            for (auto &event : _events) {
                if (event->type == sf::Event::KeyReleased) {
                    isReleased = true;
                    msg2 << event->key.code;
                }
            }

            if (isReleased)
                GameManager::GetClient()->Send(msg2);
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
