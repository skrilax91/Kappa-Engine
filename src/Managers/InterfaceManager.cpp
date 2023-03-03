//
// Created by leo_b on 02/03/2023.
//

#include "KappaEngine/Managers/InterfaceManager.hpp"
#include "KappaEngine/Interfaces/IInterface.hpp"
#include "KappaEngine/GameManager.hpp"

std::unordered_map<std::string, std::shared_ptr<Interface::Canvas>> KappaEngine::InterfaceManager::_canvases = {};
std::shared_ptr<Interface::Canvas> KappaEngine::InterfaceManager::_currentCanvas = nullptr;

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

    if (_currentCanvas != nullptr) {
        _currentCanvas->SetPosition({
            0,
            0,
            static_cast<float>(GameManager::GetWindow()->getSize().x),
            static_cast<float>(GameManager::GetWindow()->getSize().y),
            Interface::Anchor::TOP_LEFT
        });

        _currentCanvas->OnRenderInterface({
            0,
            0,
            static_cast<float>(GameManager::GetWindow()->getSize().x),
            static_cast<float>(GameManager::GetWindow()->getSize().y),
            Interface::Anchor::TOP_LEFT
      });
    }
}