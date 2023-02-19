//
// Created by leo_b on 23/01/2023.
//

#include <stdexcept>
#include "KappaEngine/EntityManager.hpp"
#include "KappaEngine/GameManager.hpp"

using namespace KappaEngine;

std::shared_ptr<Entity> EntityManager::createEntity(const std::string& name) {
    return createEntity(name, [](std::shared_ptr<Entity>) {});
}

std::shared_ptr<Entity> EntityManager::createEntity(const std::string& name, const std::function<void(std::shared_ptr<Entity>)>& cb) {
    for (auto &entity: _entities) {
        if (entity->getId() == name) {
            throw std::runtime_error("Entity already exist");
        }
    }

    auto entity = std::make_shared<Entity>(name);
    cb(entity);
    _entities.push_back(entity);

    // Handle systems if game is started and if the entity is in the selected scene (if there is one)
    if (GameManager::GameStarted()) {
        _scene->getSystemManager()->Awake(entity);
        if (GameManager::GetSelectedScene() == _scene)
            _scene->getSystemManager()->Start(entity);
    }

    return *entity;
}

void EntityManager::destroyEntity(const std::string& name) {
    for (auto it = _entities.begin(); it != _entities.end(); it++) {
        if ((*it)->getId() == name) {
            _entities.erase(it);
            return;
        }
    }
    throw std::runtime_error("Entity not found");
}


std::list <std::shared_ptr<Entity>> EntityManager::getEntities() {
    return _entities;
}

Entity &EntityManager::getEntity(const std::string& name) {
    for (auto &entity: _entities) {
        if (entity->getId() == name) {
            return *entity;
        }
    }
    throw std::runtime_error("Entity not found");
}

std::list <std::shared_ptr<Entity>> EntityManager::getEntitiesByTag(const std::string& tag) {
    std::list <std::shared_ptr<Entity>> entities;

    for (auto &entity: _entities) {
        if (entity->hasTag(tag)) {
            entities.push_back(entity);
        }
    }
    return entities;
}