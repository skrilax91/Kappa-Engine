/*
** EPITECH PROJECT, 2023
** Kappa-Engine
** File description:
** TriggerBoxSystem
*/

#include "KappaEngine/Systems/TriggerBoxSystem.hpp"
#include "KappaEngine/Components/Transform.hpp"
#include "KappaEngine/Components/NetworkComponent.hpp"
#include "KappaEngine/GameManager.hpp"

namespace KappaEngine {
    void TriggerBoxSystem::OnTriggerCheck(std::shared_ptr<Entity> entity)
    {
        if (GameManager::isNetworked()) {
            auto net = entity->getComponent<Component::NetworkComponent>();

            if (net && net->ownerId != 0 && GameManager::GetServer())
                return;
            else if (net && GameManager::GetClient() && net->ownerId != GameManager::GetClient()->GetID())
                return;
        }

        auto trigger = entity->getComponent<Component::TriggerBox>();
        auto transform = entity->getComponent<Component::Transform>();

        if (trigger == nullptr || transform == nullptr || !trigger->enabled || !transform->enabled)
            return;

        sf::FloatRect rect = {transform->position.x, transform->position.y,
                              trigger->_dimensions.x * transform->scale.x, trigger->_dimensions.y * transform->scale.y};

        auto ents = _scene->getEntityManager()->getEntitiesWithComponent<Component::TriggerBox>();

        for (const auto& ent: ents) {
            auto otherTrigger = ent->getComponent<Component::TriggerBox>();

            if (ent == entity || otherTrigger == nullptr || !otherTrigger->enabled)
                continue;

            auto otherTransform = ent->getComponent<Component::Transform>();

            if (otherTrigger == nullptr || otherTransform == nullptr)
                continue;
            else if (!otherTrigger->enabled || !otherTransform->enabled)
                continue;

            sf::FloatRect otherRect = {otherTransform->position.x, otherTransform->position.y,
                                       otherTrigger->_dimensions.x * otherTransform->scale.x, otherTrigger->_dimensions.y * otherTransform->scale.y};

            if (rect.intersects(otherRect)) {
                if (!findTrigger(trigger->_triggered, otherTrigger)) {
                    trigger->_onTriggerEnter(entity, ent);
                    trigger->_triggered.push_back(otherTrigger);
                } else
                    trigger->_onTriggerStay(entity, ent);
            } else if (findTrigger(trigger->_triggered, otherTrigger)) {
                trigger->_onTriggerExit(entity, ent);
                trigger->_triggered.remove(otherTrigger);
            }
        }
    }

    bool TriggerBoxSystem::findTrigger(std::list<Component::TriggerBox *> &list, Component::TriggerBox *trigger)
    {
        for (auto &trig: list) {
            if (trig == trigger)
                return true;
        }
        return false;
    }
}
