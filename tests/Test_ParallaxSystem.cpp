//
// Created by sebay on 03/03/2023.
//

#include "KappaEngine/Systems/ParallaxSystem.hpp"
#include "KappaEngine/Components/Parallax.hpp"
#include "KappaEngine/Components/SpriteRenderer.hpp"
#include "KappaEngine/EntityManager.hpp"
#include "KappaEngine/GameManager.hpp"

#include <gtest/gtest.h>

TEST(ParallaxSystem, SlideDown) {
    auto scene = KappaEngine::GameManager::CreateScene("test");
    auto entity = scene->getEntityManager()->createEntity("test", [](std::shared_ptr<KappaEngine::Entity> ent) {
        ent->registerComponent(Component::SpriteRenderer({0, 0}, "", {0, 0, 1280, 720}));
        ent->registerComponent(Component::Parallax({0, 1}, {0, 0}, {1280, 720}));
    });

    scene->getSystemManager()->getSystem<KappaEngine::ParallaxSystem>()->FixedUpdate();

    auto rect = entity->getComponent<Component::SpriteRenderer>()->_textureRect;

    ASSERT_EQ(rect.top, 1);
    ASSERT_EQ(rect.left, 0);
}

TEST(ParallaxSystem, SlideUp) {
    auto scene = KappaEngine::GameManager::CreateScene("test");
    auto entity = scene->getEntityManager()->createEntity("test", [](std::shared_ptr<KappaEngine::Entity> ent) {
        ent->registerComponent(Component::SpriteRenderer({0, 0}, "", {0, 0, 1280, 720}));
        ent->registerComponent(Component::Parallax({0, -1}, {0, -1}, {1280, 720}));
    });

    scene->getSystemManager()->getSystem<KappaEngine::ParallaxSystem>()->FixedUpdate();

    auto rect = entity->getComponent<Component::SpriteRenderer>()->_textureRect;

    ASSERT_EQ(rect.top, -1);
    ASSERT_EQ(rect.left, 0);
}

TEST(ParallaxSystem, SlideLeft) {
    auto scene = KappaEngine::GameManager::CreateScene("test");
    auto entity = scene->getEntityManager()->createEntity("test", [](std::shared_ptr<KappaEngine::Entity> ent) {
        ent->registerComponent(Component::SpriteRenderer({0, 0}, "", {0, 0, 1280, 720}));
        ent->registerComponent(Component::Parallax({-1, 0}, {-1, 0}, {1280, 720}));
    });

    scene->getSystemManager()->getSystem<KappaEngine::ParallaxSystem>()->FixedUpdate();

    auto rect = entity->getComponent<Component::SpriteRenderer>()->_textureRect;

    ASSERT_EQ(rect.top, 0);
    ASSERT_EQ(rect.left, -1);
}

TEST(ParallaxSystem, SlideRight) {
    auto scene = KappaEngine::GameManager::CreateScene("test");
    auto entity = scene->getEntityManager()->createEntity("test", [](std::shared_ptr<KappaEngine::Entity> ent) {
        ent->registerComponent(Component::SpriteRenderer({0, 0}, "", {0, 0, 1280, 720}));
        ent->registerComponent(Component::Parallax({1, 0}, {0, 0}, {1280, 720}));
    });

    scene->getSystemManager()->getSystem<KappaEngine::ParallaxSystem>()->FixedUpdate();

    auto rect = entity->getComponent<Component::SpriteRenderer>()->_textureRect;

    ASSERT_EQ(rect.top, 0);
    ASSERT_EQ(rect.left, 1);
}

TEST(ParallaxSystem, SlideBottomRight) {
    auto scene = KappaEngine::GameManager::CreateScene("test");
    auto entity = scene->getEntityManager()->createEntity("test", [](std::shared_ptr<KappaEngine::Entity> ent) {
        ent->registerComponent(Component::SpriteRenderer({0, 0}, "", {0, 0, 1280, 720}));
        ent->registerComponent(Component::Parallax({1, 1}, {0, 0}, {1280, 720}));
    });

    scene->getSystemManager()->getSystem<KappaEngine::ParallaxSystem>()->FixedUpdate();

    auto rect = entity->getComponent<Component::SpriteRenderer>()->_textureRect;

    ASSERT_EQ(rect.top, 1);
    ASSERT_EQ(rect.left, 1);
}

