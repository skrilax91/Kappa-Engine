//
// Created by leo_b on 23/01/2023.
//

#include <iostream>
#include "KappaEngine/Scene.hpp"

namespace KappaEngine {
    Scene::Scene(std::string name): _name(name), _window(sf::VideoMode::getFullscreenModes()[0], name, sf::Style::Fullscreen) {
        _systemManager = new SystemManager(this);
        _entityManager = new EntityManager();
        _window.setFramerateLimit(60);
        std::cout << "Scene created" << std::endl;
    }

    void Scene::StartSystemManager() {
        _systemManager->Start();
    }

    SystemManager *Scene::getSystemManager() {
        return _systemManager;
    }

    EntityManager *Scene::getEntityManager() {
        return _entityManager;
    }

    sf::RenderWindow *Scene::getWindow() {
        return &_window;
    }

    void Scene::RenderWindow() {
        _window.display();
    }
}
