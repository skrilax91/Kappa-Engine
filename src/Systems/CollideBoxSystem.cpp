//
// Created by leo_b on 23/01/2023.
//

#include <iostream>
#include "KappaEngine/Systems/CollideBoxSystem.hpp"

namespace KappaEngine {
    void CollideBoxSystem::Awake() {
        std::srand(std::time(nullptr));

        int rand = std::rand();

        for (int i = 0; i < rand ; i++);

        std::cout << "CollideBoxSystem Awake rand " << rand << std::endl;
    }
}
