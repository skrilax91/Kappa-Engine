//
// Created by Sebayl on 02/02/2023.
//

namespace Interface {
    void ButtonComponent::draw() {
        if (!sprite.getTexture())
            return;
        KappaEngine::GameManager.GetWindow()->draw(sprite);
    }
}