TEST(ParallaxSystem, SlideTopLeft) {
    auto scene = KappaEngine::GameManager::CreateScene("test");
    auto entity = scene->getEntityManager()->createEntity("test", [](std::shared_ptr<KappaEngine::Entity> ent) {
        ent->registerComponent(Component::SpriteRenderer({0, 0}, "", {0, 0, 1280, 720}));
        ent->registerComponent(Component::Parallax({-1, -1}, {-1, -1}, {1280, 720}));
    });

    scene->getSystemManager()->getSystem<KappaEngine::ParallaxSystem>()->FixedUpdate();

    auto rect = entity->getComponent<Component::SpriteRenderer>()->_textureRect;

    ASSERT_EQ(rect.top, -1);
    ASSERT_EQ(rect.left, -1);
}

TEST(ParallaxSystem, SlideTopRight) {
    auto scene = KappaEngine::GameManager::CreateScene("test");
    auto entity = scene->getEntityManager()->createEntity("test", [](std::shared_ptr<KappaEngine::Entity> ent) {
        ent->registerComponent(Component::SpriteRenderer({0, 0}, "", {0, 0, 1280, 720}));
        ent->registerComponent(Component::Parallax({-1, 1}, {-1, 0}, {1280, 720}));
    });

    scene->getSystemManager()->getSystem<KappaEngine::ParallaxSystem>()->FixedUpdate();

    auto rect = entity->getComponent<Component::SpriteRenderer>()->_textureRect;

    ASSERT_EQ(rect.top, 1);
    ASSERT_EQ(rect.left, -1);
}

TEST(ParallaxSystem, SlideBottomLeft) {
    auto scene = KappaEngine::GameManager::CreateScene("test");
    auto entity = scene->getEntityManager()->createEntity("test", [](std::shared_ptr<KappaEngine::Entity> ent) {
        ent->registerComponent(Component::SpriteRenderer({0, 0}, "", {0, 0, 1280, 720}));
        ent->registerComponent(Component::Parallax({1, -1}, {0, -1}, {1280, 720}));
    });

    scene->getSystemManager()->getSystem<KappaEngine::ParallaxSystem>()->FixedUpdate();

    auto rect = entity->getComponent<Component::SpriteRenderer>()->_textureRect;

    ASSERT_EQ(rect.top, -1);
    ASSERT_EQ(rect.left, 1);
}

TEST(ParallaxSystem, ResetToTop) {
    auto scene = KappaEngine::GameManager::CreateScene("test");
    auto entity = scene->getEntityManager()->createEntity("test", [](std::shared_ptr<KappaEngine::Entity> ent) {
        ent->registerComponent(Component::SpriteRenderer({0, 0}, "", {0, 720, 1280, 720}));
        ent->registerComponent(Component::Parallax({0, 1}, {0, 0}, {1280, 720}));
    });

    scene->getSystemManager()->getSystem<KappaEngine::ParallaxSystem>()->FixedUpdate();

    auto rect = entity->getComponent<Component::SpriteRenderer>()->_textureRect;

    ASSERT_EQ(rect.top, 0);
    ASSERT_EQ(rect.left, 0);
}

TEST(ParallaxSystem, ResetToBottom) {
    auto scene = KappaEngine::GameManager::CreateScene("test");
    auto entity = scene->getEntityManager()->createEntity("test", [](std::shared_ptr<KappaEngine::Entity> ent) {
        ent->registerComponent(Component::SpriteRenderer({0, 0}, "", {0, 0, 1280, 720}));
        ent->registerComponent(Component::Parallax({0, -1}, {0, 0}, {1280, 720}));
    });

    scene->getSystemManager()->getSystem<KappaEngine::ParallaxSystem>()->FixedUpdate();

    auto rect = entity->getComponent<Component::SpriteRenderer>()->_textureRect;

    ASSERT_EQ(rect.top, 720);
    ASSERT_EQ(rect.left, 0);
}

