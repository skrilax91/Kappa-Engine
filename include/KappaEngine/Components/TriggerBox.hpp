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
                std::function<void(std::shared_ptr<KappaEngine::Entity>, std::shared_ptr<KappaEngine::Entity>)> onTriggerEnter = nullptr,
                std::function<void(std::shared_ptr<KappaEngine::Entity>, std::shared_ptr<KappaEngine::Entity>)> onTriggerExit = nullptr,
                std::function<void(std::shared_ptr<KappaEngine::Entity>, std::shared_ptr<KappaEngine::Entity>)> onTriggerStay = nullptr)
                : _triggerBox(triggerBox), _onTriggerEnter(onTriggerEnter), _onTriggerExit(onTriggerExit), _onTriggerStay(onTriggerStay) {};

            sf::FloatRect _triggerBox;
            std::list<TriggerBox &> _triggered = {};
            std::function<void(std::shared_ptr<KappaEngine::Entity>, std::shared_ptr<KappaEngine::Entity>)> _onTriggerEnter;
            std::function<void(std::shared_ptr<KappaEngine::Entity>, std::shared_ptr<KappaEngine::Entity>)> _onTriggerExit;
            std::function<void(std::shared_ptr<KappaEngine::Entity>, std::shared_ptr<KappaEngine::Entity>)> _onTriggerStay;
    };
}