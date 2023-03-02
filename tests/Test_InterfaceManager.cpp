
#include <gtest/gtest.h>
#include "KappaEngine/Managers/InterfaceManager.hpp"

TEST(InterfaceManager, AddCanvas) {
    auto canvas = std::make_shared<Interface::Canvas>(Interface::Canvas({
        .x = 0,
        .y = 0,
        .width = 100,
        .height = 100,
        .anchor = Interface::Anchor::TOP_LEFT
    }));

    KappaEngine::InterfaceManager::AddCanvas("test", canvas);
    ASSERT_EQ(KappaEngine::InterfaceManager::GetCanvas("test"), canvas);
}

TEST(InterfaceManager, SetCurrentCanvas) {
    auto canvas = std::make_shared<Interface::Canvas>(Interface::Canvas({
        .x = 0,
        .y = 0,
        .width = 100,
        .height = 100,
        .anchor = Interface::Anchor::TOP_LEFT
    }));

    KappaEngine::InterfaceManager::AddCanvas("test", canvas);
    KappaEngine::InterfaceManager::SetCurrentCanvas("test");
    ASSERT_EQ(KappaEngine::InterfaceManager::GetCurrentCanvas(), canvas);
}

TEST(InterfaceManager, OnRenderInterface) {
    auto canvas = std::make_shared<Interface::Canvas>(Interface::Canvas({
        .x = 0,
        .y = 0,
        .width = 100,
        .height = 100,
        .anchor = Interface::Anchor::TOP_LEFT
    }));

    KappaEngine::InterfaceManager::AddCanvas("test", canvas);
    KappaEngine::InterfaceManager::SetCurrentCanvas("test");
    KappaEngine::InterfaceManager::OnRenderInterface();
    ASSERT_EQ(KappaEngine::InterfaceManager::GetCurrentCanvas(), canvas);
}