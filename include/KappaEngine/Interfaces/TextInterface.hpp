//
// Created by leo_b on 01/02/2023.
//

#pragma once

#include <array>
#include <functional>
#include <SFML/Graphics.hpp>

#include "KappaEngine/GameManager.hpp"
#include "KappaEngine/Interfaces/Utils.hpp"

namespace Interface {
    class TextInterface: public IInterface {
        public:
            TextInterface(IPosition position, std::string text);
            TextInterface() = delete;
            TextInterface(const TextInterface &) = delete;

            void OnRenderInterface(IPosition parent) override;

            void setColor(sf::Color color);
            void setSize(unsigned int size);
            void setText(std::string text);

            IPosition _position;
            sf::Font _font;
            sf::Text _text;
    };
}
