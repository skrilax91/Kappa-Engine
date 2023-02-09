//
// Created by leo_b on 23/01/2023.
//

#include "KappaEngine/Systems/CollideBoxSystem.hpp"
#include "KappaEngine/Components/CollideBox.hpp"
#include "KappaEngine/Components/Transform.hpp"

namespace KappaEngine {
    void CollideBoxSystem::Update() {
        auto ents = _scene->getEntityManager()->getEntitiesWithComponent<Component::CollideBox>();

        for (auto ent : ents) {
            auto *collideBox = ent->getComponent<Component::CollideBox>();
            auto *transform = ent->getComponent<Component::Transform>();
            
            if (!transform) {
                collideBox->enabled = false;
                continue;
            }

            for (auto otherEnt : ents) {
                if (ent == otherEnt)
                    continue;
                auto *otherCollideBox = otherEnt->getComponent<Component::CollideBox>();
                if (!canCollide(collideBox, otherCollideBox))
                    continue;
                auto *otherTransform = otherEnt->getComponent<Component::Transform>();
                if (!otherTransform) {
                    otherCollideBox->enabled = false;
                    continue;
                }
                if (isColliding(collideBox, transform, otherCollideBox, otherTransform))
                    collideBox->_onCollide(otherEnt);
            }
        }
    }


    bool CollideBoxSystem::canCollide(const Component::CollideBox *collideBox, const Component::CollideBox *otherCollideBox)
    {
        if (!collideBox->enabled || !otherCollideBox->enabled)
            return false;
        for (auto tag : collideBox->_collidingTags) {
            if (tag == otherCollideBox->_tag)
                return true;
        }
        return false;
    }

    bool CollideBoxSystem::isColliding(const Component::CollideBox *collideBox, const Component::Transform *transform,
                                       const Component::CollideBox *otherCollideBox, const Component::Transform *otherTransform)
    {
        sf::Vector2f collideBoxPos = transform->position;
        sf::Vector2f otherCollideBoxPos = otherTransform->position;
        sf::Vector2f collideBoxSize = sf::Vector2f(collideBox->_width, collideBox->_height);
        sf::Vector2f otherCollideBoxSize = sf::Vector2f(otherCollideBox->_width, otherCollideBox->_height);

        sf::Vector2f collideBoxCenter = collideBoxPos + collideBoxSize / 2.0f;
        sf::Vector2f otherCollideBoxCenter = otherCollideBoxPos + otherCollideBoxSize / 2.0f;

        sf::Vector2f collideBoxHalfSize = collideBoxSize / 2.0f;
        sf::Vector2f otherCollideBoxHalfSize = otherCollideBoxSize / 2.0f;

        sf::Vector2f delta = collideBoxCenter - otherCollideBoxCenter;

        float intersectX = abs(delta.x) - (collideBoxHalfSize.x + otherCollideBoxHalfSize.x);
        float intersectY = abs(delta.y) - (collideBoxHalfSize.y + otherCollideBoxHalfSize.y);

        return (intersectX <= 0.0f && intersectY <= 0.0f);
    }
}