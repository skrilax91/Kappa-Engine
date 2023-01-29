//
// Created by leo_b on 23/01/2023.
//

#include <iostream>
#include <ctime>
#include "KappaEngine/Systems/RigidBodySystem.hpp"
#include "KappaEngine/Components/Transform.hpp"
#include "KappaEngine/Time.hpp"

namespace KappaEngine {
    void RigidBodySystem::Awake() {
        std::srand(std::time(nullptr) + 10);

        int rand = std::rand();

        for (int i = 0; i < rand ; i++);

        std::cout << "RigidBodySystem Awake rand " << rand << std::endl;
    }

    void RigidBodySystem::FixedUpdate() {
        auto ents = _scene->getEntityManager()->getEntitiesWithComponent<Component::RigidBody>();

        for (auto &ent: ents) {
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
