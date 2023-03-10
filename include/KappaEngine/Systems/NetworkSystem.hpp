//
// Created by leo_b on 30/01/2023.
//

#ifndef KAPPA_ENGINE_NETWORKSYSTEM_HPP
#define KAPPA_ENGINE_NETWORKSYSTEM_HPP

#include "ISystem.hpp"
#include "KappaEngine/Network/MessageDefine.hpp"

namespace KappaEngine {

    /**
     * @brief The NetworkSystem class is the class that will manage all the network of the engine.
     */
    class NetworkSystem: public ISystem {
        public:
            /**
             * @brief NetworkSystem Constructor of the NetworkSystem class.
             *
             * This function will construct the NetworkSystem class.
             *
             * @param scene The scene that the network system will manage.
             */
            NetworkSystem(Scene *scene): ISystem(scene) {};

            void Awake(std::shared_ptr<Entity>) override;
            void Start(std::shared_ptr<Entity>) override;
            void Update() override;

            sf::Clock _clock;
    };
}

#endif //KAPPA_ENGINE_NETWORKSYSTEM_HPP
