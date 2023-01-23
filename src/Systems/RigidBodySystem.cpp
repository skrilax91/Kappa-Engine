//
// Created by leo_b on 23/01/2023.
//

#include <iostream>
#include <ctime>
#include "KappaEngine/Systems/RigidBodySystem.hpp"

namespace KappaEngine {
    void RigidBodySystem::Awake() {
        std::srand(std::time(nullptr) + 10);

        int rand = std::rand();

        for (int i = 0; i < rand ; i++);

        std::cout << "RigidBodySystem Awake rand " << rand << std::endl;
    }

    void RigidBodySystem::Update() {
        auto ents = _scene->getEntityManager()->getEntitiesWithComponent<Component::RigidBody>();

        for (auto &ent: ents) {
            std::cout << "RigidBodySystem Update for entity " << ent->getId() << std::endl;
        }
    }
}