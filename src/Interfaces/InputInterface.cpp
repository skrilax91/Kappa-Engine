//
// Created by leo_b on 04/03/2023.
//

#include "KappaEngine/Interfaces/InputInterface.hpp"
#include "KappaEngine/Interfaces/Utils.hpp"
#include "KappaEngine/GameManager.hpp"
#include "KappaEngine/Input.hpp"

Interface::InputInterface::InputInterface(IPosition position, std::string placeholder) : _position(position), _placeholder(placeholder) {
    _font.loadFromFile("assets/font/arial.ttf");
    _inputText.setFont(_font);
    _inputText.setString(_placeholder);
    _inputText.setCharacterSize(position.height * 0.8);
    _inputText.setFillColor(sf::Color::Black);
}

void Interface::InputInterface::OnRenderInterface(IPosition parent) {
    auto newPos = Interface::Utils::GetAbsolutePosition(parent, _position);

    sf::RectangleShape rect(sf::Vector2f(newPos.width, newPos.height));
    rect.setFillColor(sf::Color::White);
    rect.setOutlineColor(sf::Color::Black);
    rect.setOutlineThickness(2);
    rect.setPosition(newPos.x, newPos.y);
    KappaEngine::GameManager::GetWindow()->draw(rect);

    auto mousePos = sf::Mouse::getPosition(*KappaEngine::GameManager::GetWindow());

    if (mousePos.x >= newPos.x && mousePos.x <= newPos.x + newPos.width && mousePos.y >= newPos.y && mousePos.y <= newPos.y + newPos.height) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            _isFocused = true;
        }
    } else {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            _isFocused = false;
        }
    }

    if (_isFocused) {
        _inputText.setFillColor(sf::Color::Black);

        bool shiftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);
        bool ctrlPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl);
        bool altPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) || sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt);

        std::vector<sf::Keyboard::Key> keys = KappaEngine::Input::getKeysPressed();
        bool localPressed = false;
        for (auto &key : keys) {
            if (key == sf::Keyboard::LShift || key == sf::Keyboard::RShift || key == sf::Keyboard::LControl || key == sf::Keyboard::RControl || key == sf::Keyboard::LAlt || key == sf::Keyboard::RAlt)
                continue;

            localPressed = true;

            if (key >= sf::Keyboard::A && key <= sf::Keyboard::Z && !_pressed) {
                if (shiftPressed)
                    _text += 'A' + key - sf::Keyboard::A;
                else
                    _text += 'a' + key - sf::Keyboard::A;
                _inputText.setString(_text);
            } else if (key >= sf::Keyboard::Num0 && key <= sf::Keyboard::Num9 && !_pressed) {
                switch (key) {
                    case sf::Keyboard::Num1:
                        if (shiftPressed)
                            _text += '1';
                        else
                            _text += '&';
                        break;
                    case sf::Keyboard::Num2:
                        if (shiftPressed)
                            _text += "2";
                        else if (altPressed)
                            _text += '~';
                        else
                            _text += "??";
                        break;
                    case sf::Keyboard::Num3:
                        if (shiftPressed)
                            _text += "3";
                        else if (altPressed)
                            _text += '#';
                        else
                            _text += '"';
                        break;
                    case sf::Keyboard::Num4:
                        if (shiftPressed)
                            _text += "4";
                        else if (altPressed)
                            _text += '{';
                        else
                            _text += "'";
                        break;
                    case sf::Keyboard::Num5:
                        if (shiftPressed)
                            _text += "5";
                        else if (altPressed)
                            _text += '[';
                        else
                            _text += '(';
                        break;
                    case sf::Keyboard::Num6:
                        if (shiftPressed)
                            _text += "6";
                        else if (altPressed)
                            _text += '|';
                        else
                            _text += '-';
                        break;
                    case sf::Keyboard::Num7:
                        if (shiftPressed)
                            _text += "7";
                        else if (altPressed)
                            _text += '`';
                        else
                            _text += "??";
                        break;
                    case sf::Keyboard::Num8:
                        if (shiftPressed)
                            _text += "8";
                        else if (altPressed)
                            _text += '\\';
                        else
                            _text += "_";
                        break;
                    case sf::Keyboard::Num9:
                        if (shiftPressed)
                            _text += "9";
                        else if (altPressed)
                            _text += '^';
                        else
                            _text += "??";
                        break;
                    case sf::Keyboard::Num0:
                        if (shiftPressed)
                            _text += "0";
                        else if (altPressed)
                            _text += '@';
                        else
                            _text += "??";
                        break;
                }
                _inputText.setString(_text);
            } else if (key >= sf::Keyboard::Numpad0 && key <= sf::Keyboard::Numpad9 && !_pressed) {
                _text += '0' + key - sf::Keyboard::Numpad0;
                _inputText.setString(_text);
            } else if (key == sf::Keyboard::Period && !_pressed) {
                if (shiftPressed)
                    _text += '.';
                else
                    _text += ';';
                _inputText.setString(_text);
            } else if (key == sf::Keyboard::Comma && !_pressed) {
                if (shiftPressed)
                    _text += '?';
                else
                    _text += ',';
                _inputText.setString(_text);
            } else if (key == sf::Keyboard::Slash && !_pressed) {
                if (shiftPressed)
                    _text += '/';
                else
                    _text += ':';
                _inputText.setString(_text);
            } else if (key == sf::Keyboard::Space && !_pressed) {
                _text += ' ';
                _inputText.setString(_text);
            } else if (key == sf::Keyboard::BackSpace && !_pressed) {
                if (!_text.empty()) {
                    _text.pop_back();
                    _inputText.setString(_text);
                    if (_text.empty())
                        _inputText.setString(_placeholder);

                }
            }

            _pressed = true;
            break;
        }

        if (!localPressed) {
            _pressed = false;
        }
    }

    auto localBounds = _inputText.getLocalBounds();
    _inputText.setPosition(newPos.x + 5, newPos.y + newPos.height / 2 - localBounds.height / 2 - localBounds.top);

    KappaEngine::GameManager::GetWindow()->draw(_inputText);
}

std::string Interface::InputInterface::getText() {
    return _inputText.getString();
}