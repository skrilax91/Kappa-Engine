//
// Created by leo_b on 23/01/2023.
//

#ifndef KAPPA_ENGINE_SCENE_HPP
#define KAPPA_ENGINE_SCENE_HPP

#include <string>

namespace KappaEngine {
    class SystemManager;
    class EntityManager;
}

#include "KappaEngine/SystemManager.hpp"
#include "KappaEngine/EntityManager.hpp"

namespace KappaEngine {

    class Scene {
        public:
            Scene(std::string name);

            SystemManager *getSystemManager();
            EntityManager *getEntityManager();

            void StartSystemManager();
            void wait();

        private:
            std::string _name;
            SystemManager *_systemManager;
            EntityManager *_entityManager;
    };
}

#endif //KAPPA_ENGINE_SCENE_HPP
