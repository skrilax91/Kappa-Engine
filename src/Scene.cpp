//
// Created by leo_b on 23/01/2023.
//

#include <iostream>
#include "KappaEngine/Scene.hpp"

namespace KappaEngine {
    Scene::Scene(std::string name): _name(name) {
        _systemManager = new SystemManager(this);
        _entityManager = new EntityManager();
        std::cout << "Scene created" << std::endl;
    }

    void Scene::Awake() {
        _systemManager->Awake();
    }

    void Scene::Start() {
        _systemManager->Start();
    }

    void Scene::Update() {
        _systemManager->Update();
    }

    void Scene::OnRenderObject() {
        _systemManager->OnRenderObject();
    }

    SystemManager *Scene::getSystemManager() {
        return _systemManager;
    }

    EntityManager *Scene::getEntityManager() {
        return _entityManager;
    }
}
