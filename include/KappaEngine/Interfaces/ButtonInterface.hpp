//
// Created by leo_b on 01/02/2023.
//

#ifndef KAPPA_ENGINE_BUTTONINTERFACE_HPP
#define KAPPA_ENGINE_BUTTONINTERFACE_HPP

#include <array>
#include <functional>
#include <SFML/Graphics.hpp>

#include "KappaEngine/GameManager.hpp"
#include "KappaEngine/Interfaces/IInterface.hpp"

namespace Interface {
    class ButtonInterface: public IInterface {
        public:
            ButtonInterface();

            void OnRenderObject() override
            {   if (_sprite.getTexture())
                    KappaEngine::GameManager::GetWindow()->draw(_sprite);
                if (_text.getString() != "")
                    KappaEngine::GameManager::GetWindow()->draw(_text);   };

            void setOnClick(std::function<void()> onClick) { _onClick = onClick; };
            void setOnRelease(std::function<void()> onRelease) { _onRelease = onRelease; };
            void setOnHover(std::function<void()> onHover) { _onHover = onHover; };
            void setOnUnhover(std::function<void()> onUnhover) { _onUnhover = onUnhover; };

            std::array<sf::IntRect, 3> _rects;
            Anchor _anchor = Anchor::TOP_LEFT;

            sf::Sprite _sprite = sf::Sprite();

            sf::Font _font = sf::Font();
            unsigned int _charSize = 11;
            sf::Vector2f _textPos = sf::Vector2f(0, 0);
            sf::Text _text = sf::Text();
    };
}


#endif //KAPPA_ENGINE_BUTTONINTERFACE_HPP
