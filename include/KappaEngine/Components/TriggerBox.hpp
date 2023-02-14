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
            TriggerBox(const sf::FloatRect &triggerBox,
                std::function<void(std::shared_ptr<KappaEngine::Entity>, std::shared_ptr<KappaEngine::Entity>)> onEnter = nullptr,
                std::function<void(std::shared_ptr<KappaEngine::Entity>, std::shared_ptr<KappaEngine::Entity>)> onExit = nullptr,
                std::function<void(std::shared_ptr<KappaEngine::Entity>, std::shared_ptr<KappaEngine::Entity>)> onStay = nullptr)
                : _triggerBox(triggerBox), _onEnter(onEnter), _onExit(onExit), _onStay(onStay) {};

            sf::FloatRect _triggerBox;
            std::function<void(std::shared_ptr<KappaEngine::Entity>, std::shared_ptr<KappaEngine::Entity>)> _onEnter;
            std::function<void(std::shared_ptr<KappaEngine::Entity>, std::shared_ptr<KappaEngine::Entity>)> _onExit;
            std::function<void(std::shared_ptr<KappaEngine::Entity>, std::shared_ptr<KappaEngine::Entity>)> _onStay;
    };
}