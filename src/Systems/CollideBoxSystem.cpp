//
// Created by leo_b on 23/01/2023.
//

#include "KappaEngine/Systems/CollideBoxSystem.hpp"
#include "KappaEngine/Components/CollideBox.hpp"
#include "KappaEngine/Components/Transform.hpp"

namespace KappaEngine {
    void CollideBoxSystem::OnCollideCheck(std::shared_ptr<Entity> entity) {
        auto collideBox = entity->getComponent<Component::CollideBox>();
        auto transform = entity->getComponent<Component::Transform>();

        if (collideBox == nullptr || collideBox->_collidingTags.empty() || !collideBox->enabled
            || transform == nullptr || !transform->enabled)
            return;

        auto ents = _scene->getEntityManager()->getEntitiesWithComponent<Component::CollideBox>();

        for (auto otherEntity : ents) {
            if (otherEntity == entity)
                continue;

            auto otherCollideBox = otherEntity->getComponent<Component::CollideBox>();

            if (otherCollideBox == nullptr || !otherCollideBox->enabled || canCollide(collideBox, otherCollideBox))
                continue;

            if (collideBox->_collideBox.intersects(otherCollideBox->_collideBox)) {
                if (!findCollide(collideBox->_collided, otherCollideBox)) {
                    enterCollideBox(entity, otherEntity, collideBox, otherCollideBox);
                    collideBox->_collided.push_back(*otherCollideBox);
                } else {
                    if (collideBox->_onCollideStay != nullptr)
                        collideBox->_onCollideStay(entity, otherEntity);
                }
            } else {
                if (findCollide(collideBox->_collided, otherCollideBox)) {
                    if (collideBox->_onCollideExit != nullptr)
                        collideBox->_onCollideExit(entity, otherEntity);
                    collideBox->_collided.remove(*otherCollideBox);
                }
            }
        }
    }

    bool CollideBoxSystem::findCollide(std::list<Component::CollideBox &> &list, Component::CollideBox *collide) {
        for (auto &collideBox : list) {
            if (&collideBox == collide)
                return true;
        }
        return false;
    }

    bool CollideBoxSystem::canCollide(Component::CollideBox *collideBox, Component::CollideBox *otherCollideBox) {
        for (auto &tag : collideBox->_collidingTags) {
            if (tag == otherCollideBox->_tag)
                return true;
        }
        return false;
    }

    void CollideBoxSystem::rollback(Component::Transform *transform, Component::RigidBody *rigidBody,
                                    Component::CollideBox *collideBox, Component::CollideBox *otherCollideBox) {
        sf::Vector2f &collideBoxPos = sf::Vector2f(collideBox->_collideBox.left, collideBox->_collideBox.top);
        sf::Vector2f &collideBoxSize = sf::Vector2f(collideBox->_collideBox.width, collideBox->_collideBox.height);
        sf::Vector2f &otherCollideBoxPos = sf::Vector2f(collideBox->_collideBox.left, collideBox->_collideBox.top);
        sf::Vector2f &otherCollideBoxSize = sf::Vector2f(collideBox->_collideBox.width, collideBox->_collideBox.height);

        float xOffset(0);
        float yOffset(0);

        if (collideBoxPos.x < otherCollideBoxPos.x)
            float xOffset = abs(collideBoxPos.x + collideBoxSize.x - otherCollideBoxPos.x);
        else if (collideBoxPos.x > otherCollideBoxPos.x)
            float xOffset = abs(collideBoxPos.x - (otherCollideBoxPos.x + otherCollideBoxSize.x));
        if (collideBoxPos.y < otherCollideBoxPos.y)
            float yOffset = abs(collideBoxPos.y + collideBoxSize.y - otherCollideBoxPos.y);
        else if (collideBoxPos.y > otherCollideBoxPos.y)
            float yOffset = abs(collideBoxPos.y - (otherCollideBoxPos.y + otherCollideBoxSize.y));

        if (xOffset < yOffset) {
            if (rigidBody->velocity.x > 0) {
                transform->position.x -= xOffset;
                collideBox->_collideBox.left -= xOffset;
            } else if (rigidBody->velocity.x < 0) {
                transform->position.x += xOffset;
                collideBox->_collideBox.left += xOffset;
            }
        } else {
            if (rigidBody->velocity.y > 0) {
                transform->position.y -= yOffset;
                collideBox->_collideBox.top -= yOffset;
            } else if (rigidBody->velocity.y < 0) {
                transform->position.y += yOffset;
                collideBox->_collideBox.top += yOffset;
            }
        }
    }

    void CollideBoxSystem::enterCollideBox(std::shared_ptr<Entity> entity, std::shared_ptr<Entity> otherEntity,
                                        Component::CollideBox *collideBox, Component::CollideBox *otherCollideBox) {
        auto transform = entity->getComponent<Component::Transform>();
        auto rigidBody = entity->getComponent<Component::RigidBody>();

        if (collideBox->_onCollideEnter) {
            if (!collideBox->_onCollideEnter(entity, otherEntity) && rigidBody)
                rollback(transform, rigidBody, collideBox, otherCollideBox);
        }
    }
}