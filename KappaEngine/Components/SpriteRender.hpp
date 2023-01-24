//
// Created by Sebayl on 23/01/2023.
//

#ifndef R_TYPE_SERVER_SPRITERENDER_HPP
#define R_TYPE_SERVER_SPRITERENDER_HPP

#include <string>
#include <cassert>
#include <SFML/Graphics>
#include "IComponent.hpp"

struct intRect {
    int x;
    int y;
    int width;
    int height;
};

namespace Component {
    class SpriteRender : IComponent {
        public:
            SpriteRender(std::string texturePath, struct intRect)
            {
                assert(_texture.loadFromFile(texturePath));
                _sprite.setTexture(_texture);
                _sprite.setTextureRect(sf::IntRect(intRect.x, intRect.y, intRect.width, intRect.height));
            }

            ~SpriteRender()
            {
                _texture.destroy();
                _sprite.destroy();
            }

            sf::Texture _texture;
            sf::Sprite _sprite;
    };
}

#endif //R_TYPE_SERVER_SPRITERENDER_HPP
