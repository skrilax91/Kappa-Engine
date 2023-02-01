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

    /**
     * @brief The Entity class defines every object in the scene.
     * 
     * It contains a string id and a list of components, which are attached to the Entity
     * 
     */
    class Entity {
        public:
            explicit Entity(std::string id): _id(std::move(id)) {};
            virtual ~Entity() = default;

            /**
             * @brief Get the Id object
             * 
             * @return const std::string& 
             */
            const std::string &getId() const { return _id; }

            /**
             * @brief Check if the Entity object is attached to a specific type of component.
             * 
             * @tparam T The type of component we are looking for
             * @return true if the Entity is attached to the T component
             * @return false if the Entity is not attached to the T component
             */
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

            /**
             * @brief Registers a component into an Entity object.
             * 
             * @tparam T The type of the component we are trying to attach to the Entity
             * @param component The component we are trying to attach to the Entity
             * @return true if the component was successfully attached
             * @return false if a component of the same type was already attached
             */
            template<typename T>
            bool registerComponent(T component) {
                static_assert(std::is_base_of<Component::IComponent, T>::value, "T must inherit from Component");

                if (hasComponent<T>()) {
                    return false;
                }
                _components.push_back(std::make_shared<T>(component));
                return true;
            }

            /**
             * @brief Get a speciffic component that has been attached to the Entity.
             * 
             * @tparam T The type of the component we are looking for
             * @return T* A pointer to the component we are looking for, or nullptr if there is no component of this type attached to the Entity.
             */
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

            /**
             * @brief Enable a component attached to the Entity
             * 
             * @tparam T The type of the component we are trying to enable.
             */
            template<class T>
            void enableComponent() {
                static_assert(std::is_base_of<Component::IComponent, T>::value, "T must inherit from Component");

                if (auto *component = getComponent<T>()) {
                    component->enabled = true;
                }
            }

            /**
             * @brief Disable a component attached to the Entity
             * 
             * @tparam T The type of the component we are trying to disable.
             */
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
