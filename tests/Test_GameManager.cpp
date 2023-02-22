//
// Created by leo on 15/02/23.
//

#include "KappaEngine/GameManager.hpp"
#include <gtest/gtest.h>

TEST(GameManager, CreateScene) {
    auto scene = KappaEngine::GameManager::CreateScene("MainScene");
    ASSERT_EQ(scene->getName(), "MainScene");
    ASSERT_EQ(KappaEngine::GameManager::GetScenes().size(), 1);
}

TEST(GameManager, GetScene) {
    auto scene = KappaEngine::GameManager::CreateScene("MainScene");
    auto scene2 = KappaEngine::GameManager::GetScene("MainScene");
    ASSERT_EQ(scene2, scene);
}

TEST(GameManager, SelectScene) {
    auto scene = KappaEngine::GameManager::CreateScene("MainScene");
    KappaEngine::GameManager::SelectScene("MainScene");
    ASSERT_EQ(KappaEngine::GameManager::GetSelectedScene(), scene);
}

TEST(GameManager, GetSelectedScene) {
    auto scene = KappaEngine::GameManager::CreateScene("MainScene");
    KappaEngine::GameManager::SelectScene("MainScene");
    ASSERT_EQ(KappaEngine::GameManager::GetSelectedScene(), scene);
}