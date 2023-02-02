//
// Created by Sebayl on 02/02/2023.
//

#include "../../include/KappaEngine/Interfaces/ImageComponent.hpp"

namespace Interface {
    void ImageComponent::draw() {
        if (!sprite.getTexture())
            return;
        KappaEngine::GameManager::GetWindow()->draw(sprite);
    }
} // Interface