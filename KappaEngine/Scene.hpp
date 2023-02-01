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

#include <SFML/Graphics.hpp>
#include "KappaEngine/SystemManager.hpp"
#include "KappaEngine/EntityManager.hpp"

namespace KappaEngine {

    /**
     * @brief The Scene class allows us to render a specific scene of the game. It contains its own Entity and System Managers
     * 
     */
    class Scene {
        public:
            Scene(std::string name);

            /**
             * @brief Get the System Manager object
             * 
             * @return SystemManager* 
             */
            SystemManager *getSystemManager();

            /**
             * @brief Get the Entity Manager object
             * 
             * @return EntityManager* 
             */
            EntityManager *getEntityManager();

            /**
             * @brief Get the Name object
             * 
             * @return std::string 
             */
            std::string getName() {
                return _name;
            }

            /**
             * @brief Calls the Start method of the SystemManager class.
             * 
             */
            void StartSystemManager();

        private:
            std::string _name;
            SystemManager *_systemManager;
            EntityManager *_entityManager;
    };
}

#endif //KAPPA_ENGINE_SCENE_HPP
