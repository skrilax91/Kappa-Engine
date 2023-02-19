//
// Created by leo_b on 23/01/2023.
//

#ifndef KAPPA_ENGINE_ENTITY_HPP
#define KAPPA_ENGINE_ENTITY_HPP

#include <list>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <utility>

#include "KappaEngine/Components/IComponent.hpp"

namespace KappaEngine {

    /**
     * @brief Entity class
     * @details This class is used to create entities in the game
     */
    class Entity {
        public:

            /**
             * @brief Constructor of the Entity class
             * @details This constructor is used to create an entity
             * @details It takes an id as parameter
             * @details The id is used to identify the entity
             * @param id The id of the entity
             */
            explicit Entity(std::string id): _id(std::move(id)) {};
            virtual ~Entity() = default;

            /**
             * @brief Get the Id of the entity
             * @details This method is used to get the id of the entity
             * @return The id of the entity
             */
            const std::string &getId() const { return _id; }

            /**
             * @brief Check if the entity has a component
             * @details This method is used to check if the entity has a component
             * @details It takes a template parameter
             * @details The template parameter must inherit from Component
             * @tparam T The type of the component
             * @return True if the entity has the component, false otherwise
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
             * @brief Register a component to the entity
             * @details This method is used to register a component to the entity
             * @details It takes a template parameter
             * @details The template parameter must inherit from Component
             * @tparam T The type of the component
             * @param component The component to register
             * @return The component if the entity doesn't have it, nullptr otherwise
             */
            template<typename T>
            std::shared_ptr<T> registerComponent(T component) {
                static_assert(std::is_base_of<Component::IComponent, T>::value, "T must inherit from Component");

                if (hasComponent<T>()) {
                    return nullptr;
                }

                auto newComponent = std::make_shared<T>(component);
                _components.push_back(newComponent);
                return newComponent;
            }

            /**
             * @brief Get a component from the entity
             * @details This method is used to get a component from the entity
             * @details It takes a template parameter
             * @details The template parameter must inherit from Component
             * @tparam T The type of the component
             * @return The component if the entity has it, nullptr otherwise
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
             * @brief Enable a component
             * @details This method is used to enable a component
             * @details It takes a template parameter
             * @details The template parameter must inherit from Component
             * @tparam T The type of the component
             */
            template<class T>
            void enableComponent() {
                static_assert(std::is_base_of<Component::IComponent, T>::value, "T must inherit from Component");

                if (auto *component = getComponent<T>()) {
                    component->enabled = true;
                }
            }

            /**
             * @brief Disable a component
             * @details This method is used to disable a component
             * @details It takes a template parameter
             * @details The template parameter must inherit from Component
             * @tparam T The type of the component
             */
            template<class T>
            void disableComponent() {
                static_assert(std::is_base_of<Component::IComponent, T>::value, "T must inherit from Component");

                if (auto *component = getComponent<T>()) {
                    component->enabled = false;
                }
            }

            /**
             * @brief Check if the entity has a tag
             * @details This method is used to check if the entity has a tag
             * @details It takes a tag as parameter
             * @param tag The tag to check
             * @return True if the entity has the tag, false otherwise
             */
            bool hasTag(const std::string &tag) {
                return std::find(_tags.begin(), _tags.end(), tag) != _tags.end();
            }

            /**
             * @brief Add a tag to the entity
             * @details This method is used to add a tag to the entity
             * @details It takes a tag as parameter
             * @param tag The tag to add
             */
            void addTag(const std::string &tag) {
                if (!hasTag(tag)) {
                    _tags.push_back(tag);
                }
            }

            /**
             * @brief Remove a tag from the entity
             * @details This method is used to remove a tag from the entity
             * @details It takes a tag as parameter
             * @param tag The tag to remove
             */
            void removeTag(const std::string &tag) {
                if (hasTag(tag)) {
                    _tags.erase(std::remove(_tags.begin(), _tags.end(), tag), _tags.end());
                }
            }


        private:
            std::string _id;
            std::list<std::shared_ptr<Component::IComponent>> _components;
            std::vector<std::string> _tags;
    };
}

#endif //KAPPA_ENGINE_ENTITY_HPP
