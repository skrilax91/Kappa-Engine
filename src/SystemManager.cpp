//
// Created by leo_b on 23/01/2023.
//

#include <iostream>
#include <thread>

#include "KappaEngine/SystemManager.hpp"
#include "KappaEngine/Systems/RigidBodySystem.hpp"
#include "KappaEngine/Systems/CollideBoxSystem.hpp"

namespace KappaEngine {
    SystemManager::SystemManager(Scene *scene) : _scene(scene) {

        // Register all internal systems
        registerSystem<RigidBodySystem>();
        registerSystem<CollideBoxSystem>();


        std::cout << "SystemManager created" << std::endl;
    };

    void SystemManager::Awake() {
        std::vector<std::thread> threads;

        for (auto &system: _systems) {
            std::thread t(&ISystem::Awake, system);
            threads.push_back(std::move(t));
        }
        for (auto &thread: threads) {
            thread.join();
        }
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
            while (_scene->getWindow()->pollEvent(event)) {
                _events.push_back(event);
            }

            if (getEvent<sf::Event::Closed>()) {
                _started = false;
                _scene->getWindow()->close();
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

            for (auto &system: _systems) {
                system->OnRenderObject();
            }


            _scene->RenderWindow();
            std::cout << "FPS: " << 1 / Time::DeltaTime().asSeconds() << std::endl;
        }

        std::cout << "SystemManager stopped" << std::endl;
    }
}