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
        auto rigidBody = entity->getComponent<Component::RigidBody>();

        if (collideBox == nullptr || collideBox->_notCollidingTags.empty() || !collideBox->enabled
            || transform == nullptr || !transform->enabled)
            return;

        sf::FloatRect rect = {transform->position.x, transform->position.y, collideBox->_dimensions.x, collideBox->_dimensions.y};

        auto ents = _scene->getEntityManager()->getEntitiesWithComponent<Component::CollideBox>();

        for (auto otherEntity : ents) {
            if (otherEntity == entity)
                continue;

            auto otherCollideBox = otherEntity->getComponent<Component::CollideBox>();
            auto otherTransform = otherEntity->getComponent<Component::Transform>();

            if (otherCollideBox == nullptr || !otherCollideBox->enabled || canCollide(collideBox, otherCollideBox)
                || otherTransform == nullptr || !otherTransform->enabled)
                continue;

            sf::FloatRect otherRect = {otherTransform->position.x, otherTransform->position.y, otherCollideBox->_dimensions.x, otherCollideBox->_dimensions.y};

            if (rect.intersects(otherRect)) {
                if (!findCollide(collideBox->_collided, otherCollideBox)) {
                    if (!collideBox->_onCollideEnter(entity, otherEntity) && rigidBody)
                        rollbackOnEnter(rect, otherRect, transform, rigidBody->velocity);
                    else
                        collideBox->_collided.push_back(otherCollideBox);
                } else
                    collideBox->_onCollideStay(entity, otherEntity);
            } else if (findCollide(collideBox->_collided, otherCollideBox)) {
                if (!collideBox->_onCollideExit(entity, otherEntity) && rigidBody)
                    rollbackOnExit(rect, otherRect, transform, rigidBody->velocity);
                else
                    collideBox->_collided.remove(otherCollideBox);
            }
        }
    }

    bool CollideBoxSystem::findCollide(std::list<Component::CollideBox *> &list, Component::CollideBox *collide) {
        for (auto &collideBox : list) {
            if (collideBox == collide)
                return true;
        }
        return false;
    }

    bool CollideBoxSystem::canCollide(Component::CollideBox *collideBox, Component::CollideBox *otherCollideBox) {
        for (auto &tag : collideBox->_notCollidingTags) {
            if (tag == otherCollideBox->_tag)
                return false;
        }
        return true;
    }

    void CollideBoxSystem::rollbackOnEnter(sf::FloatRect rect, sf::FloatRect otherRect,
                                        Component::Transform *transform, sf::Vector2f velocity)
    {
        float xOffset = 0;
        float yOffset = 0;

        if (velocity.x > 0)
            xOffset = otherRect.left - rect.left + rect.width;
        else if (velocity.x < 0)
            xOffset = rect.left - otherRect.left + otherRect.width;
        if (velocity.y > 0)
            yOffset = otherRect.top - rect.top + rect.height;
        else if (velocity.y < 0)
            yOffset = rect.top - otherRect.top + otherRect.height;

        if (abs(xOffset) < abs(yOffset) && xOffset != 0)
            transform->position.x += xOffset;
        else if (yOffset != 0)
            transform->position.y += yOffset;
    }

    void CollideBoxSystem::rollbackOnExit(sf::FloatRect rect, sf::FloatRect otherRect,
                                        Component::Transform *transform, sf::Vector2f velocity)
    {
        float xOffset = 0;
        float yOffset = 0;

        if (velocity.x > 0)
            xOffset = rect.left + rect.width - otherRect.left - otherRect.width;
        else if (velocity.x < 0)
            xOffset = otherRect.left - rect.left;
        if (velocity.y > 0)
            yOffset = rect.top + rect.height - otherRect.top - otherRect.height;
        else if (velocity.y < 0)
            yOffset = otherRect.top - rect.top;

        if (xOffset >= 0) {
            if (velocity.x > 0)
                transform->position.x -= xOffset;
            else if (velocity.x < 0)
                transform->position.x += xOffset;
        }
        if (yOffset >= 0) {
            if (velocity.y > 0)
                transform->position.y -= yOffset;
            else if (velocity.y < 0)
                transform->position.y += yOffset;
        }
    }
}