#include "KappaEngine/Systems/AnimationSystem.hpp"
#include "KappaEngine/Components/Animator.hpp"
#include "KappaEngine/Components/SpriteRenderer.hpp"
#include "KappaEngine/Systems/SpriteRendererSystem.hpp"
#include "KappaEngine/GameManager.hpp"

namespace KappaEngine {

    void AnimationSystem::Awake(std::shared_ptr<Entity> entity) {
        auto srs = _scene->getSystemManager()->getSystem<SpriteRendererSystem>();

        if (GameManager::isNetworked() && GameManager::GetServer()) {
            return;
        }

        std::cout << "AnimationSystem Awake" << std::endl;

        auto spriteRenderer = entity->getComponent<Component::SpriteRenderer>();
        auto animator = entity->getComponent<Component::Animator>();

        if (spriteRenderer == nullptr || animator == nullptr) {
            return;
        }

        if (!spriteRenderer->enabled)
            animator->enabled = false;


        for (auto animation : animator->_animations) {
            if (srs->_textureCache.contains(animation.second->_texturePath)) {
                std::cout << "AnimationSystem: texture " + animation.second->_texturePath + " already loaded" << std::endl;
                animation.second->_texture = srs->_textureCache[animation.second->_texturePath];
                return;
            } else {
                std::cout << "AnimationSystem: loading texture " + animation.second->_texturePath << std::endl;
            }

            sf::Texture texture;
            if (!texture.loadFromFile(animation.second->_texturePath)) {
                std::cout << "Error while loading texture " << animation.second->_texturePath << std::endl;
                return;
            }

            srs->_textureCache[animation.second->_texturePath] = texture;
            animation.second->_texture = srs->_textureCache[animation.second->_texturePath];
            std::cout << "AnimationSystem: added texture " + animation.second->_texturePath << std::endl;

        }
    }

    void AnimationSystem::OnAnimator() {
        auto entities = _scene->getEntityManager()->getEntitiesWithComponent<Component::Animator>();
        for (auto entity : entities) {
            auto animator = entity->getComponent<Component::Animator>();
            auto animation = animator->_animations[animator->_actualAnimation];
            if (animation->_clock.getElapsedTime().asSeconds() >= animation->_duration) {
                animation->_actualFrame++;
                if (animation->_actualFrame >= animation->_textureRect.size()) {
                    if (animation->_loop) {
                        animation->_actualFrame = 0;
                    } else {
                        animation->_actualFrame--;
                    }
                }
                animation->_clock.restart();
            }
            animation->_spriteRenderer->_sprite.setTexture(animation->_texture);
            animation->_spriteRenderer->_sprite.setTextureRect(animation->_textureRect[animation->_actualFrame]);
        }
    }
}