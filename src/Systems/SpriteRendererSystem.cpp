//
// Created by Sebayl on 23/01/2023.
//

#include "KappaEngine/Systems/SpriteRendererSystem.hpp"
#include "KappaEngine/GameManager.hpp"

namespace KappaEngine {
    void SpriteRendererSystem::Awake(std::shared_ptr<Entity> entity) {
        if (GameManager::isNetworked() && GameManager::GetServer()) {
            return;
        }

        std::cout << "SpriteRendererSystem Awake" << std::endl;

        auto spriteRenderer = entity->getComponent<Component::SpriteRenderer>();
        auto transform = entity->getComponent<Component::Transform>();

        if (spriteRenderer == nullptr || transform == nullptr) {
            return;
        }

        if (!transform->enabled)
            spriteRenderer->enabled = false;
        else {
            spriteRenderer->_sprite.setTextureRect(spriteRenderer->_textureRect);
        }

        if (_textureCache.contains(spriteRenderer->_texturePath)) {
            std::cout << "SpriteRendererSystem: texture " + spriteRenderer->_texturePath + " already loaded" << std::endl;
            spriteRenderer->_sprite.setTexture(_textureCache[spriteRenderer->_texturePath]);
            return;
        } else {
            std::cout << "SpriteRendererSystem: loading texture " + spriteRenderer->_texturePath << std::endl;
        }

        sf::Texture texture;
        if (!texture.loadFromFile(spriteRenderer->_texturePath)) {
            std::cout << "Error while loading texture " << spriteRenderer->_texturePath << std::endl;
            return;
        }

        _textureCache[spriteRenderer->_texturePath] = texture;
        spriteRenderer->_sprite.setTexture(_textureCache[spriteRenderer->_texturePath]);
        std::cout << "SpriteRendererSystem: added texture " + spriteRenderer->_texturePath << std::endl;
    }

    void SpriteRendererSystem::OnDestroy(std::shared_ptr<Entity> entity) {
        std::cout << "SpriteRenderSystem::OnDestroy" << std::endl;
        auto spriteRenderer = entity->getComponent<Component::SpriteRenderer>();

        if (spriteRenderer == nullptr)
            return;

        delete &spriteRenderer->_sprite;
    }

    void SpriteRendererSystem::OnRenderObject() {
        auto ents = _scene->getEntityManager()->getEntitiesWithComponent<Component::SpriteRenderer>();
        auto cams = _scene->getEntityManager()->getEntitiesWithComponent<Component::Camera>();

        for (auto &cam : cams) {
            auto camera = cam->getComponent<Component::Camera>();

            if (!camera || !camera->enabled)
                continue;

            for (auto &ent : ents) {
                auto spriteRenderer = ent->getComponent<Component::SpriteRenderer>();
                auto transform = ent->getComponent<Component::Transform>();

                for (auto it = camera->_layers.begin(); it != camera->_layers.end(); it++) {
                    if (*it == spriteRenderer->_layer && spriteRenderer->enabled) {

                        auto winSize = GameManager::GetWindow()->getSize();

                        float xRatio = (float)winSize.x / (float)camera->_size.x;
                        float yRatio = (float)winSize.y / (float)camera->_size.y;

                        float x = (transform->position.x + spriteRenderer->_position.x - camera->_position.x + ((float)camera->_size.x / 2)) * xRatio;
                        float y = (transform->position.y + spriteRenderer->_position.y - camera->_position.y + ((float)camera->_size.y / 2)) * yRatio;

                        spriteRenderer->_sprite.setPosition(x, y);
                        spriteRenderer->_sprite.setScale(transform->scale.x * ((float)winSize.x / (float)camera->_size.x), transform->scale.y * ((float)winSize.x / (float)camera->_size.x));
                        GameManager::Draw(spriteRenderer->_sprite);
                        break;
                    }
                }
            }
        }
    }
}
