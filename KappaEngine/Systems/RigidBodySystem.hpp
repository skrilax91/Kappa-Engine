//
// Created by leo_b on 23/01/2023.
//

#ifndef KAPPA_ENGINE_RIGIDBODYSYSTEM_HPP
#define KAPPA_ENGINE_RIGIDBODYSYSTEM_HPP

#include "ISystem.hpp"
#include "KappaEngine/Components/RigidBody.hpp"

namespace KappaEngine {
    class RigidBodySystem : public ISystem {
        public:
            explicit RigidBodySystem(Scene *scene) : ISystem(scene) {};
            void Awake() override;
            void FixedUpdate() override;

            static void applyForce(Component::RigidBody *rg, sf::Vector2f force);
    };
}


#endif //KAPPA_ENGINE_RIGIDBODYSYSTEM_HPP
