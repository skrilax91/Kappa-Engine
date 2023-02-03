//
// Created by leo_b on 23/01/2023.
//

#include <iostream>
#include <thread>

#include "KappaEngine/SystemManager.hpp"
#include "KappaEngine/Systems/RigidBodySystem.hpp"
#include "KappaEngine/Systems/CollideBoxSystem.hpp"
#include "KappaEngine/Systems/SpriteRendererSystem.hpp"
#include "KappaEngine/GameManager.hpp"
#include "KappaEngine/Input.hpp"

namespace KappaEngine {
    SystemManager::SystemManager(Scene *scene) : _scene(scene) {

        // Register all internal systems
        registerSystem<RigidBodySystem>();
        registerSystem<CollideBoxSystem>();
        registerSystem<SpriteRendererSystem>();

        std::cout << "SystemManager created" << std::endl;
    };

    void SystemManager::Awake() {
        for (auto &system: _systems) {
            system->Awake();
        }

        std::cout << "SystemManager awake" << std::endl;
    }

    void SystemManager::Start() {
        for (auto &system: _systems) {
            system->Start();
        }
        _started = true;
        Time::resetTimeLib();
        std::cout << "SystemManager started" << std::endl;
    }

    void SystemManager::Update() {
        Time::UpdateDeltaTime();

        sf::Event event{};
        _events.clear();
        while (GameManager::GetWindow()->pollEvent(event)) {
            _events.push_back(event);
        }

        Input::setEvents(GetEvents<sf::Event::KeyReleased>());

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
