//
// Created by leo_b on 23/01/2023.
//

#include <iostream>
#include "Scene.hpp"

namespace KappaEngine {
    Scene::Scene(std::string name): _name(name) {
        _systemManager = new SystemManager(this);
        _entityManager = new EntityManager();
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
}
