//
// Created by leo_b on 23/01/2023.
//

#ifndef KAPPA_ENGINE_COLLIDEBOXSYSTEM_HPP
#define KAPPA_ENGINE_COLLIDEBOXSYSTEM_HPP

#include "ISystem.hpp"

namespace KappaEngine {
    class CollideBoxSystem : public ISystem {
        public:
            explicit CollideBoxSystem(Scene *scene) : ISystem(scene) {};
            void Awake(std::shared_ptr<Entity>) override;
    };
}


#endif //KAPPA_ENGINE_COLLIDEBOXSYSTEM_HPP
