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
     * @brief The RigidBody component contains all the data used for the physics of the game or scene.
     * 
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
