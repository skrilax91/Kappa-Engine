//
// Created by Sebayl on 23/01/2023.
//

#include <iostream>
#include <unordered_map>
#include "ISystem.hpp"
#include "KappaEngine/Components/SpriteRenderer.hpp"
#include "KappaEngine/Components/Transform.hpp"

namespace KappaEngine {
    class SpriteRendererSystem : public ISystem {
        public:
            explicit SpriteRendererSystem(Scene *scene) : ISystem(scene) {};

            void Awake() override;
            void Update() override;
            void OnDestroy(Entity *) override;


        private:
            std::unordered_map<std::string, sf::Texture> _textureCache = std::unordered_map<std::string, sf::Texture>();
    };
};