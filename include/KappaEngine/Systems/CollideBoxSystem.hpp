//
// Created by leo_b on 23/01/2023.
//

#ifndef KAPPA_ENGINE_COLLIDEBOXSYSTEM_HPP
#define KAPPA_ENGINE_COLLIDEBOXSYSTEM_HPP

#include "ISystem.hpp"
#include "KappaEngine/Components/CollideBox.hpp"
#include "KappaEngine/Components/Transform.hpp"
#include "KappaEngine/Components/RigidBody.hpp"

namespace KappaEngine {
    class CollideBoxSystem : public ISystem {
        public:
            CollideBoxSystem(Scene *scene) : ISystem(scene) {};
            void OnCollideCheck(std::shared_ptr<Entity> entity);

        private:
            bool canCollide(Component::CollideBox *collideBox, Component::CollideBox *otherCollideBox);
            bool findCollide(std::list<Component::CollideBox &> &list, Component::CollideBox *collide);
            void rollbackOnEnter(sf::FloatRect rect, sf::FloatRect otherRect,
                                Component::Transform *transform, sf::Vector2f velocity);
            void rollbackOnExit(sf::FloatRect rect, sf::FloatRect otherRect,
                                Component::Transform *transform, sf::Vector2f velocity);
    };
}


#endif //KAPPA_ENGINE_COLLIDEBOXSYSTEM_HPP
