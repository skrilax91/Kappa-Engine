
#ifndef KAPPA_ENGINE_ANIMATIONSYSTEM_HPP
#define KAPPA_ENGINE_ANIMATIONSYSTEM_HPP

#include "ISystem.hpp"
#include "KappaEngine/Scene.hpp"
#include "KappaEngine/Entity/Entity.hpp"

namespace KappaEngine {
    class SoundSystem : public ISystem {
        public:
            explicit SoundSystem(Scene *scene) : ISystem(scene) {};

            void Awake(std::shared_ptr<Entity>) override;
            void OnSound() override;
    };
}

#endif //KAPPA_ENGINE_ANIMATIONSYSTEM_HPP