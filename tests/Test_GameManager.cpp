//
// Created by leo on 15/02/23.
//

#include "KappaEngine/GameManager.hpp"
#include <gtest/gtest.h>

TEST(GameManager, CreateScene) {
    auto *scene = KappaEngine::GameManager::CreateScene("MainScene");
    ASSERT_EQ(scene->getName(), "MainScene");
}

TEST(GameManager, GetScene) {
    auto *scene = KappaEngine::GameManager::CreateScene("MainScene");
    ASSERT_EQ(KappaEngine::GameManager::GetScene("MainScene"), scene);
}

TEST(GameManager, SelecteScene) {
    auto *scene = KappaEngine::GameManager::CreateScene("MainScene");
    KappaEngine::GameManager::SelectScene("MainScene");
    ASSERT_EQ(KappaEngine::GameManager::GetSelectedScene(), scene);
}

TEST(GameManager, GetSelectedScene) {
    auto *scene = KappaEngine::GameManager::CreateScene("MainScene");
    KappaEngine::GameManager::SelectScene("MainScene");
    ASSERT_EQ(KappaEngine::GameManager::GetSelectedScene(), scene);
}