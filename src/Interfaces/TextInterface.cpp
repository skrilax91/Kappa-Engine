//
// Created by leo_b on 04/03/2023.
//

#include "KappaEngine/GameManager.hpp"
#include "KappaEngine/Interfaces/TextInterface.hpp"

namespace Interface {

    TextInterface::TextInterface(IPosition position, std::string text): _position(position) {
        if (!_font.loadFromFile("assets/font/arial.ttf"))
            std::cout << "Error while loading font" << std::endl;
        _text.setFont(_font);
        _text.setString(text);
        _text.setFillColor(sf::Color::White);
        _text.setCharacterSize(24);
    }

    void TextInterface::OnRenderInterface(IPosition parent) {
        auto ap = Utils::GetAbsolutePosition(parent, _position);
        auto lb = _text.getLocalBounds();
        _text.setPosition(ap.x + ap.width / 2 - lb.width / 2, ap.y + ap.height / 2 - lb.height / 2 - lb.top);
        KappaEngine::GameManager::GetWindow()->draw(_text);
    }

    void TextInterface::setColor(sf::Color color) {
        _text.setFillColor(color);
    }

    void TextInterface::setSize(unsigned int size) {
        _text.setCharacterSize(size);
    }

    void TextInterface::setText(std::string text) {
        _text.setString(text);
    }
}