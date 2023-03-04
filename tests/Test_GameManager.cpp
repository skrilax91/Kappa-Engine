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
    ASSERT_EQ(KappaEngine::GameManager::GetScene("MainScene"), scene);
}

TEST(GameManager, SelectScene) {
    KappaEngine::GameManager::CreateScene("MainScene");
    KappaEngine::GameManager::SelectScene("SecondScene");
    ASSERT_EQ(KappaEngine::GameManager::GetSelectedScene(), KappaEngine::GameManager::GetScene("SecondScene"));
}