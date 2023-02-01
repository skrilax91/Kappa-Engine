//
// Created by leo_b on 29/01/2023.
//

#include <iostream>
#include "GameManager.hpp"

namespace KappaEngine {

    sf::RenderWindow *GameManager::_window = nullptr;
    std::string GameManager::_name = "Kappa Engine Game";
    bool GameManager::_fullscreen = false;
    std::vector<Scene *> GameManager::_scenes = std::vector<Scene *>();


    ///////////////////////////
    // WINDOW
    ///////////////////////////

    void GameManager::CreateGameWindow(const std::string &name, int width, int height) {
        _name = name;
        _window = new sf::RenderWindow();
        _window->create(sf::VideoMode(width, height), name);
        std::cout << "Window created" << std::endl;
    }

    void GameManager::setFramerateLimit(int limit) {
        if (!_window)
            return;
        _window->setFramerateLimit(limit);
    }

    void GameManager::setFullscreen(bool fullscreen) {
        if (fullscreen == _fullscreen || !_window)
            return;

        if (fullscreen)
            _window->create(sf::VideoMode::getFullscreenModes()[0], _name, sf::Style::Fullscreen);
        else
            _window->create(sf::VideoMode::getFullscreenModes()[0], _name);
    }

    sf::RenderWindow *GameManager::GetWindow() {
        return _window;
    }

    void GameManager::Draw(sf::Drawable& drawable) {
        if (!_window)
            return;

        _window->draw(drawable);
    }

    void GameManager::RenderWindow() {
        if (!_window)
            return;

        _window->display();
    }

    void GameManager::CloseWindow() {
        if (!_window)
            return;

        _window->close();
    }


    ///////////////////////////
    // SCENE
    ///////////////////////////

    Scene *GameManager::CreateScene(const std::string &name) {
        auto *scene = new Scene(name);
        _scenes.push_back(scene);
        return scene;
    }

    Scene* GameManager::GetScene(const std::string& name) {
        for (auto scene : _scenes) {
            if (scene->getName() == name)
                return scene;
        }
        return nullptr;
    }

}
