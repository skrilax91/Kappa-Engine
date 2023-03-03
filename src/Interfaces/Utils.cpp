//
// Created by leo_b on 02/03/2023.
//

#include "KappaEngine/Interfaces/Utils.hpp"

Interface::IPosition Interface::Utils::GetAbsolutePosition(Interface::IPosition parent, Interface::IPosition child) {
    Interface::IPosition newPos {0, 0, child.width, child.height, Interface::Anchor::TOP_LEFT};

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