TEST(ParallaxSystem, ResetToLeft) {
    auto scene = KappaEngine::GameManager::CreateScene("test");
    auto entity = scene->getEntityManager()->createEntity("test", [](std::shared_ptr<KappaEngine::Entity> ent) {
        ent->registerComponent(Component::SpriteRenderer({0, 0}, "", {1280, 0, 1280, 720}));
        ent->registerComponent(Component::Parallax({1, 0}, {0, 0}, {1280, 720}));
    });

    scene->getSystemManager()->getSystem<KappaEngine::ParallaxSystem>()->FixedUpdate();

    auto rect = entity->getComponent<Component::SpriteRenderer>()->_textureRect;

    ASSERT_EQ(rect.top, 0);
    ASSERT_EQ(rect.left, 0);
}

TEST(ParallaxSystem, ResetToRight) {
    auto scene = KappaEngine::GameManager::CreateScene("test");
    auto entity = scene->getEntityManager()->createEntity("test", [](std::shared_ptr<KappaEngine::Entity> ent) {
        ent->registerComponent(Component::SpriteRenderer({0, 0}, "", {0, 0, 1280, 720}));
        ent->registerComponent(Component::Parallax({-1, 0}, {0, 0}, {1280, 720}));
    });

    scene->getSystemManager()->getSystem<KappaEngine::ParallaxSystem>()->FixedUpdate();

    auto rect = entity->getComponent<Component::SpriteRenderer>()->_textureRect;

    ASSERT_EQ(rect.top, 0);
    ASSERT_EQ(rect.left, 1280);
}

TEST(ParallaxSystem, ResetToTopLeft) {
    auto scene = KappaEngine::GameManager::CreateScene("test");
    auto entity = scene->getEntityManager()->createEntity("test", [](std::shared_ptr<KappaEngine::Entity> ent) {
        ent->registerComponent(Component::SpriteRenderer({0, 0}, "", {1280, 720, 1280, 720}));
        ent->registerComponent(Component::Parallax({1, 1}, {0, 0}, {1280, 720}));
    });

    scene->getSystemManager()->getSystem<KappaEngine::ParallaxSystem>()->FixedUpdate();

    auto rect = entity->getComponent<Component::SpriteRenderer>()->_textureRect;

    ASSERT_EQ(rect.top, 0);
    ASSERT_EQ(rect.left, 0);
}

TEST(ParallaxSystem, ResetToTopRight) {
    auto scene = KappaEngine::GameManager::CreateScene("test");
    auto entity = scene->getEntityManager()->createEntity("test", [](std::shared_ptr<KappaEngine::Entity> ent) {
        ent->registerComponent(Component::SpriteRenderer({0, 0}, "", {0, 720, 1280, 720}));
        ent->registerComponent(Component::Parallax({-1, 1}, {0, 0}, {1280, 720}));
    });

    scene->getSystemManager()->getSystem<KappaEngine::ParallaxSystem>()->FixedUpdate();

    auto rect = entity->getComponent<Component::SpriteRenderer>()->_textureRect;

    ASSERT_EQ(rect.top, 0);
    ASSERT_EQ(rect.left, 1280);
}

TEST(ParallaxSystem, ResetToBottomLeft) {
    auto scene = KappaEngine::GameManager::CreateScene("test");
    auto entity = scene->getEntityManager()->createEntity("test", [](std::shared_ptr<KappaEngine::Entity> ent) {
        ent->registerComponent(Component::SpriteRenderer({0, 0}, "", {1280, 0, 1280, 720}));
        ent->registerComponent(Component::Parallax({1, -1}, {0, 0}, {1280, 720}));
    });

    scene->getSystemManager()->getSystem<KappaEngine::ParallaxSystem>()->FixedUpdate();

    auto rect = entity->getComponent<Component::SpriteRenderer>()->_textureRect;

    ASSERT_EQ(rect.top, 720);
    ASSERT_EQ(rect.left, 0);
}

