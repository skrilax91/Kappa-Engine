//
// Created by leo on 10/02/23.
//

#include "KappaEngine/EntityManager.hpp"
#include "KappaEngine/Components/Transform.hpp"
#include <gtest/gtest.h>

TEST(EntityManager, CreateEntity) {
    KappaEngine::EntityManager entityManager(nullptr);
    auto entity = entityManager.createEntity("test");
    ASSERT_EQ(entity->getId(), "test");
}

TEST(EntityManager, GetEntity) {
    KappaEngine::EntityManager entityManager(nullptr);
    auto entity = entityManager.createEntity("test");
    ASSERT_EQ(entityManager.getEntity("test"), entity);
}

TEST(EntityManager, GetEntitiesWithComponent) {
    KappaEngine::EntityManager entityManager(nullptr);
    auto entity = entityManager.createEntity("test", [](KappaEngine::Entity &ent) {
        ent.registerComponent(Component::Transform({0, 0}, {1, 1}, {0, 0}));
    });
    auto entity2 = entityManager.createEntity("test2");
    auto entities = entityManager.getEntitiesWithComponent<Component::Transform>();
    ASSERT_EQ(entities.size(), 1);
    ASSERT_EQ(entities.front(), entity);
}

TEST(EntityManager, GetEntities) {
    KappaEngine::EntityManager entityManager(nullptr);
    auto entity = entityManager.createEntity("test");
    auto entity2 = entityManager.createEntity("test2");
    auto entities = entityManager.getEntities();
    ASSERT_EQ(entities.size(), 2);
}

TEST(EntityManager, DestroyEntityByName) {
    KappaEngine::EntityManager entityManager(nullptr);
    auto entity = entityManager.createEntity("test");
    entityManager.destroyEntity("test");
    ASSERT_EQ(entityManager.getEntities().size(), 0);
}

TEST(EntityManager, DestroyEntityByEntity) {
    KappaEngine::EntityManager entityManager(nullptr);
    auto entity = entityManager.createEntity("test");
    entityManager.destroyEntity(entity);
    ASSERT_EQ(entityManager.getEntities().size(), 0);
}
