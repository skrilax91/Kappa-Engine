//
// Created by leo_b on 30/01/2023.
//

#include "KappaEngine/Systems/NetworkSystem.hpp"
#include "KappaEngine/Components/NetworkComponent.hpp"
#include "KappaEngine/GameManager.hpp"
#include "KappaEngine/Components/Transform.hpp"

namespace KappaEngine {

    enum NetworkMsg {
        ServerReplication = -999,
    };

    void NetworkSystem::Awake(std::shared_ptr<Entity> entity) {
        std::cout << "NetworkSystem::Awake" << std::endl;

        try {
            GameManager::RegisterServerMessageHandler(NetworkMsg::ServerReplication, [](std::shared_ptr<Network::Connection> client, Network::Message &msg) {
                uint32_t id;

                msg >> id;

                auto entities = GameManager::GetSelectedScene()->getEntityManager()->getEntitiesWithComponent<Component::NetworkComponent>();

                for (auto &entity : entities) {
                    auto net = entity->getComponent<Component::NetworkComponent>();
                    if (net->uniqueId == id) {
                        auto transform = entity->getComponent<Component::Transform>();
                        msg >> transform;
                        return;
                    }
                }

                std::cout << "ServerReplication: " << id << std::endl;
            });
            std::cout << "NetworkSystem::Awake: Registered ServerReplication" << std::endl;
        } catch (std::exception &e) {
            std::cout << "[SERVER][ERROR] " << e.what() << std::endl;
        }

    }

    void NetworkSystem::Start(std::shared_ptr<Entity> entity) {
        std::cout << "NetworkSystem::Start" << std::endl;
    }

    void NetworkSystem::Update() {
        if (!GameManager::isNetworked()) {
            return;
        }

        auto entities = _scene->getEntityManager()->getEntitiesWithComponent<Component::NetworkComponent>();



        for (auto &entity : entities) {
            auto net = entity->getComponent<Component::NetworkComponent>();
            auto transform = entity->getComponent<Component::Transform>();

            if (!net || !transform) {
                continue;
            }

            if (GameManager::GetServer()) {
                auto client = GameManager::GetServer()->GetClient(net->ownerId);

                Network::Message msg;
                msg.header.id = NetworkMsg::ServerReplication;
                msg << net->uniqueId;
                msg << transform;

                GameManager::GetServer()->MessageAllClients(msg, client);
            } else if (GameManager::GetClient() && net->ownerId == GameManager::GetClient()->GetID()) {
                Network::Message msg;
                msg.header.id = NetworkMsg::ServerReplication;
                msg << net->uniqueId;
                msg << transform;

                GameManager::GetClient()->Send(msg);
            }
        }
    }
}
