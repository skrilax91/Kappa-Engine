//
// Created by leo_b on 29/01/2023.
//

#include "KappaEngine/GameManager.hpp"

namespace KappaEngine {

    sf::Window GameManager::_window;
    std::string GameManager::_name = "Kappa Engine Game";
    bool GameManager::_fullscreen = false;

    void GameManager::createWindow(const std::string &name, int width, int height) {
        _name = name;
        _window.create(sf::VideoMode(width, height), name);
    }

    void GameManager::setFramerateLimit(int limit) {
        _window.setFramerateLimit(limit);
    }

    void GameManager::setFullscreen(bool fullscreen) {
        if (fullscreen == _fullscreen)
            return;

        if (fullscreen)
            _window.create(sf::VideoMode::getFullscreenModes()[0], _name, sf::Style::Fullscreen);
        else
            _window.create(sf::VideoMode::getFullscreenModes()[0], _name);
    }



}
