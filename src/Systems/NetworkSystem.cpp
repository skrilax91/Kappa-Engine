//
// Created by leo_b on 30/01/2023.
//

#include "KappaEngine/Systems/NetworkSystem.hpp"
#include "KappaEngine/Components/NetworkComponent.hpp"

namespace KappaEngine {
    void NetworkSystem::Awake(std::shared_ptr<Entity> entity) {

        _clock.restart();

        try {
            GameManager::RegisterServerMessageHandler(Network::NetworkMsg::ServerReplication, [](std::shared_ptr<Network::Connection> client, Network::Message &msg) {
                uint32_t id;
                sf::Vector2f pos;

                msg >> pos >> id;

                auto entities = GameManager::GetSelectedScene()->getEntityManager()->getEntitiesWithComponent<Component::NetworkComponent>();

                for (auto &entity : entities) {
                    auto net = entity->getComponent<Component::NetworkComponent>();
                    if (net->uniqueId == id) {
                        auto transform = entity->getComponent<Component::Transform>();
                        transform->position = pos;
                        continue;
                    }
                }
            });

            std::cout << "NetworkSystem::Awake: Registered ServerReplication" << std::endl;
        } catch (std::exception &e) {
            std::cout << "[SERVER][ERROR] " << e.what() << std::endl;
        }

        try {
            GameManager::RegisterClientMessageHandler(Network::NetworkMsg::ServerReplication, [](Network::Message &msg) {
                uint32_t id;
                sf::Vector2f pos;

                msg >> pos >> id;

                auto entities = GameManager::GetSelectedScene()->getEntityManager()->getEntitiesWithComponent<Component::NetworkComponent>();

                for (auto &entity : entities) {
                    auto net = entity->getComponent<Component::NetworkComponent>();
                    if (net->uniqueId == id) {
                        auto transform = entity->getComponent<Component::Transform>();
                        transform->position = pos;
                        continue;
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

            _clock.restart();

            if (GameManager::GetServer()) {
                auto client = GameManager::GetServer()->GetClient(net->ownerId);

                Network::Message msg;
                msg.header.id = Network::NetworkMsg::ServerReplication;
                msg << net->uniqueId << transform->position;

                GameManager::GetServer()->MessageAllClients(msg, client);
            } else if (GameManager::GetClient() && net->ownerId == GameManager::GetClient()->GetID()) {

                Network::Message msg;
                msg.header.id = Network::NetworkMsg::ServerReplication;
                msg << net->uniqueId << transform->position;

                GameManager::GetClient()->Send(msg);
            }
        }
    }
}
