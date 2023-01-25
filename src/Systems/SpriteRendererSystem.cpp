//
// Created by Sebayl on 23/01/2023.
//

#include "KappaEngine/Systems/SpriteRendererSystem.hpp"

namespace KappaEngine {
    void SpriteRendererSystem::Awake() {
        auto ents = _scene->getEntityManager()->getEntitiesWithComponent<Component::SpriteRenderer>();

        for (auto &ent : ents) {
            auto spriteRenderer = ent->getComponent<Component::SpriteRenderer>();

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

    void SpriteRendererSystem::Update() {
        auto ents = _scene->getEntityManager()->getEntitiesWithComponent<Component::SpriteRenderer>();

        for (auto &ent : ents) {
            auto sR_Comp = ent->getComponent<Component::SpriteRenderer>();
            if (sR_Comp->enabled) {
                _scene->getWindow()->draw(sR_Comp->_sprite);
            }
        }
    }

    void SpriteRendererSystem::OnDestroy(Entity *entity) {
        std::cout << "SprteRenderSystem::OnDestroy" << std::endl;
        auto spriteRenderer = entity->getComponent<Component::SpriteRenderer>();

        if (spriteRenderer == nullptr)
            return;

        delete &spriteRenderer->_sprite;
    }
}