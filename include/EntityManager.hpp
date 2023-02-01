//
// Created by leo_b on 23/01/2023.
//

#ifndef KAPPA_ENGINE_ENTITYMANAGER_HPP
#define KAPPA_ENGINE_ENTITYMANAGER_HPP

#include <list>
#include <string>
#include <memory>

#include "Entity/Entity.hpp"

namespace KappaEngine {
    class EntityManager {
        public:
            EntityManager() = default;
            virtual ~EntityManager() = default;

            Entity &createEntity(const std::string& name, void (*cb)(Entity&) );

            std::list<std::shared_ptr<Entity>> getEntities();
            Entity &getEntity(const std::string& name);

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
