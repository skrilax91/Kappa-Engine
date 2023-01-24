//
// Created by Sebayl on 23/01/2023.
//

#include "ISystem.hpp"
#include "SpriteRender.hpp"

namespace KappaEngine {
    class SpriteRenderSystem : public ISystem {
        public:
            explicit SpriteRenderSystem(Scene *scene) : ISystem(scene) {};
            void Awake() override;
            void Start() override;
            void Update() override;
            void OnDisable() override;
            void OnDestroy() override;
            void updateSpriteRectangle(Entity entity,struct intRect textureRect);
    };
}