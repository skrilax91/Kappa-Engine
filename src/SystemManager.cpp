//
// Created by leo_b on 23/01/2023.
//

#include <iostream>
#include <thread>

#include "SystemManager.hpp"
#include "Systems/RigidBodySystem.hpp"
#include "Systems/CollideBoxSystem.hpp"
#include "Systems/SpriteRendererSystem.hpp"
#include "GameManager.hpp"
#include "Input.hpp"

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
        std::cout << "SystemManager started" << std::endl;

        Time::resetTimeLib();

        while (_started) {
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
                break;
            }

            Time::RunOnFixedEnv([&] {
                for (auto &system: _systems) {
                    system->FixedUpdate();
                }
            });

            /*std::vector<std::thread> threads;

            for (auto &system: _systems) {
                std::thread t(&ISystem::Update, system);
                threads.push_back(std::move(t));
            }
            for (auto &thread: threads) {
                thread.join();
            }*/

            GameManager::GetWindow()->clear();
            for (auto &system: _systems) {
                system->OnRenderObject();
            }


            GameManager::RenderWindow();
            //std::cout << "FPS: " << 1 / Time::DeltaTime().asSeconds() << std::endl;
        }

        std::cout << "SystemManager stopped" << std::endl;
    }
}
