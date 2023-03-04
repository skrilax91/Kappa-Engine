//
// Created by leo_b on 04/03/2023.
//

#include "KappaEngine/Interfaces/Canvas.hpp"

namespace Interface {
    void Canvas::OnRenderInterface(IPosition parent) {
        if (!_isActivated)
            return;

        auto newPos = Interface::Utils::GetAbsolutePosition(parent, _rect);

        sf::RectangleShape rect(sf::Vector2f(_rect.width, _rect.height));
        rect.setFillColor(_color);
        rect.setOutlineColor(sf::Color::Red);
        rect.setOutlineThickness(1);
        rect.setPosition(newPos.x, newPos.y);
        KappaEngine::GameManager::GetWindow()->draw(rect);

        for (auto &interface : _interfaces) {
            interface->OnRenderInterface(newPos);
        }
    }

    void Canvas::SetPosition(IPosition pos) {
        _rect = pos;
    }

    void Canvas::AddInterface(std::shared_ptr<IInterface> interface) {
        _interfaces.push_back(interface);
    }

    void Canvas::SetColor(sf::Color color) {
        _color = color;
    }
}