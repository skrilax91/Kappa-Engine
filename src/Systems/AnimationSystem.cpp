#include "KappaEngine/Systems/AnimationSystem.hpp"
#include "KappaEngine/Components/Animator.hpp"

namespace KappaEngine {
    void AnimationSystem::OnAnimator() {
        auto entities = _scene->getEntityManager()->getEntitiesWithComponent<Component::Animator>();
        for (auto entity : entities) {
            auto animator = entity->getComponent<Component::Animator>();
            auto animation = animator->_animations[animator->_actualAnimation];
            if (animation._clock.getElapsedTime().asSeconds() >= animation._duration) {
                animation._actualFrame++;
                if (animation._actualFrame >= animation._textureRect.size()) {
                    if (animation._loop) {
                        animation._actualFrame = 0;
                    } else {
                        animation._actualFrame--;
                    }
                }
                animation._clock.restart();
            }
            animation._spriteRenderer._sprite.setTexture(animation._texture);
            animation._spriteRenderer._sprite.setTextureRect(animation._textureRect[animation._actualFrame]);
        }
    }
}