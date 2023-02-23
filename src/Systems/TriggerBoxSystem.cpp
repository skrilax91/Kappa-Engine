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
        auto transform = entity->getComponent<Component::Transform>();

        if (trigger == nullptr || transform == nullptr)
            return;
        else if (!trigger->enabled || !transform->enabled)
            return;

        sf::FloatRect rect = {transform->position.x, transform->position.y, trigger->_dimensions.x, trigger->_dimensions.y};

        auto ents = _scene->getEntityManager()->getEntitiesWithComponent<Component::TriggerBox>();

        for (auto ent: ents) {
            auto otherTrigger = ent->getComponent<Component::TriggerBox>();

            if (ent == entity)
                continue;

            auto otherTransform = ent->getComponent<Component::Transform>();

            if (otherTrigger == nullptr || otherTransform == nullptr)
                continue;
            else if (!otherTrigger->enabled || !otherTransform->enabled)
                continue;

            sf::FloatRect otherRect = {otherTransform->position.x, otherTransform->position.y, otherTrigger->_dimensions.x, otherTrigger->_dimensions.y};

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
