//
// Created by Sebayl on 23/01/2023.
//

#include "KappaEngine/Systems/SpriteRendererSystem.hpp"
#include "KappaEngine/GameManager.hpp"

namespace KappaEngine {
    void SpriteRendererSystem::Awake() {
        std::cout << "SpriteRendererSystem Awake" << std::endl;

        auto ents = _scene->getEntityManager()->getEntitiesWithComponent<Component::SpriteRenderer>();

        for (auto &ent : ents) {
            auto spriteRenderer = ent->getComponent<Component::SpriteRenderer>();
            auto transform = ent->getComponent<Component::Transform>();

            if (!transform || !transform->enabled)
                spriteRenderer->enabled = false;
            else {
                spriteRenderer->_sprite.setTextureRect(spriteRenderer->_textureRect);
            }

            if (_textureCache.contains(spriteRenderer->_texturePath)) {
                std::cout << "SpriteRendererSystem: texture " + spriteRenderer->_texturePath + " already loaded" << std::endl;
                spriteRenderer->_sprite.setTexture(_textureCache[spriteRenderer->_texturePath]);
                continue;
            } else {
                std::cout << "SpriteRendererSystem: loading texture " + spriteRenderer->_texturePath << std::endl;
            }

            sf::Texture texture;
            if (!texture.loadFromFile(spriteRenderer->_texturePath)) {
                std::cerr << "Error while loading texture " << spriteRenderer->_texturePath << std::endl;
                continue;
            }

            _textureCache[spriteRenderer->_texturePath] = texture;
            spriteRenderer->_sprite.setTexture(_textureCache[spriteRenderer->_texturePath]);
            std::cout << "SpriteRendererSystem: added texture " + spriteRenderer->_texturePath << std::endl;
        }
    }

    void SpriteRendererSystem::OnDestroy(Entity *entity) {
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

                        float x = transform->position.x + spriteRenderer->_position.x - camera->_position.x + winSize.x / 2;
                        float y = transform->position.y + spriteRenderer->_position.y - camera->_position.y + winSize.y / 2;

                        //if (x < -winSize.x || x > winSize.x || y < -winSize.y || y > winSize.y)
                        //    continue;

                        spriteRenderer->_sprite.setPosition(x, y);
                        GameManager::Draw(spriteRenderer->_sprite);
                        break;
                    }
                }
            }
        }
    }
}
