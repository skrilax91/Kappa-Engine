//
// Created by leo_b on 23/01/2023.
//

#include "KappaEngine/Systems/CollideBoxSystem.hpp"
#include "KappaEngine/Components/CollideBox.hpp"
#include "KappaEngine/Components/Transform.hpp"
#include "KappaEngine/GameManager.hpp"
#include "KappaEngine/Components/NetworkComponent.hpp"

namespace KappaEngine {
    void CollideBoxSystem::OnCollideCheck(std::shared_ptr<Entity> entity) {

        if (GameManager::isNetworked()) {
            auto net = entity->getComponent<Component::NetworkComponent>();

            if (net && net->ownerId != 0 && GameManager::GetServer())
                return;
            else if (net && GameManager::GetClient() && net->ownerId != GameManager::GetClient()->GetID())
                return;
        }

        auto collideBox = entity->getComponent<Component::CollideBox>();
        auto transform = entity->getComponent<Component::Transform>();
        auto rigidBody = entity->getComponent<Component::RigidBody>();

        if (collideBox == nullptr || !collideBox->enabled || transform == nullptr || !transform->enabled)
            return;

        sf::FloatRect rect = {transform->position.x, transform->position.y,
                              collideBox->_dimensions.x * transform->scale.x, collideBox->_dimensions.y * transform->scale.y};

        auto entities = _scene->getEntityManager()->getEntitiesWithComponent<Component::CollideBox>();

        for (auto otherEntity : entities) {
            if (otherEntity == entity)
                continue;

            std::cout << "Checking collision with Entity " << otherEntity->getId() << "..." << std::endl;

            auto otherCollideBox = otherEntity->getComponent<Component::CollideBox>();
            auto otherTransform = otherEntity->getComponent<Component::Transform>();

            if (otherCollideBox == nullptr || !otherCollideBox->enabled || !canCollide(collideBox, otherCollideBox)
                || otherTransform == nullptr || !otherTransform->enabled)
                continue;

            sf::FloatRect otherRect = {otherTransform->position.x, otherTransform->position.y,
                                       otherCollideBox->_dimensions.x * otherTransform->scale.x, otherCollideBox->_dimensions.y * otherTransform->scale.y};

            std::cout << entity->getId() << " collideBox: " << rect.left << ", " << rect.top << ", " << rect.width << ", " << rect.height << std::endl;
            std::cout << otherEntity->getId() << " collideBox: " << otherRect.left << ", " << otherRect.top << ", " << otherRect.width << ", " << otherRect.height << std::endl;

            if (rect.intersects(otherRect)) {
                std::cout << "Collision detected !" << std::endl;
                if (!findCollide(collideBox->_collided, otherCollideBox)) {
                    std::cout << "New collision !" << std::endl;
                    if (!collideBox->_onCollideEnter(entity, otherEntity) && rigidBody)
                        rollbackOnEnter(rect, otherRect, transform, rigidBody->velocity);
                    else
                        collideBox->_collided.push_back(otherCollideBox);
                } else
                    collideBox->_onCollideStay(entity, otherEntity);
            } else if (findCollide(collideBox->_collided, otherCollideBox)) {
                std::cout << "No collision anymore !" << std::endl;
                if (!collideBox->_onCollideExit(entity, otherEntity) && rigidBody)
                    rollbackOnExit(rect, otherRect, transform, rigidBody->velocity);
                else
                    collideBox->_collided.remove(otherCollideBox);
            }
        }
    }

    bool CollideBoxSystem::findCollide(std::list<Component::CollideBox *> &list, Component::CollideBox *collide) {
        std::cout << "Looking for existing collision..." << std::endl;
        for (auto &collideBox : list) {
            if (collideBox == collide)
                return true;
        }
        std::cout << "No collision found !" << std::endl;
        return false;
    }

    bool CollideBoxSystem::canCollide(Component::CollideBox *collideBox, Component::CollideBox *otherCollideBox) {
        std::cout << "Checking if collision is allowed..." << std::endl;
        for (auto &tag : collideBox->_notCollidingTags) {
            if (tag == otherCollideBox->_tag)
                return false;
        }
        std::cout << "Collision allowed !" << std::endl;
        return true;
    }

    void CollideBoxSystem::rollbackOnEnter(sf::FloatRect rect, sf::FloatRect otherRect,
                                        Component::Transform *transform, sf::Vector2f velocity)
    {
        float xOffset = 0;
        float yOffset = 0;

        std::cout << "Rollback on enter !" << std::endl;

        if (velocity.x > 0)
            xOffset = otherRect.left - (rect.left + rect.width);
        else if (velocity.x < 0)
            xOffset = rect.left - (otherRect.left + otherRect.width);
        if (velocity.y > 0)
            yOffset = otherRect.top - (rect.top + rect.height);
        else if (velocity.y < 0)
            yOffset = rect.top - (otherRect.top + otherRect.height);

        std::cout << "Offsets: " << xOffset << ", " << yOffset << std::endl;
        std::cout << "Position: " << transform->position.x << ", " << transform->position.y << std::endl;

        if (abs(xOffset) < abs(yOffset) && velocity.y == 0)
            transform->position.x += xOffset;
        else if (abs(yOffset) < abs(xOffset) || velocity.x == 0)
            transform->position.y += yOffset;

        std::cout << "New position: " << transform->position.x << ", " << transform->position.y << std::endl;
    }

    void CollideBoxSystem::rollbackOnExit(sf::FloatRect rect, sf::FloatRect otherRect,
                                        Component::Transform *transform, sf::Vector2f velocity)
    {
        float xOffset = 0;
        float yOffset = 0;

        std::cout << "Rollback on exit !" << std::endl;

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