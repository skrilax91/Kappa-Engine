/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-dylan.akpinar
** File description:
** ParalaxSystem
*/

#include "KappaEngine/Components/ParallaxComponent.hpp"
#include "KappaEngine/Systems/ParallaxSystem.hpp"

namespace KappaEngine {
    void ParallaxSystem::FixedUpdate() {
        auto entities = _scene->getEntityManager()->getEntitiesWithComponent<Component::ParallaxComponent>();

        for (auto ent: entities) {
            auto parallax = ent->getComponent<Component::ParallaxComponent>();
            auto spRenderer = ent->getComponent<Component::SpriteRenderer>();

            if (!spRenderer) {
                parallax->enabled = false;
                continue;
            }

            spRenderer->_textureRect.left += parallax->_offset.x;
            spRenderer->_textureRect.top += parallax->_offset.y;
            if (spRenderer->_textureRect.left > parallax->_max.x)
                spRenderer->_textureRect.left = parallax->_min.x;
            else if (spRenderer->_textureRect.left < parallax->_min.x)
                spRenderer->_textureRect.left = parallax->_max.x;
            if (spRenderer->_textureRect.top > parallax->_max.y)
                spRenderer->_textureRect.top = parallax->_min.y;
            else if (spRenderer->_textureRect.top < parallax->_min.y)
                spRenderer->_textureRect.top = parallax->_max.y;

            spRenderer->_sprite.setTextureRect(spRenderer->_textureRect);
        }
    }
}