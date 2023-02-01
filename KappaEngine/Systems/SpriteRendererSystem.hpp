//
// Created by Sebayl on 23/01/2023.
//

#include <iostream>
#include <unordered_map>
#include "ISystem.hpp"
#include "KappaEngine/Components/SpriteRenderer.hpp"
#include "KappaEngine/Components/Transform.hpp"
#include "KappaEngine/Components/Camera.hpp"

namespace KappaEngine {

    /**
     * @brief SpriteRendererSystem contains the logic that allows to render any object of a scene on a window?
     * 
     * It contains a texture cache to avoid loading the same texture several times
     * 
     */
    class SpriteRendererSystem : public ISystem {
        public:
            explicit SpriteRendererSystem(Scene *scene) : ISystem(scene) {};

            void Awake() override;
            void OnDestroy(Entity *) override;
            void OnRenderObject() override;

        private:
            std::unordered_map<std::string, sf::Texture> _textureCache = std::unordered_map<std::string, sf::Texture>();
    };
};
