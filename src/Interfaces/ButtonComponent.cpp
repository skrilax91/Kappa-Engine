//
// Created by Sebayl on 02/02/2023.
//

#include "KappaEngine/Interfaces/ButtonComponent.hpp"

namespace Interface {
    void ButtonComponent::draw() {
        if (!sprite.getTexture())
            return;
        KappaEngine::GameManager::GetWindow()->draw(sprite);
    }
}