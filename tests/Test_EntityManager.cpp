//
// Created by leo on 10/02/23.
//

#include <gtest/gtest.h>
#include "KappaEngine/EntityManager.hpp"


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