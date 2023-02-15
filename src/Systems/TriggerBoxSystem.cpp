/*
** EPITECH PROJECT, 2023
** Kappa-Engine
** File description:
** TriggerBoxSystem
*/

#include "KappaEngine/Systems/TriggerBoxSystem.hpp"
#include "KappaEngine/Components/Transform.hpp"

namespace KappaEngine {
    void TriggerBoxSystem::OnTriggerCheck(std::shared_ptr<Entity> entity)
    {
        auto trigger = entity->getComponent<Component::TriggerBox>();

        if (trigger == nullptr)
            return;
        else if (!trigger->enabled)
            return;

        auto ents = _scene->getEntityManager()->getEntitiesWithComponent<Component::TriggerBox>();

        for (auto ent: ents) {
            auto otherTrigger = ent->getComponent<Component::TriggerBox>();

            if (ent == entity)
                continue;
            if (otherTrigger == nullptr)
                continue;
            else if (!otherTrigger->enabled)
                continue;

            if (trigger->_triggerBox.intersects(otherTrigger->_triggerBox)) {
                if (!findTrigger(trigger->_triggered, otherTrigger)) {
                    trigger->_triggered.push_back(*otherTrigger);
                    if (trigger->_onTriggerEnter)
                        trigger->_onTriggerEnter(entity, ent);
                } else if (trigger->_onTriggerStay)
                    trigger->_onTriggerStay(entity, ent);
            } else if (findTrigger(trigger->_triggered, otherTrigger)) {
                trigger->_triggered.remove(*otherTrigger);
                if (trigger->_onTriggerExit)
                    trigger->_onTriggerExit(entity, ent);
            }
        }
    }

    bool TriggerBoxSystem::findTrigger(std::list<Component::TriggerBox &> &list, Component::TriggerBox *trigger)
    {
        for (auto &trig: list) {
            if (&trig == trigger)
                return true;
        }
        return false;
    }
}
