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

            void checkTrigger(std::shared_ptr<Entity> entity, sf::Vector2f oldPos, sf::Vector2f newPos);
    };
}
