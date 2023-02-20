#include "KappaEngine/Systems/AnimationSystem.hpp"
#include "KappaEngine/Components/Animator.hpp"

namespace KappaEngine {
    void AnimationSystem::OnAnimator(std::shared_ptr<Entity> entity) {
        auto animator = entity->getComponent<Component::Animator>();
        if (!animator) {
            return;
        }

        // Find actual Animation
        auto currentAnimation = animator->_animations.begin();
        for (; currentAnimation != animator->_animations.end(); ++currentAnimation) {
            if (currentAnimation->_id == animator->_idleAnimation) {
                break;
            }
        }
        if (currentAnimation == animator->_animations.end()) {
            return;
        }
    }
}