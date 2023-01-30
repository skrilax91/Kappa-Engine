//
// Created by leo_b on 30/01/2023.
//

#ifndef KAPPA_ENGINE_NETWORKSYSTEM_HPP
#define KAPPA_ENGINE_NETWORKSYSTEM_HPP

#include "KappaEngine/Systems/ISystem.hpp"

namespace KappaEngine {
    class NetworkSystem: public ISystem {
        public:
            NetworkSystem(Scene *scene): ISystem(scene) {};

            void Awake() override;
    };
}

#endif //KAPPA_ENGINE_NETWORKSYSTEM_HPP
