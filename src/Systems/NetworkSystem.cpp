//
// Created by leo_b on 30/01/2023.
//

#include "KappaEngine/Systems/NetworkSystem.hpp"
#include "KappaEngine/Components/NetworkComponent.hpp"
#include "KappaEngine/GameManager.hpp"
#include "KappaEngine/Components/Transform.hpp"

namespace KappaEngine {

    enum NetworkMsg {
        ServerReplication,
    };

    void NetworkSystem::Awake(std::shared_ptr<Entity> entity) {
        std::cout << "NetworkSystem::Awake" << std::endl;
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
                msg << entity->getId().c_str();
                msg << transform;

                GameManager::GetServer()->MessageAllClients(msg, client);
            } else if (GameManager::GetClient() && net->ownerId == GameManager::GetClient()->GetID()) {
                Network::Message msg;
                msg.header.id = NetworkMsg::ServerReplication;
                msg << entity->getId().c_str();
                msg << transform;

                GameManager::GetClient()->Send(msg);
            }
        }
    }
}
