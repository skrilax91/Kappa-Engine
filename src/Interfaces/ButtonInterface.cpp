//
// Created by leo_b on 03/03/2023.
//

#include "KappaEngine/Interfaces/ButtonInterface.hpp"


Interface::ButtonInterface::ButtonInterface(IPosition position, std::string path, std::array<sf::IntRect, 3> rects): _rect(position), _rects(rects) {
    _texture.loadFromFile(path);
    _sprite.setTexture(_texture);
    _sprite.setTextureRect(_rects[0]);
};

void Interface::ButtonInterface::OnRenderInterface(IPosition parent) {
    auto newPos = Interface::Utils::GetAbsolutePosition(parent, _rect);
    _sprite.setPosition(newPos.x, newPos.y);

    _sprite.setScale(newPos.width / _sprite.getTextureRect().width, newPos.height / _sprite.getTextureRect().height);

    auto mousePos = sf::Mouse::getPosition(*KappaEngine::GameManager::GetWindow());

    if (newPos.x < mousePos.x && newPos.x + newPos.width > mousePos.x && newPos.y < mousePos.y && newPos.y + newPos.height > mousePos.y) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            _sprite.setTextureRect(_rects[2]);
            if (_onClick != nullptr && !_isClicked) {
                _onClick();
            }
            _isClicked = true;
            _isReleased = false;
        } else {
            _sprite.setTextureRect(_rects[1]);

            if (_onRelease != nullptr && !_isReleased) {
                _onRelease();
            }

            if (_onHover != nullptr && !_isHovered) {
                _onHover();
            }

            _isReleased = true;
            _isClicked = false;
            _isHovered = true;
            _isUnhovered = false;
        }
    } else {
        _sprite.setTextureRect(_rects[0]);

        if (_onUnhover != nullptr && !_isUnhovered) {
            _onUnhover();
        }

        if (_onRelease != nullptr && !_isReleased) {
            _onRelease();
        }
        _isUnhovered = true;
        _isHovered = false;
        _isReleased = true;
        _isClicked = false;
    }

    KappaEngine::GameManager::Draw(_sprite);

    if (_text.getString() != "") {
        auto localBounds = _text.getLocalBounds();
        _text.setPosition(newPos.x + newPos.width / 2 - localBounds.width / 2, newPos.y + newPos.height / 2 - localBounds.height / 2 - localBounds.top);
        KappaEngine::GameManager::Draw(_text);
    }
};

void Interface::ButtonInterface::setOnClick(std::function<void()> onClick) { _onClick = onClick; };
void Interface::ButtonInterface::setOnRelease(std::function<void()> onRelease) { _onRelease = onRelease; };
void Interface::ButtonInterface::setOnHover(std::function<void()> onHover) { _onHover = onHover; };
void Interface::ButtonInterface::setOnUnhover(std::function<void()> onUnhover) { _onUnhover = onUnhover; };