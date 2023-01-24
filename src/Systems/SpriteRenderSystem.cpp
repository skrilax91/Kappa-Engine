//
// Created by Sebayl on 23/01/2023.
//

#include "SpriteRenderSystem.hpp"

void KappaEngine::SpriteRender::Awake()
{
    std::cout << "SpriteRenderSystem::Awake" << std::endl;
}

void KappaEngine::SpriteRenderSystem::Start()
{
    auto ents = _scene->getEntityManager()->getEntitiesWithComponent<Component::SpriteRender>();
    for (auto &ent : ents) {
        if (ent.getComponent<Component::SpriteRender>().enabled)
            ent.getComponent<Component::SpriteRender>()._sprite.display();
    }
}

void KappaEngine::SpriteRenderSystem::Update()
{
    auto ents = _scene->getEntityManager()->getEntitiesWithComponent<Component::SpriteRender>();
    for (auto &ent : ents) {
        if (ent.getComponent<Component::SpriteRender>().enabled)
            ent.getComponent<Component::SpriteRender>()._sprite.display();
    }
}

void KappaEngine::SpriteRenderSystem::OnDisable()
{
    std::cout << "SprteRenderSystem::OnDisable" << std::endl;
}

void KappaEngine::SpriteRenderSystem::OnDestroy()
{
    std::cout << "SprteRenderSystem::OnDestroy" << std::endl;
}

void KappaEngine::SpriteRenderSystem::updateSpriteRectangle(Entity &entity, struct intRect textureRect)
{
    entity.getComponent<Component::SpriteRender>._sprite.setTextureRect(
        sf::IntRect(textureRect.x, textureRect.y, textureRect.width, textureRect.height));
}