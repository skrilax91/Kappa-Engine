/*
** EPITECH PROJECT, 2023
** Kappa-Engine
** File description:
** TriggerBox
*/

#pragma once

#include "KappaEngine/Components/IComponent.hpp"
#include "KappaEngine/Entity/Entity.hpp"
#include <functional>
#include <SFML/Graphics.hpp>

namespace Component {
    class TriggerBox : public IComponent {
        public:
            TriggerBox(const sf::Vector2f &dimensions)
                : _dimensions(dimensions) {};

            sf::Vector2f _dimensions;
            std::list<TriggerBox *> _triggered = {};
            std::function<void(std::shared_ptr<KappaEngine::Entity>, std::shared_ptr<KappaEngine::Entity>)> _onTriggerEnter =
                [](std::shared_ptr<KappaEngine::Entity> entity, std::shared_ptr<KappaEngine::Entity> other){ return; };
            std::function<void(std::shared_ptr<KappaEngine::Entity>, std::shared_ptr<KappaEngine::Entity>)> _onTriggerExit =
                [](std::shared_ptr<KappaEngine::Entity> entity, std::shared_ptr<KappaEngine::Entity> other){ return; };
            std::function<void(std::shared_ptr<KappaEngine::Entity>, std::shared_ptr<KappaEngine::Entity>)> _onTriggerStay =
                [](std::shared_ptr<KappaEngine::Entity> entity, std::shared_ptr<KappaEngine::Entity> other){ return; };
    };
}