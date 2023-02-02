//
// Created by Sebayl on 02/02/2023.
//

#ifndef KAPPA_ENGINE_TEXT_HPP
#define KAPPA_ENGINE_TEXT_HPP

#include "KappaEngine/Interfaces/IInterface.hpp"

namespace Interface {
    class TextComponent : public IInterface {
        public:
            TextComponent() = default;

            sf::Vector2f position = {0, 0};
            sf::Vector2f rotation = {0, 0};
            unsigned int characterSize = 11;
            sf::Text::Style style = sf::Text::Style::Regular;
            float lineSpacing = 1;
            float letterSpacing = 1;
            float outlineThickness = 0;

            sf::Color outline = sf::Color::Black;
            sf::Color fill = sf::Color::White;

            sf::Font font = sf::Font();
            sf::Text text = sf::Text();

            std::string str = "";

            Anchor anchor = Anchor::TOP_LEFT;

            void draw() override;
    };

} // Interface

#endif //KAPPA_ENGINE_TEXT_HPP
