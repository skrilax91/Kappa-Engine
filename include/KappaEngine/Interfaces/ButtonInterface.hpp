//
// Created by leo_b on 01/02/2023.
//

#ifndef KAPPA_ENGINE_BUTTONINTERFACE_HPP
#define KAPPA_ENGINE_BUTTONINTERFACE_HPP

#include <functional>
#include <SFML/Graphics.hpp>

#include "KappaEngine/Interfaces/IInterface.hpp"

namespace Interface {
    class ButtonInterface: public IInterface {
        public:
            ButtonInterface();

            void Awake() override;
            void OnRenderObject() override;

            void setGlobalBounds(sf::FloatRect bounds) { _bounds = bounds; };
            void setAnchor(Anchor anchor) { _anchor = anchor; };

            void setTexture(sf::Texture &texture) { _texture = texture; };
            void setColor(sf::Color color) { _color = color; };

            void setText(std::string str) { _str = str; };
            void setTextPos(sf::Vector2f pos) { _textPos = pos; };
            void setCharSize(unsigned int charSize) { _charSize = charSize; };
            void setTextColor(sf::Color color) { _textColor = color; };
            void setFont(sf::Font &font) { _font = font; };

            void setOnClick(std::function<void()> onClick) { _onClick = onClick; };
            void setOnRelease(std::function<void()> onRelease) { _onRelease = onRelease; };

        private:
            sf::FloatRect _bounds = {};
            Anchor _anchor = Anchor::TOP_LEFT;

            sf::Sprite _sprite = sf::Sprite();
            sf::Texture _texture = sf::Texture();

            sf::Color _color = sf::Color::White;

            sf::Color _textColor = sf::Color::Black;
            sf::Font _font = sf::Font();
            std::string _str = "";
            unsigned int _charSize = 11;
            sf::Vector2f _textPos = sf::Vector2f(0, 0);
            sf::Text _text = sf::Text(_str, _font, _charSize);

            std::function<void()> _onClick;
            std::function<void()> _onRelease;

            std::function<void()> _onHover;
            std::function<void()> _onUnhover;
    };
}


#endif //KAPPA_ENGINE_BUTTONINTERFACE_HPP
