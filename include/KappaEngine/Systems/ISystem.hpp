//
// Created by leo_b on 23/01/2023.
//

#ifndef KAPPA_ENGINE_ISYSTEM_HPP
#define KAPPA_ENGINE_ISYSTEM_HPP

namespace KappaEngine {
    class SystemManager;
    class EntityManager;
    class Scene;
}

#include "KappaEngine/EntityManager.hpp"
#include "KappaEngine/Scene.hpp"
#include "KappaEngine/SystemManager.hpp"

namespace KappaEngine {
    /**
     * @brief The ISystem class is the base class of all systems of the engine.
     */
    class ISystem {
        public:
            // Lifecycle methods (called by the engine)
            /**
             * @brief ISystem Constructor of the ISystem class.
             *
             * This function will construct the ISystem class.
             *
             * @param scene The scene that the system will manage.
             */
            explicit ISystem(Scene *scene) : _scene(scene) {}

            /**
             * @brief Awake Called when the system is created.
             *
             * This function will be called when the system is created.
             */
            virtual void Awake(std::shared_ptr<Entity>) {};

            /**
             * @brief Start Called when the system is started.
             *
             * This function will be called when the system is started.
             * It will be called after the Awake function.
             *
             */
            virtual void Start(std::shared_ptr<Entity>) {};

            /**
             * @brief FixedUpdate Called every fixed time.
             *
             * This function will be called every fixed time.
             * It will be called after the Start function.
             * It will be called before the Update function.
             * It is used for physics calculations.
             *
             * @attention This function is called multiple times per frame.
             */
            virtual void FixedUpdate() {};

            /**
             * @brief Update Called every frame.
             *
             * This function will be called every frame.
             * It will be called after the FixedUpdate function.
             * It is used for logic calculations.
             */
            virtual void Update() {};

            /**
             * @brief LateUpdate Called every frame after the Update function.
             *
             * This function will be called every frame after the Update function.
             * It is used for logic calculations.
             */
            virtual void LateUpdate() {};

            /**
             * @brief OnGUI Called every frame after the Update function.
             *
             * This function will be called every frame after the Update function.
             * It is used for GUI rendering.
             */
            virtual void OnRenderObject() {};

            /**
             * @brief OnDestroy Called when the system is destroyed.
             * This function will be called when the system is destroyed.
             */
            virtual void OnDestroy(std::shared_ptr<Entity>) {};

            virtual void OnDisable(std::shared_ptr<Entity>) {};

        protected:
            Scene *_scene;


    };
}

#endif //KAPPA_ENGINE_ISYSTEM_HPP