TEST(ParallaxSystem, ResetToBottomRight) {
    auto scene = KappaEngine::GameManager::CreateScene("test");
    auto entity = scene->getEntityManager()->createEntity("test", [](std::shared_ptr<KappaEngine::Entity> ent) {
        ent->registerComponent(Component::SpriteRenderer({0, 0}, "", {0, 0, 1280, 720}));
        ent->registerComponent(Component::Parallax({-1, -1}, {0, 0}, {1280, 720}));
    });

    scene->getSystemManager()->getSystem<KappaEngine::ParallaxSystem>()->FixedUpdate();

    auto rect = entity->getComponent<Component::SpriteRenderer>()->_textureRect;

    ASSERT_EQ(rect.top, 720);
    ASSERT_EQ(rect.left, 1280);
}

TEST(ParallaxSystem, ResetToTopLeftWithOffset) {
    auto scene = KappaEngine::GameManager::CreateScene("test");
    auto entity = scene->getEntityManager()->createEntity("test", [](std::shared_ptr<KappaEngine::Entity> ent) {
        ent->registerComponent(Component::SpriteRenderer({0, 0}, "", {1280, 720, 1280, 720}));
        ent->registerComponent(Component::Parallax({1, 1}, {100, 100}, {1280, 720}));
    });

    scene->getSystemManager()->getSystem<KappaEngine::ParallaxSystem>()->FixedUpdate();

    auto rect = entity->getComponent<Component::SpriteRenderer>()->_textureRect;

    ASSERT_EQ(rect.top, 100);
    ASSERT_EQ(rect.left, 100);
}

TEST(ParallaxSystem, ResetToTopRightWithOffset) {
    auto scene = KappaEngine::GameManager::CreateScene("test");
    auto entity = scene->getEntityManager()->createEntity("test", [](std::shared_ptr<KappaEngine::Entity> ent) {
        ent->registerComponent(Component::SpriteRenderer({0, 0}, "", {0, 720, 1280, 720}));
        ent->registerComponent(Component::Parallax({-1, 1}, {0, 100}, {1180, 720}));
    });

    scene->getSystemManager()->getSystem<KappaEngine::ParallaxSystem>()->FixedUpdate();

    auto rect = entity->getComponent<Component::SpriteRenderer>()->_textureRect;

    ASSERT_EQ(rect.top, 100);
    ASSERT_EQ(rect.left, 1180);
}

TEST(ParallaxSystem, ResetToBottomLeftWithOffset) {
    auto scene = KappaEngine::GameManager::CreateScene("test");
    auto entity = scene->getEntityManager()->createEntity("test", [](std::shared_ptr<KappaEngine::Entity> ent) {
        ent->registerComponent(Component::SpriteRenderer({0, 0}, "", {1280, 0, 1280, 720}));
        ent->registerComponent(Component::Parallax({1, -1}, {100, 0}, {1280, 620}));
    });

    scene->getSystemManager()->getSystem<KappaEngine::ParallaxSystem>()->FixedUpdate();

    auto rect = entity->getComponent<Component::SpriteRenderer>()->_textureRect;

    ASSERT_EQ(rect.top, 620);
    ASSERT_EQ(rect.left, 100);
}

TEST(ParallaxSystem, ResetToBottomRightWithOffset) {
    auto scene = KappaEngine::GameManager::CreateScene("test");
    auto entity = scene->getEntityManager()->createEntity("test", [](std::shared_ptr<KappaEngine::Entity> ent) {
        ent->registerComponent(Component::SpriteRenderer({0, 0}, "", {0, 0, 1280, 720}));
        ent->registerComponent(Component::Parallax({-1, -1}, {0, 0}, {1180, 620}));
    });

    scene->getSystemManager()->getSystem<KappaEngine::ParallaxSystem>()->FixedUpdate();

    auto rect = entity->getComponent<Component::SpriteRenderer>()->_textureRect;

    ASSERT_EQ(rect.top, 620);
    ASSERT_EQ(rect.left, 1180);
}
