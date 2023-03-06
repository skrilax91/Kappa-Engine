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
#include "SystemManager.hpp"
#include "EntityManager.hpp"

namespace KappaEngine {

    /**
     * @brief The Scene class is the class that will manage all entities and systems of the engine.
     */
    class Scene {
        public:
            /**
             * @brief Scene Constructor of the Scene class.
             *
             * This function will construct the Scene class.
             *
             * @param name The name of the scene.
             */
            Scene(std::string name);

            /**
             * @brief getSystemManager Get the system manager of the scene.
             *
             * This function will return the system manager of the scene.
             *
             * @return The system manager of the scene.
             */
            SystemManager *getSystemManager();

            /**
             * @brief getEntityManager Get the entity manager of the scene.
             *
             * This function will return the entity manager of the scene.
             *
             * @return The entity manager of the scene.
             */
            EntityManager *getEntityManager();

            /**
             * @brief getName Get the name of the scene.
             *
             * This function will return the name of the scene.
             *
             * @return The name of the scene.
             */
            std::string getName() {
                return _name;
            }

            //////////////////////////
            // Lifecycle functions
            //////////////////////////

            /**
             * @brief Awake Awake the scene.
             * This function will awake the scene.
             */
            void Awake();

            /**
             * @brief Start Start the scene.
             * This function will start the scene.
             */
            void Start();

            /**
             * @brief FixedUpdate FixedUpdate the scene.
             * This function will FixedUpdate the scene.
             */
            void Update();

            /**
             * @brief OnAnimator OnAnimator the scene.
             * This function will OnAnimator the scene.
             */
            void OnAnimator();

            /**
             * @brief OnRenderObject OnRenderObject the scene.
             * This function will OnRenderObject the scene.
             */
            void OnRenderObject();

            /**
             * @brief OnRenderInterface OnRenderInterface the scene.
             * This function will OnRenderInterface the scene.
             */
            void OnRenderInterface();


        private:
            std::string _name;
            SystemManager *_systemManager;
            EntityManager *_entityManager;
    };
}

#endif //KAPPA_ENGINE_SCENE_HPP
