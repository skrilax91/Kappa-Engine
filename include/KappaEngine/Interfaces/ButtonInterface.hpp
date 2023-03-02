//
// Created by leo_b on 01/02/2023.
//

#ifndef KAPPA_ENGINE_BUTTONINTERFACE_HPP
#define KAPPA_ENGINE_BUTTONINTERFACE_HPP

#include <array>
#include <functional>
#include <SFML/Graphics.hpp>

#include "KappaEngine/GameManager.hpp"
#include "KappaEngine/Interfaces/Utils.hpp"
#include "KappaEngine/Input.hpp"

namespace Interface {
    class ButtonInterface: public IInterface {
        public:
            ButtonInterface(IPosition position, sf::Sprite sprite, std::array<sf::IntRect, 3> rects): _rect(position), _sprite(sprite), _rects(rects) {
                _sprite.setTextureRect(_rects[0]);
            };

            void OnRenderInterface(IPosition parent) override {
                auto newPos = Interface::Utils::GetAbsolutePosition(parent, _rect);
                _sprite.setPosition(newPos.x, newPos.y);

                auto mousePos = sf::Mouse::getPosition(*KappaEngine::GameManager::GetWindow());

                if (newPos.x < mousePos.x && newPos.x + newPos.width > mousePos.x && newPos.y < mousePos.y && newPos.y + newPos.height > mousePos.y) {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        _sprite.setTextureRect(_rects[2]);
                        if (_onClick != nullptr && !_isClicked) {
                            _onClick();
                            _isClicked = true;
                            _isReleased = false;
                        }
                    } else {
                        _sprite.setTextureRect(_rects[1]);

                        if (_onRelease != nullptr && !_isReleased) {
                            _onRelease();
                            _isReleased = true;
                            _isClicked = false;
                        }

                        if (_onHover != nullptr && !_isHovered) {
                            _onHover();
                            _isHovered = true;
                            _isUnhovered = false;
                        }

                    }
                } else {
                    _sprite.setTextureRect(_rects[0]);

                    if (_onUnhover != nullptr && !_isUnhovered) {
                        _onUnhover();
                        _isUnhovered = true;
                        _isHovered = false;
                    }

                    if (_onRelease != nullptr && !_isReleased) {
                        _onRelease();
                        _isReleased = true;
                        _isClicked = false;
                    }
                }

                KappaEngine::GameManager::Draw(_sprite);

                if (_text.getString() != "") {
                    _text.setPosition(newPos.x + newPos.width / 2 - _text.getLocalBounds().width / 2, newPos.y + newPos.height / 2 - _text.getLocalBounds().height / 2);
                    KappaEngine::GameManager::Draw(_text);
                }
            };

            void setOnClick(std::function<void()> onClick) { _onClick = onClick; };
            void setOnRelease(std::function<void()> onRelease) { _onRelease = onRelease; };
            void setOnHover(std::function<void()> onHover) { _onHover = onHover; };
            void setOnUnhover(std::function<void()> onUnhover) { _onUnhover = onUnhover; };

            std::array<sf::IntRect, 3> _rects;
            IPosition _rect;

            sf::Sprite _sprite;
            sf::Font _font;
            sf::Text _text;
    };
}


#endif //KAPPA_ENGINE_BUTTONINTERFACE_HPP
