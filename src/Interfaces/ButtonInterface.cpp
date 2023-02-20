/*
** EPITECH PROJECT, 2023
** Kappa-Engine
** File description:
** ButtonInterface
*/

#include "KappaEngine/Interfaces/ButtonInterface.hpp"

namespace Interface {
    void ButtonInterface::Awake()
    {

    }

    void ButtonInterface::OnRenderObject()
    {
        if (!enabled)
            return;
        if (_sprite.getTexture() != &_texture)
            _sprite.setTexture(_texture);
        sf::Vector2f pos = sf::Vector2f(_bounds.left, _bounds.top);
        if (pos != _sprite.getPosition())
            _sprite.setPosition(pos);
    }
}
