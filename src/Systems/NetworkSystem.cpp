//
// Created by leo_b on 30/01/2023.
//

#include "KappaEngine/Systems/NetworkSystem.hpp"
#include "KappaEngine/Components/NetworkComponent.hpp"
#include "KappaEngine/GameManager.hpp"
#include "KappaEngine/Components/Transform.hpp"

namespace KappaEngine {

    void NetworkSystem::Awake(std::shared_ptr<Entity> entity) {

        _clock.restart();

        try {
            GameManager::RegisterServerMessageHandler(Network::NetworkMsg::ServerReplication, [](std::shared_ptr<Network::Connection> client, Network::Message &msg) {
                std::map<uint32_t, sf::Vector2f> positions;

                while (msg.body.size() > 0) {
                    uint32_t id;
                    sf::Vector2f pos;

                    msg >> pos >> id;
                    positions[id] = pos;
                }

                auto entities = GameManager::GetSelectedScene()->getEntityManager()->getEntitiesWithComponent<Component::NetworkComponent>();

                for (auto &entity : entities) {
                    auto net = entity->getComponent<Component::NetworkComponent>();

                    if (positions.find(net->uniqueId) != positions.end()) {
                        auto transform = entity->getComponent<Component::Transform>();
                        transform->position = positions[net->uniqueId];
                    }
                }
            });

            std::cout << "NetworkSystem::Awake: Registered ServerReplication" << std::endl;
        } catch (std::exception &e) {
            std::cout << "[SERVER][ERROR] " << e.what() << std::endl;
        }

        try {
            GameManager::RegisterClientMessageHandler(Network::NetworkMsg::ServerReplication, [](Network::Message &msg) {
                std::map<uint32_t, sf::Vector2f> positions;

                while (msg.body.size() > 0) {
                    uint32_t id;
                    sf::Vector2f pos;

                    msg >> pos >> id;
                    positions[id] = pos;
                }

                auto entities = GameManager::GetSelectedScene()->getEntityManager()->getEntitiesWithComponent<Component::NetworkComponent>();

                for (auto &entity : entities) {
                    auto net = entity->getComponent<Component::NetworkComponent>();

                    if (positions.find(net->uniqueId) != positions.end() && net->ownerId != GameManager::GetClient()->GetID()) {
                        auto transform = entity->getComponent<Component::Transform>();
                        transform->position = positions[net->uniqueId];
                    }
                }
            });
        } catch (std::exception &e) {
            std::cout << "[CLIENT][ERROR] " << e.what() << std::endl;
        }

    }

    void NetworkSystem::Start(std::shared_ptr<Entity> entity) {
        std::cout << "NetworkSystem::Start on scene " << _scene->getName() << std::endl;
    }

    void NetworkSystem::Update() {
        if (!GameManager::isNetworked()) {
            return;
        }

        bool finallyReplicated = false;
        Network::Message msg;
        msg.header.id = Network::NetworkMsg::ServerReplication;

        auto entities = _scene->getEntityManager()->getEntitiesWithComponent<Component::NetworkComponent>();



        for (auto &entity : entities) {
            auto net = entity->getComponent<Component::NetworkComponent>();
            auto transform = entity->getComponent<Component::Transform>();

            bool replicated = false;

            if (!net || !transform) {
                continue;
            }

            if (net->transform.position != transform->position) {
                net->transform.position = transform->position;
                replicated = true;
            }

            if (!replicated || _clock.getElapsedTime().asMilliseconds() < 10) {
                continue;
            }

            if (GameManager::GetServer()) {
                msg << net->uniqueId << transform->position;
                finallyReplicated = true;
            } else if (GameManager::GetClient() && net->ownerId == GameManager::GetClient()->GetID()) {
                msg << net->uniqueId << transform->position;
                finallyReplicated = true;
            }
        }

        if (finallyReplicated) {
            if (GameManager::GetClient())
                GameManager::GetClient()->Send(msg);
            else if (GameManager::GetServer())
                GameManager::GetServer()->MessageAllClients(msg);
            _clock.restart();
        }
    }
}
