//
// Created by leo_b on 23/01/2023.
//

#ifndef KAPPA_ENGINE_ENTITYMANAGER_HPP
#define KAPPA_ENGINE_ENTITYMANAGER_HPP

#include <list>
#include <string>
#include <memory>

#include "Entity/Entity.hpp"
#include "Scene.hpp"

namespace KappaEngine {
    /**
     * @brief The EntityManager class is the class that will manage all entities of a scene.
     */
    class EntityManager {
        public:
            /**
             * @brief EntityManager Constructor of the EntityManager class.
             *
             * This function will construct the EntityManager class.
             */
            EntityManager(Scene *scene) : _scene(scene) {};
            virtual ~EntityManager() = default;

            /**
             * @brief createEntity Create an entity.
             *
             * This function will create an entity.
             *
             * @param name The name of the entity.
             * @param cb The callback function that will be called when the entity is created.
             * @return The entity created.
             * @throw std::runtime_error If the entity already exists.
             */
            Entity &createEntity(const std::string& name, void (*cb)(Entity&) );

            /**
             * @brief createEntity Create an entity.
             *
             * This function will create an entity.
             *
             * @param name The name of the entity.
             * @return The entity created.
             * @throw std::runtime_error If the entity already exists.
             */
            Entity &createEntity(const std::string& name);


            /**
             * @brief destroyEntity Destroy an entity.
             *
             * This function will destroy an entity.
             *
             * @param name The name of the entity.
             * @throw std::runtime_error If the entity doesn't exist.
             */
            void destroyEntity(const std::string& name);

            /**
             * @brief Get all entities.
             * @return A list of all entities.
             */
            std::list<std::shared_ptr<Entity>> getEntities();

            /**
             * @brief Get an entity by its name.
             * @param name The name of the entity.
             * @return The entity.
             * @throw std::runtime_error If the entity doesn't exist.
             */
            Entity &getEntity(const std::string& name);

            /**
             * @brief Get all entities with a specific component.
             * @details This function will return a list of all entities that have a specific component.
             * @details The component must inherit from Component::IComponent.
             * @tparam T The type of the component.
             * @return A list of all entities with the component.
             */
            template<class T>
            std::list<std::shared_ptr<Entity>> getEntitiesWithComponent() {
                static_assert(std::is_base_of<Component::IComponent, T>::value, "T must inherit from Component");

                std::list<std::shared_ptr<Entity>> entities;

                for (auto &entity: _entities) {
                    if (entity->hasComponent<T>()) {
                        entities.push_back(entity);
                    }
                }
                return entities;
            }

            /**
             * @brief Get all entities with a specific tag.
             * @details This function will return a list of all entities that have a specific tag.
             * @param tag The tag of the entities.
             * @return A list of all entities with the tag.
             */
            std::list<std::shared_ptr<Entity>> getEntitiesByTag(const std::string& tag);



        private:
            Scene *_scene;
            std::list<std::shared_ptr<Entity>> _entities;
    };
}

#endif //KAPPA_ENGINE_ENTITYMANAGER_HPP
