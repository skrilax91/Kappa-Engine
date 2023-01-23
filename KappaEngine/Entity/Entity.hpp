//
// Created by leo_b on 23/01/2023.
//

#ifndef KAPPA_ENGINE_ENTITY_HPP
#define KAPPA_ENGINE_ENTITY_HPP

#include <list>
#include <memory>
#include <algorithm>
#include <utility>

#include "KappaEngine/Components/IComponent.hpp"

namespace KappaEngine {
    class Entity {
        public:
            explicit Entity(std::string id): _id(std::move(id)) {};
            virtual ~Entity() = default;

            const std::string &getId() const { return _id; }

            template<class T>
            bool hasComponent() {
                static_assert(std::is_base_of<Component::IComponent, T>::value, "T must inherit from Component");

                for (auto &component: _components) {
                    if (dynamic_cast<T *>(component.get()) != nullptr) {
                        return true;
                    }
                }
                return false;
            };

            template<typename T>
            bool registerComponent(T component) {
                static_assert(std::is_base_of<Component::IComponent, T>::value, "T must inherit from Component");

                if (hasComponent<T>()) {
                    return false;
                }
                _components.push_back(std::make_shared<T>(component));
                return true;
            }

            template<class T>
            T *getComponent() {
                static_assert(std::is_base_of<Component::IComponent, T>::value, "T must inherit from Component");

                for (auto &component: _components) {
                    if (auto *castedComponent = dynamic_cast<T *>(component.get())) {
                        return castedComponent;
                    }
                }
                return nullptr;
            }

            template<class T>
            void enableComponent() {
                static_assert(std::is_base_of<Component::IComponent, T>::value, "T must inherit from Component");

                if (auto *component = getComponent<T>()) {
                    component->enabled = true;
                }
            }

            template<class T>
            void disableComponent() {
                static_assert(std::is_base_of<Component::IComponent, T>::value, "T must inherit from Component");

                if (auto *component = getComponent<T>()) {
                    component->enabled = false;
                }
            }


        private:
            std::string _id;
            std::list<std::shared_ptr<Component::IComponent>> _components;
    };
}

#endif //KAPPA_ENGINE_ENTITY_HPP
