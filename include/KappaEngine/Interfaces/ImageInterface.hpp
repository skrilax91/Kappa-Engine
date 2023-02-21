/*
** EPITECH PROJECT, 2023
** Kappa-Engine
** File description:
** ImageInterface
*/

#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "KappaEngine/GameManager.hpp"
#include "IInterface.hpp"

namespace Interface {
    class ImageInterface : public IInterface {
        public:
            ImageInterface() = default;

            void OnRenderObject() override {

            }

            void SetImage(const std::string &imgPath) {
                _texture.loadFromFile(imgPath);
                _sprite.setTexture(_texture);
            };

        private:
            sf::Texture &_texture = sf::Texture();
            sf::Sprite _sprite = sf::Sprite();
    }
}