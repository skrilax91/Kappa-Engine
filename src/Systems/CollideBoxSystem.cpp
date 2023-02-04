//
// Created by leo_b on 23/01/2023.
//

#include <iostream>
#include "KappaEngine/Systems/CollideBoxSystem.hpp"

namespace KappaEngine {
    void CollideBoxSystem::Awake(std::shared_ptr<Entity> entity) {
        std::cout << "CollideBoxSystem Awake"<< std::endl;
    }
}
