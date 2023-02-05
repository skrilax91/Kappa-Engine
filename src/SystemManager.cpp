//
// Created by leo_b on 23/01/2023.
//

#include <iostream>
#include <thread>

#include "KappaEngine/SystemManager.hpp"
#include "KappaEngine/Systems/RigidBodySystem.hpp"
#include "KappaEngine/Systems/CollideBoxSystem.hpp"
#include "KappaEngine/Systems/SpriteRendererSystem.hpp"
#include "KappaEngine/Systems/NetworkSystem.hpp"
#include "KappaEngine/GameManager.hpp"
#include "KappaEngine/Input.hpp"

namespace KappaEngine {
    SystemManager::SystemManager(Scene *scene) : _scene(scene) {

        // Register all internal systems
        registerSystem<RigidBodySystem>();
        registerSystem<CollideBoxSystem>();
        registerSystem<SpriteRendererSystem>();
        registerSystem<NetworkSystem>();

        std::cout << "SystemManager created" << std::endl;
    };

    void SystemManager::Awake() {
        auto ents = _scene->getEntityManager()->getEntities();

        for (auto ent : ents) {
            Awake(ent);
        }

        std::cout << "SystemManager awake" << std::endl;
    }

    void SystemManager::Awake(std::shared_ptr<Entity> entity) {
        for (auto &system: _systems) {
            system->Awake(entity);
        }
    }

    void SystemManager::Start() {
        auto ents = _scene->getEntityManager()->getEntities();

        for (auto ent : ents) {
            Start(ent);
        }

        _started = true;
        Time::resetTimeLib();
        std::cout << "SystemManager started" << std::endl;
    }

    void SystemManager::Start(std::shared_ptr<Entity> entity) {
        for (auto &system: _systems) {
            system->Start(entity);
        }
    }

    void SystemManager::Update() {
        Time::UpdateDeltaTime();

        sf::Event event{};
        _events.clear();

        if (GameManager::GetWindow() != nullptr) {
            while (GameManager::GetWindow()->pollEvent(event)) {
                _events.push_back(event);
            }

            std::vector<const sf::Event *> events = GetEvents<sf::Event::KeyPressed>();
            std::vector<const sf::Event *> events2 = GetEvents<sf::Event::KeyReleased>();

            events.insert(events.end(), events2.begin(), events2.end());

            Input::setEvents(events);
        }

        if (getEvent<sf::Event::Closed>()) {
            _started = false;
            GameManager::CloseWindow();
            return;
        }

        Time::RunOnFixedEnv([&] {
            for (auto &system: _systems) {
                system->FixedUpdate();
            }
        });

        for (auto &system: _systems) {
            system->Update();
        }

        for (auto &system: _systems) {
            system->LateUpdate();
        }
        //std::cout << "FPS: " << 1 / Time::DeltaTime().asSeconds() << std::endl;
    }


    void SystemManager::OnRenderObject() {
        for (auto &system: _systems) {
            system->OnRenderObject();
        }
    }
}
