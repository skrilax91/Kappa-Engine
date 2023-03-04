//
// Created by leo_b on 02/03/2023.
//

#include "KappaEngine/Interfaces/Utils.hpp"
#include "KappaEngine/GameManager.hpp"

Interface::IPosition Interface::Utils::GetAbsolutePosition(Interface::IPosition parent, Interface::IPosition child) {

    sf::Vector2<unsigned int> windowSize = KappaEngine::GameManager::GetWindow()->getSize();

    float xRatio = (float)windowSize.x / (float)KappaEngine::GameManager::getInitialResolution().x;
    float yRatio = (float)windowSize.y / (float)KappaEngine::GameManager::getInitialResolution().y;

    Interface::IPosition newPos {0, 0, child.width * xRatio, child.height * yRatio, Interface::Anchor::TOP_LEFT};

    child.x *= xRatio;
    child.y *= yRatio;
    child.width *= xRatio;
    child.height *= yRatio;

    switch (child.anchor) {
        case Interface::Anchor::TOP_LEFT:
            newPos.x = parent.x + child.x;
            newPos.y = parent.y + child.y;
            break;
        case Interface::Anchor::TOP_RIGHT:
            newPos.x = parent.x + parent.width - child.x - child.width;
            newPos.y = parent.y + child.y;
            break;
        case Interface::Anchor::TOP_CENTER:
            newPos.x = parent.x + parent.width / 2 - child.width / 2 + child.x;
            newPos.y = parent.y + child.y;
            break;
        case Interface::Anchor::CENTER_LEFT:
            newPos.x = parent.x + child.x;
            newPos.y = parent.y + parent.height / 2 - child.height / 2 + child.y;
            break;
        case Interface::Anchor::CENTER_RIGHT:
            newPos.x = parent.x + parent.width - child.x - child.width;
            newPos.y = parent.y + parent.height / 2 - child.height / 2 + child.y;
            break;
        case Interface::Anchor::CENTER_CENTER:
            newPos.x = parent.x + parent.width / 2 - child.width / 2 + child.x;
            newPos.y = parent.y + parent.height / 2 - child.height / 2 + child.y;
            break;
        case Interface::Anchor::BOTTOM_LEFT:
            newPos.x = parent.x + child.x;
            newPos.y = parent.y + parent.height - child.y - child.height;
            break;
        case Interface::Anchor::BOTTOM_RIGHT:
            newPos.x = parent.x + parent.width - child.x - child.width;
            newPos.y = parent.y + parent.height - child.y - child.height;
            break;
        case Interface::Anchor::BOTTOM_CENTER:
            newPos.x = parent.x + parent.width / 2 - child.width / 2 + child.x;
            newPos.y = parent.y + parent.height - child.y - child.height;
            break;
    }

    return newPos;
}