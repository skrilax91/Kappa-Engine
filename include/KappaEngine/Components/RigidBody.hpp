//
// Created by leo_b on 23/01/2023.
//

#ifndef KAPPA_ENGINE_RIGIDBODY_HPP
#define KAPPA_ENGINE_RIGIDBODY_HPP

#include <vector>

#include "IComponent.hpp"
#include <SFML/System/Vector2.hpp>

namespace Component {

    /**
     * @brief Component that adds a rigidbody to an entity
     * @details This component is used to add physics to an entity
     * @details It is used to add a mass and a gravity to an entity
     * @details It is used to add a velocity to an entity
     */
    class RigidBody: public IComponent {
        public:
            RigidBody(float mass, float gravity) : mass(mass), gravity(gravity) {};
            float mass = 1;
            float gravity = 1;
            sf::Vector2f velocity = {0, 0};

    };
}

#endif //KAPPA_ENGINE_RIGIDBODY_HPP
