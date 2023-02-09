//
// Created by leo_b on 23/01/2023.
//

#ifndef KAPPA_ENGINE_COLLIDEBOXSYSTEM_HPP
#define KAPPA_ENGINE_COLLIDEBOXSYSTEM_HPP

#include "ISystem.hpp"

namespace KappaEngine {
    class CollideBoxSystem : public ISystem {
        public:
            explicit CollideBoxSystem(Scene *scene) : ISystem(scene) {};
            void Update() override;

        private:
            bool canCollide(const Component::CollideBox *collideBox, const Component::CollideBox *otherCollideBox);
            bool isColliding(const Component::CollideBox *collideBox, const Component::Transform *transform,
                            const Component::CollideBox *otherCollideBox, const Component::Transform *otherTransform);
    };
}


#endif //KAPPA_ENGINE_COLLIDEBOXSYSTEM_HPP
