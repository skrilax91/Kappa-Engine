
#ifndef KAPPA_ENGINE_ANIMATIONSYSTEM_HPP
#define KAPPA_ENGINE_ANIMATIONSYSTEM_HPP

#include "ISystem.hpp"
#include "KappaEngine/Components/Animator.hpp"
#include "KappaEngine/Scene.hpp"
#include "KappaEngine/Entity/Entity.hpp"

namespace KappaEngine {
    class AnimationSystem : public ISystem {
        public:
            explicit AnimationSystem(Scene *scene) : ISystem(scene) {};
            void OnAnimator();
    };
}

#endif //KAPPA_ENGINE_ANIMATIONSYSTEM_HPP