/*
** EPITECH PROJECT, 2023
** Kappa-Engine
** File description:
** TriggerBoxSystem
*/

#include "KappaEngine/Systems/TriggerBoxSystem.hpp"
#include "KappaEngine/Components/Transform.hpp"
#include "KappaEngine/Components/TriggerBox.hpp"

namespace KappaEngine {
    void TriggerBoxSystem::checkTrigger(std::shared_ptr<Entity> entity, sf::Vector2f oldPos, sf::Vector2f newPos)
    {
        auto trigger = entity->getComponent<Component::TriggerBox>();
        auto transform = entity->getComponent<Component::Transform>();

        if (trigger == nullptr || transform == nullptr)
            return;
        else if (!trigger->enabled || !transform->enabled)
            return;

        auto ents = _scene->getEntityManager()->getEntitiesWithComponent<Component::TriggerBox>();

        sf::FloatRect oldBox = trigger->_triggerBox;
        trigger->_triggerBox.left = newPos.x;
        trigger->_triggerBox.top = newPos.y;

        for (auto ent: ents) {
            auto otherTrigger = ent->getComponent<Component::TriggerBox>();
            auto otherTransform = ent->getComponent<Component::Transform>();

            if (ent == entity)
                continue;
            if (otherTrigger == nullptr || otherTransform == nullptr)
                continue;
            else if (!otherTrigger->enabled || !otherTransform->enabled)
                continue;

            if (!oldBox.intersects(otherTrigger->_triggerBox) && trigger->_triggerBox.intersects(otherTrigger->_triggerBox)) {
                if (trigger->_onEnter)
                    trigger->_onEnter(entity, ent);
                if (otherTrigger->_onEnter)
                    otherTrigger->_onEnter(ent, entity);
            } else if (oldBox.intersects(otherTrigger->_triggerBox) && trigger->_triggerBox.intersects(otherTrigger->_triggerBox)) {
                if (trigger->_onStay)
                    trigger->_onStay(entity, ent);
                if (otherTrigger->_onStay)
                    otherTrigger->_onStay(ent, entity);
            } else if (oldBox.intersects(otherTrigger->_triggerBox) && !trigger->_triggerBox.intersects(otherTrigger->_triggerBox)) {
                if (trigger->_onExit)
                    trigger->_onExit(entity, ent);
                if (otherTrigger->_onExit)
                    otherTrigger->_onExit(ent, entity);
            }
        }
    }
}
