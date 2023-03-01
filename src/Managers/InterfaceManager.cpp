//
// Created by leo_b on 02/03/2023.
//

#include "KappaEngine/Managers/InterfaceManager.hpp"

static std::unordered_map<std::string, std::shared_ptr<Interface::Canvas>> _canvases;
static std::shared_ptr<Interface::Canvas> _currentCanvas = nullptr;

void KappaEngine::InterfaceManager::AddCanvas(const std::string &name, std::shared_ptr<Interface::Canvas> canvas) {
    _canvases[name] = canvas;
}

void KappaEngine::InterfaceManager::SetCurrentCanvas(const std::string &name) {
    _currentCanvas = _canvases[name];
}

std::shared_ptr<Interface::Canvas> KappaEngine::InterfaceManager::GetCurrentCanvas() {
    return _currentCanvas;
}

std::shared_ptr<Interface::Canvas> KappaEngine::InterfaceManager::GetCanvas(const std::string &name) {
    return _canvases[name];
}

void KappaEngine::InterfaceManager::OnRenderInterface() {
    if (_currentCanvas != nullptr)
        _currentCanvas->OnRenderInterface({0, 0});
}

Interface::IPosition KappaEngine::InterfaceManager::GetAbsolutePosition(Interface::IPosition parent, Interface::IPosition child) {
    Interface::IPosition newPos = { .x = 0, .y = 0, .width = child.width, .height = child.height, .anchor = Interface::Anchor::TOP_LEFT };

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
}