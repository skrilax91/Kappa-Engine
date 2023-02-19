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

    /**
     * @brief The SpriteRenderer class
     * @def This class is used to create a sprite renderer
     * @def The position is the relative position of the sprite
     * @def The texturePath is the path to the texture
     * @def The textureRect is the rectangle of the texture to use
     * @def The layer is the layer to render the sprite
     */
    class SpriteRenderer : public IComponent {
        public:
            SpriteRenderer(struct coord2d position): _position(position) {};
            SpriteRenderer(struct coord2d position, std::string texturePath, sf::IntRect textureRect = sf::IntRect(), std::string layer = "default"):
                _position(position),
                _texturePath(std::move(texturePath)),
                _textureRect(textureRect),
                _layer(std::move(layer)) {};

            /**
             * @brief Set the position of the component
             * @param position The position
             * @return The component
             */
            SpriteRenderer *SetPosition(struct coord2d position) { _position = position; return this; }

            /**
             * @brief Set the texture path of the component
             * @param texturePath The texture path
             * @return The component
             */
            SpriteRenderer *SetTexturePath(std::string texturePath) { _texturePath = texturePath; return this; }

            /**
             * @brief Set the sprite of the component
             * @param sprite The sprite
             * @return The component
             */
            SpriteRenderer *SetSprite(sf::Sprite sprite) { _sprite = sprite; return this; }

            /**
             * @brief Set the texture rect of the component
             * @param textureRect The texture rect
             * @return The component
             */
            SpriteRenderer *SetTextureRect(sf::IntRect textureRect) { _textureRect = textureRect; return this; }

            /**
             * @brief Set the layer of the component
             * @param layer The layer
             * @return The component
             */
            SpriteRenderer *SetLayer(std::string layer) { _layer = std::move(layer); return this; }

            struct coord2d _position;
            std::string _texturePath;
            sf::Sprite _sprite = sf::Sprite();
            sf::IntRect _textureRect;
            std::string _layer;
    };
}

#endif //R_TYPE_SERVER_SPRITERENDER_HPP
