#include <gtest/gtest.h>

#include "factory.hpp"
#include "NPC.hpp"

TEST(TestFactory, TestCreateWithType) {
    auto npc = Factory::Create(NPCType(1), "Pavel" ,1, 2);

    ASSERT_TRUE(npc->getType() == NPCType(1) && npc->position().first == 1 && npc->position().second == 2);

    auto npc2 = Factory::Create(NPCType(100), "Pavel", 3, 4);

    ASSERT_TRUE(npc2 == nullptr);
}

TEST(TestFactory, TestCreateWithStream) {
    auto npc = Factory::Create(NPCType(1), std::cin);

    ASSERT_TRUE(npc->getType() == NPCType(1) && npc->position().first == 1 && npc->position().second == 2);

    auto npc2 = Factory::Create(NPCType(100), std::cin);

    ASSERT_TRUE(npc2 == nullptr);
}