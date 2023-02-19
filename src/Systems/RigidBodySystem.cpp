//
// Created by leo_b on 23/01/2023.
//

#include <iostream>
#include <ctime>

#include "KappaEngine/GameManager.hpp"
#include "KappaEngine/Systems/RigidBodySystem.hpp"
#include "KappaEngine/Components/Transform.hpp"
#include "KappaEngine/Components/NetworkComponent.hpp"
#include "KappaEngine/Time.hpp"

namespace KappaEngine {
    void RigidBodySystem::Awake(std::shared_ptr<Entity> entity) {
        std::cout << "RigidBodySystem Awake" << std::endl;
    }

    void RigidBodySystem::FixedUpdate() {
        auto ents = _scene->getEntityManager()->getEntitiesWithComponent<Component::RigidBody>();

        for (auto ent: ents) {
            if (GameManager::isNetworked()) {
                auto net = ent->getComponent<Component::NetworkComponent>();

                if (GameManager::GetServer() && net && net->ownerId != -1) {
                    continue;
                }

                if (GameManager::GetClient() && net && net->ownerId == GameManager::GetClient()->GetID()) {
                    continue;
                }
            }


            auto rg = ent->getComponent<Component::RigidBody>();
            auto tr = ent->getComponent<Component::Transform>();

            if (tr == nullptr) {
                continue;
            }

            tr->position += rg->velocity * (float) Time::FixedDeltaTime();
        }
    }

    void RigidBodySystem::applyForce(Component::RigidBody *rg, sf::Vector2f force) {}
}
