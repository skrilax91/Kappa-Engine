//
// Created by Sebayl on 23/01/2023.
//

#include "KappaEngine/Systems/SpriteRendererSystem.hpp"


namespace KappaEngine {
    void SpriteRendererSystem::Awake() {
        auto ents = _scene->getEntityManager()->getEntitiesWithComponent<Component::SpriteRenderer>();

        for (auto &ent : ents) {
            auto spriteRenderer = ent->getComponent<Component::SpriteRenderer>();
            auto transform = ent->getComponent<Component::Transform>();

            if (!transform || !transform->enabled)
                spriteRenderer->enabled = false;
            else {
                spriteRenderer->_sprite.setPosition(
                    transform->position.x + spriteRenderer->_position.x,
                    transform->position.y + spriteRenderer->_position.y);
            }

            if (_textureCache.contains(spriteRenderer->_texturePath)) {
                spriteRenderer->_sprite.setTexture(_textureCache[spriteRenderer->_texturePath]);
                continue;
            }

            sf::Texture texture;
            if (!texture.loadFromFile(spriteRenderer->_texturePath)) {
                std::cerr << "Error while loading texture " << spriteRenderer->_texturePath << std::endl;
                continue;
            }

            _textureCache[spriteRenderer->_texturePath] = texture;
            spriteRenderer->_sprite.setTexture(_textureCache[spriteRenderer->_texturePath]);
        }
    }

    void SpriteRendererSystem::FixedUpdate() {
        auto ents = _scene->getEntityManager()->getEntitiesWithComponent<Component::SpriteRenderer>();
        auto cams = _scene->getEntityManager()->getEntitiesWithComponent<Component::Camera>();

        for (auto &camera : cams) {
            auto &cam = *camera->getComponent<Component::Camera>();
            if (cam.enabled) {

                for (auto &ent : ents) {
                    auto spriteRenderer = ent->getComponent<Component::SpriteRenderer>();

                    for (auto it = cam._layers.begin(); it != cam._layers.end(); it++) {
                        if (*it == spriteRenderer->_layer && spriteRenderer->enabled) {
                            auto sTransform = ent->getComponent<Component::Transform>();

                            if (!sTransform || !sTransform->enabled)
                                spriteRenderer->enabled = false;
                            else {

                                auto &cTransform = *camera->getComponent<Component::Transform>();
                                auto winDim = _scene->getWindow()->getSize();

                                float spriteX = sTransform->position.x + spriteRenderer->_position.x
                                                - (cTransform.position.x + cam._position.x
                                                - winDim.x / 2);

                                float spriteY = sTransform->position.y + spriteRenderer->_position.y
                                                - (cTransform.position.y + cam._position.y
                                                - winDim.y / 2);

                                spriteRenderer->_sprite.setPosition({spriteX, spriteY});
                            }
                            break;
                        }
                    }
                }
                break;
            }
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
            auto &camera = *cam->getComponent<Component::Camera>();
            if (camera.enabled) {

                for (auto &ent : ents) {
                    auto spriteRenderer = ent->getComponent<Component::SpriteRenderer>();

                    for (auto it = camera._layers.begin(); it != camera._layers.end(); it++) {
                        if (*it == spriteRenderer->_layer && spriteRenderer->enabled) {
                            _scene->getWindow()->draw(spriteRenderer->_sprite);
                            break;
                        }
                    }
                }

                break;
            }
        }
    }
}