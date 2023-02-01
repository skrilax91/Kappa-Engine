//
// Created by leo_b on 23/01/2023.
//

#ifndef KAPPA_ENGINE_ENTITYMANAGER_HPP
#define KAPPA_ENGINE_ENTITYMANAGER_HPP

#include <list>
#include <string>
#include <memory>

#include "KappaEngine/Entity/Entity.hpp"

namespace KappaEngine {

    /**
     * @brief The EntityManager class manages all the entities in a specific scene
     * 
     */
    class EntityManager {
        public:
            EntityManager() = default;
            virtual ~EntityManager() = default;

            /**
             * @brief Create a Entity object
             * 
             * @param name The name of the Entity
             * @param cb A pointer to a function used to execute any action on an Entity after its creation, like registering components
             * @return Entity& The entity created
             */
            Entity &createEntity(const std::string& name, void (*cb)(Entity&) );

            /**
             * @brief Get the Entities objects
             * 
             * @return std::list<std::shared_ptr<Entity>>
             */
            std::list<std::shared_ptr<Entity>> getEntities();

            /**
             * @brief Get a specific Entity object defined by its name
             * 
             * @param name The name of the Entity object
             * @return Entity& 
             */
            Entity &getEntity(const std::string& name);

            /**
             * @brief Get the all the Entity objects that are attached to a specific type of component
             * 
             * @tparam T The type of the component object we are looking for
             * @return std::list<std::shared_ptr<Entity>>
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

        private:
            std::list<std::shared_ptr<Entity>> _entities;
    };
}

#endif //KAPPA_ENGINE_ENTITYMANAGER_HPP
