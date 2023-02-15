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
            void rollback(Component::Transform *transform, Component::CollideBox *collideBox, Component::CollideBox *otherCollideBox);
            void enterCollideBox(std::shared_ptr<Entity> entity, std::shared_ptr<Entity> otherEntity,
                                Component::CollideBox *collideBox, Component::CollideBox *otherCollideBox);
    };
}


#endif //KAPPA_ENGINE_COLLIDEBOXSYSTEM_HPP
