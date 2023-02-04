//
// Created by leo_b on 23/01/2023.
//

#ifndef KAPPA_ENGINE_RIGIDBODYSYSTEM_HPP
#define KAPPA_ENGINE_RIGIDBODYSYSTEM_HPP

#include "ISystem.hpp"
#include "KappaEngine/Components/RigidBody.hpp"

namespace KappaEngine {

    /**
     * @brief The RigidBodySystem class is the class that will manage all the rigid bodies of the engine.
     */
    class RigidBodySystem : public ISystem {
        public:
            /**
             * @brief RigidBodySystem Constructor of the RigidBodySystem class.
             *
             * This function will construct the RigidBodySystem class.
             *
             * @param scene The scene that the rigid body system will manage.
             */
            explicit RigidBodySystem(Scene *scene) : ISystem(scene) {};
            void Awake(std::shared_ptr<Entity>) override;
            void FixedUpdate() override;

            static void applyForce(Component::RigidBody *rg, sf::Vector2f force);
    };
}


#endif //KAPPA_ENGINE_RIGIDBODYSYSTEM_HPP
