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

#include "EntityManager.hpp"
#include "Scene.hpp"
#include "SystemManager.hpp"

namespace KappaEngine {

    class ISystem {
        public:
            // Lifecycle methods (called by the engine)
            explicit ISystem(Scene *scene) : _scene(scene) {}

            virtual void Awake() {};
            virtual void Start() {};
            virtual void FixedUpdate() {};
            virtual void Update() {};
            virtual void LateUpdate() {};

            virtual void OnRenderObject() {};


            virtual void OnDestroy(Entity *) {};
            virtual void OnDisable() {};

        protected:
            Scene *_scene;


    };
}

#endif //KAPPA_ENGINE_ISYSTEM_HPP
