//
// Created by leo_b on 23/01/2023.
//

#ifndef KAPPA_ENGINE_SYSTEMMANAGER_HPP
#define KAPPA_ENGINE_SYSTEMMANAGER_HPP

#include <vector>
#include <thread>

namespace KappaEngine {
    class Scene;
    class ISystem;
}

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

            void Start();
            void Awake();

            template<class T>
            void registerSystem() {
                static_assert(std::is_base_of<ISystem, T>::value, "T must inherit from ISystem");

                if (getSystem<T>()) {
                    return;
                }
                _systems.push_back(new T(_scene));
            };

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

            Scene *getScene() const { return _scene; }
            void WaitStop();

        private:
            Scene *_scene;
            bool _started = false;
            std::thread _updateThread;
            std::vector<ISystem *> _systems;

            void _startUpdates();
    };
}

#endif //KAPPA_ENGINE_SYSTEMMANAGER_HPP
