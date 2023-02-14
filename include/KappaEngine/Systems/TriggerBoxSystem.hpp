/*
** EPITECH PROJECT, 2023
** Kappa-Engine
** File description:
** TriggerBoxSystem
*/

#pragma once

#include "KappaEngine/Systems/ISystem.hpp"

namespace KappaEngine {
    class TriggerBoxSystem : public ISystem {
        public:
            TriggerBoxSystem(Scene *scene) : ISystem(scene) {};

        private:
            void OnTrigger(std::shared_ptr<Entity> entity);
            bool findTrigger(std::list<Component::TriggerBox &> &list, Component::TriggerBox *trigger);
    };
}
