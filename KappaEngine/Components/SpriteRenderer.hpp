//
// Created by Sebayl on 23/01/2023.
//

#ifndef R_TYPE_SERVER_SPRITERENDER_HPP
#define R_TYPE_SERVER_SPRITERENDER_HPP

#include <string>
#include <cassert>
#include <SFML/Graphics.hpp>
#include <utility>
#include "IComponent.hpp"
#include "Transform.hpp"

struct coord2d;

struct coord2d {
    float x;
    float y;
};

namespace Component {
    class SpriteRenderer : public IComponent {
        public:
            SpriteRenderer(coord2d position, std::string texturePath, sf::IntRect textureRect):
                _position(position),
                _texturePath(std::move(texturePath)),
                _textureRect(textureRect) {};

            struct coord2d _position;
            std::string _texturePath;
            sf::Sprite _sprite = sf::Sprite();
            sf::IntRect _textureRect;
            coord2d _position;
    };
}

#endif //R_TYPE_SERVER_SPRITERENDER_HPP
