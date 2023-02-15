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

        auto ents = _scene->getEntityManager()->getEntitiesWithComponent<Component::CollideBox>();

        for (auto otherEntity : ents) {
            if (otherEntity == entity)
                continue;

            auto otherCollideBox = otherEntity->getComponent<Component::CollideBox>();

            if (otherCollideBox == nullptr || !otherCollideBox->enabled || canCollide(collideBox, otherCollideBox))
                continue;

            if (collideBox->_collideBox.intersects(otherCollideBox->_collideBox)) {
                if (!findCollide(collideBox->_collided, otherCollideBox)) {
                    enterCollideBox(entity, otherEntity, transform, rigidBody, collideBox, otherCollideBox);
                } else {
                    if (collideBox->_onCollideStay != nullptr)
                        collideBox->_onCollideStay(entity, otherEntity);
                }
            } else if (findCollide(collideBox->_collided, otherCollideBox))
                exitCollideBox(entity, otherEntity, transform, rigidBody, collideBox, otherCollideBox);
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
        for (auto &tag : collideBox->_notCollidingTags) {
            if (tag == otherCollideBox->_tag)
                return false;
        }
        return true;
    }

    void CollideBoxSystem::rollback(Component::Transform *transform, Component::RigidBody *rigidBody,
                                    Component::CollideBox *collideBox, Component::CollideBox *otherCollideBox, bool enter) {
        float xOffset(0);
        float yOffset(0);

        if (collideBox->_collideBox.left < otherCollideBox->_collideBox.left)
            xOffset = abs(collideBox->_collideBox.left + collideBox->_collideBox.width - otherCollideBox->_collideBox.left);
        else
            xOffset = abs(collideBox->_collideBox.left - (otherCollideBox->_collideBox.left + otherCollideBox->_collideBox.width));
        if (collideBox->_collideBox.top < otherCollideBox->_collideBox.top)
            yOffset = abs(collideBox->_collideBox.top + collideBox->_collideBox.height - otherCollideBox->_collideBox.top);
        else
            yOffset = abs(collideBox->_collideBox.top - (otherCollideBox->_collideBox.top + otherCollideBox->_collideBox.height));

        if (!enter) {
            xOffset = abs(xOffset - collideBox->_collideBox.width);
            yOffset = abs(yOffset - collideBox->_collideBox.height);
        }

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
                                        Component::Transform *transform, Component::RigidBody *rigidBody,
                                        Component::CollideBox *collideBox, Component::CollideBox *otherCollideBox)
    {
        if (collideBox->_onCollideEnter) {
            if (!collideBox->_onCollideEnter(entity, otherEntity) && rigidBody)
                rollback(transform, rigidBody, collideBox, otherCollideBox, true);
            else
                collideBox->_collided.push_back(*otherCollideBox);
        } else if (rigidBody)
            rollback(transform, rigidBody, collideBox, otherCollideBox, true);
    }

    void CollideBoxSystem::exitCollideBox(std::shared_ptr<Entity> entity, std::shared_ptr<Entity> otherEntity,
                                        Component::Transform *transform, Component::RigidBody *rigidBody,
                                        Component::CollideBox *collideBox, Component::CollideBox *otherCollideBox)
    {
        if (collideBox->_onCollideExit)
            if (collideBox->_onCollideExit(entity, otherEntity))
                collideBox->_collided.remove(*otherCollideBox);
            else if (rigidBody)
                rollback(transform, rigidBody, collideBox, otherCollideBox, false);
    }
}