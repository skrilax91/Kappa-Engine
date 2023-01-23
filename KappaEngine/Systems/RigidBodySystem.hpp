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
            void Update() override;
    };
}


#endif //KAPPA_ENGINE_RIGIDBODYSYSTEM_HPP
