//
// Created by leo_b on 23/01/2023.
//

#ifndef KAPPA_ENGINE_SYSTEMMANAGER_HPP
#define KAPPA_ENGINE_SYSTEMMANAGER_HPP

#include <vector>
#include <thread>
#include <iostream>
#include <SFML/Window/Event.hpp>

namespace KappaEngine {
    class Scene;
    class ISystem;
}

#include "Time.hpp"

#include "Systems/ISystem.hpp"
#include "Scene.hpp"


namespace KappaEngine {

    /**
     * @brief The SystemManager class is the class that will manage all the systems of the engine.
     */
    class SystemManager {
        public:
            explicit SystemManager(Scene *scene);
            ~SystemManager() = default;


            /**
             * @brief Start Start the system manager.
             *
             * This function will start the system manager.
             */
            void Start();

            void Awake();

            /**
             * @brief Update Update the system manager.
             *
             * This function will update the system manager.
             */
            void Update();

            /**
             * @brief OnRenderObject Render the scene.
             *
             * This function will render the scene.
             */
            void OnRenderObject();

            /**
             * @brief registerSystem Register a system.
             *
             * This function will register a system to the system manager.
             *
             * @tparam T The type of the system to register.
             */
            template<class T>
            void registerSystem() {
                static_assert(std::is_base_of<ISystem, T>::value, "T must inherit from ISystem");

                if (getSystem<T>()) {
                    std::cout << "System " << typeid(T).name() << " already registered" << std::endl;
                    return;
                }
                _systems.push_back(new T(_scene));
                std::cout << "System " << typeid(T).name() << " registered" << std::endl;

            };

            /**
             * @brief getSystem Get the first system of the given type.
             *
             * This function will return the first system of the given type.
             *
             * @tparam T The type of the system to get.
             * @return A pointer to the system if found, nullptr otherwise.
             */
            template<class T>
            T *getSystem() {
                static_assert(std::is_base_of<ISystem, T>::value, "T must inherit from ISystem");

                for (auto &system: _systems) {
                    auto *castedSystem = dynamic_cast<T *>(system);
                    if (castedSystem != nullptr) {
                        return castedSystem;
                    }
                }
                return nullptr;
            }

            /**
             * @brief getEvent Get the first event of the given type.
             *
             * This function will return the first event of the given type.
             *
             * @tparam E The type of the event to get.
             * @return A pointer to the event if found, nullptr otherwise.
             */
            template<sf::Event::EventType E>
            const sf::Event *getEvent() {
                for (auto &event: _events) {
                    if (event.type == E) {
                        return &event;
                    }
                }
                return nullptr;
            }

            /**
             * @brief getEvents Get all the events of the given type.
             *
             * This function will return all the events of the given type.
             *
             * @tparam E The type of the events to get.
             * @return A vector of all the events of the given type.
             */
            template<sf::Event::EventType E>
            std::vector<const sf::Event *> GetEvents() {
                std::vector<const sf::Event *> events;
                for (auto &event: _events) {
                    if (event.type == E) {
                        events.push_back(&event);
                    }
                }
                return events;
            }

            /**
             * @brief getScene Get the scene of the system manager.
             *
             * This function will return the scene of the system manager.
             *
             * @return A pointer to the scene.
             */
            Scene *getScene() const { return _scene; }

        private:
            Scene *_scene;
            bool _started = false;
            std::vector<ISystem *> _systems;
            std::vector<sf::Event> _events;
    };
}

#endif //KAPPA_ENGINE_SYSTEMMANAGER_HPP
