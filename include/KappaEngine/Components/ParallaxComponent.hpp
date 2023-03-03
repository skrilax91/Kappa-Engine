/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-dylan.akpinar
** File description:
** ParalaxComponent
*/

#pragma once

#include <SFML/System.hpp>

#include "KappaEngine/Components/IComponent.hpp"

namespace Component {
    class ParallaxComponent : public Component::IComponent {
        public:
            ParallaxComponent(sf::Vector2i offset, sf::Vector2i min, sf::Vector2i max)
                : _offset(offset), _min(min), _max(max) {};

            sf::Vector2i _offset;
            sf::Vector2i _min;
            sf::Vector2i _max;
    };
}