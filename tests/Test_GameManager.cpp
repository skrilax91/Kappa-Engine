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
    ASSERT_EQ(scene2->getName(), scene->getName());
    ASSERT_EQ(scene.use_count(), 2);
}

TEST(GameManager, SelectScene) {
    auto scene = KappaEngine::GameManager::CreateScene("MainScene");
    KappaEngine::GameManager::SelectScene("MainScene");
    ASSERT_EQ(KappaEngine::GameManager::GetSelectedScene()->getName(), scene->getName());
    ASSERT_EQ(scene.use_count(), 2);
}

TEST(GameManager, GetSelectedScene) {
    auto scene = KappaEngine::GameManager::CreateScene("MainScene");
    KappaEngine::GameManager::SelectScene("MainScene");
    ASSERT_EQ(KappaEngine::GameManager::GetSelectedScene()->getName(), scene->getName());
    ASSERT_EQ(scene.use_count(), 2);
}