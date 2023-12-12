#include <gtest/gtest.h>

#include "factory.hpp"

TEST(TestFactory, TestCreateWithType) {
    auto npc = Factory::Create(NPCType(1), 1, 2);

    ASSERT_TRUE(npc->type == NPCType(1) && npc -> x == 1 && npc -> y == 2 && npc->observers.size() == 2);

    auto npc2 = Factory::Create(NPCType(100), 3, 4);

    ASSERT_TRUE(npc2 == nullptr);
}

TEST(TestFactory, TestCreateWithStream) {
    auto npc = Factory::Create(NPCType(1), std::cin);

    ASSERT_TRUE(npc->type == NPCType(1) && npc -> x == 1 && npc -> y == 2 && npc->observers.size() == 2);

    auto npc2 = Factory::Create(NPCType(100), std::cin);

    ASSERT_TRUE(npc2 == nullptr);
}