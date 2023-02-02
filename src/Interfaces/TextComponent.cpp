//
// Created by sebay on 02/02/2023.
//

#include "../../include/KappaEngine/Interfaces/TextComponent.hpp"

namespace Interface {
    void TextComponent::draw() {
        if (text.getString().isEmpty())
            return;
        KappaEngine::GameManager::GetWindow()->draw(text);
    }
} // Interface