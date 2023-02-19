#include "KappaEngine/Systems/AnimationSystem.hpp"
#include "KappaEngine/Components/Animation.hpp"

namespace KappaEngine {
    void AnimationSystem::Awake(std::shared_ptr<Entity> entity) {
        std::cout << "AnimationSystem Awake" << std::endl;
    }

    void AnimationSystem::Update(std::shared_ptr<Entity> entity) {
        std::cout << "AnimationSystem Update" << std::endl;
    }

    void AnimationSystem::FixedUpdate(std::shared_ptr<Entity> entity) {
        std::cout << "AnimationSystem FixedUpdate" << std::endl;
    }
}
