//
// Created by Sebayl on 23/01/2023.
//

#ifndef R_TYPE_SERVER_SPRITERENDER_HPP
#define R_TYPE_SERVER_SPRITERENDER_HPP

#include <SFML/Graphics.hpp>
#include <cassert>
#include <string>
#include <utility>

#include "IComponent.hpp"
#include "Transform.hpp"

namespace Component {
    class SpriteRenderer : public IComponent {
        public:
            SpriteRenderer(struct coord2d position, std::string texturePath, sf::IntRect textureRect = sf::IntRect(), std::string layer = "default"):
                _position(position),
                _texturePath(std::move(texturePath)),
                _textureRect(textureRect),
                _layer(std::move(layer)) {};

            struct coord2d _position;
            std::string _texturePath;
            sf::Sprite _sprite = sf::Sprite();
            sf::IntRect _textureRect;
            std::string _layer;
    };
}

#endif //R_TYPE_SERVER_SPRITERENDER_HPP