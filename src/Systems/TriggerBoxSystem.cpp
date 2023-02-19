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
    void TriggerBoxSystem::OnTriggerCheck(std::shared_ptr<Entity> entity)
    {
        auto trigger = entity->getComponent<Component::TriggerBox>();
        auto transform = entity->getComponent<Component::Transform>();

        if (trigger == nullptr || transform == nullptr || !trigger->enabled || !transform->enabled)
            return;

        auto ents = _scene->getEntityManager()->getEntitiesWithComponent<Component::TriggerBox>();

        for (const auto& ent: ents) {
            auto otherTrigger = ent->getComponent<Component::TriggerBox>();
            auto otherTransform = ent->getComponent<Component::Transform>();

            if (ent == entity || otherTrigger == nullptr || otherTransform == nullptr || !otherTrigger->enabled || !otherTransform->enabled)
                continue;

            if (trigger->_triggerBox.intersects(otherTrigger->_triggerBox)) {
                if (!findTrigger(trigger->_triggered, otherTrigger)) {
                    trigger->_triggered.push_back(otherTrigger);
                    if (trigger->_onTriggerEnter)
                        trigger->_onTriggerEnter(entity, ent);
                } else if (trigger->_onTriggerStay)
                    trigger->_onTriggerStay(entity, ent);
            } else if (findTrigger(trigger->_triggered, otherTrigger)) {
                trigger->_triggered.remove(otherTrigger);
                if (trigger->_onTriggerExit)
                    trigger->_onTriggerExit(entity, ent);
            }
        }
    }

    bool TriggerBoxSystem::findTrigger(std::list<Component::TriggerBox *> list, Component::TriggerBox *trigger)
    {
        for (auto trig: list) {
            if (trig == trigger)
                return true;
        }
        return false;
    }
}
