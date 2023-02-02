//
// Created by Sebayl on 02/02/2023.
//

void Interface::ButtonComponent::draw() {
    if (!sprite.getTexture())
        return;
    KappaEngine::GameManager.GetWindow()->draw(sprite);
}