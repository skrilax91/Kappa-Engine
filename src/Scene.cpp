//
// Created by leo_b on 23/01/2023.
//

#include <iostream>
#include <utility>
#include "KappaEngine/Scene.hpp"

namespace KappaEngine {
    Scene::Scene(std::string name): _name(std::move(name)) {
        _systemManager = new SystemManager(this);
        _entityManager = new EntityManager(this);
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

    void Scene::OnAnimator() {
        _systemManager->OnAnimator();
    }

    void Scene::OnRenderObject() {
        _systemManager->OnRenderObject();
    }

    void Scene::OnRenderInterface() {
        _systemManager->OnRenderInterface();
    }

    SystemManager *Scene::getSystemManager() {
        return _systemManager;
    }

    EntityManager *Scene::getEntityManager() {
        return _entityManager;
    }
}
