
#ifndef KAPPA_ENGINE_ANIMATIONSYSTEM_HPP
#define KAPPA_ENGINE_ANIMATIONSYSTEM_HPP

#include "ISystem.hpp"

namespace KappaEngine {
    class AnimationSystem : public ISystem {
        public:
            explicit AnimationSystem(Scene *scene) : ISystem(scene) {};
            void Awake(std::shared_ptr<Entity>) override;
    };
}

#endif //KAPPA_ENGINE_ANIMATIONSYSTEM_HPP