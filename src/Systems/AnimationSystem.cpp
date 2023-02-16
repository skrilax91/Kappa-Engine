#include "KappaEngine/Systems/AnimationSystem.hpp"

namespace KappaEngine {
    void AnimationSystem::Awake(std::shared_ptr<Entity> entity) {
        std::cout << "AnimationSystem Awake" << std::endl;
    }
}
