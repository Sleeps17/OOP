#include<gtest/gtest.h>

#include "NPC.hpp"
#include "factory.hpp"

TEST(TestVisitor, TestFight) {
    auto squirrel = Factory::Create(NPCType::SquirrelType, "volodya", 3, 5);
    auto otherSquirrel = Factory::Create(NPCType::SquirrelType, "sanya", 3, 5);
    auto elf = Factory::Create(NPCType::ElfType, "gevorg", 5, 7);
    auto otherElf = Factory::Create(NPCType::ElfType, "arsen", 5, 7);
    auto outlaw = Factory::Create(NPCType::OutlawType, "stepa", 7, 7);
    auto otherOutlaw = Factory::Create(NPCType::OutlawType, "max", 7, 7);

    bool win = squirrel -> accept(elf);
    ASSERT_TRUE(win == false);

    win = squirrel -> accept(outlaw);
    ASSERT_TRUE(win == true);

    win = squirrel -> accept(otherSquirrel);
    ASSERT_TRUE(win == false);

    win = elf -> accept(otherElf);
    ASSERT_TRUE(win == false);

    win = elf -> accept(outlaw);
    ASSERT_TRUE(win == false);

    win = elf -> accept(otherSquirrel);
    ASSERT_TRUE(win == true);

    win = outlaw -> accept(otherElf);
    ASSERT_TRUE(win == true);

    win = outlaw -> accept(outlaw);
    ASSERT_TRUE(win == false);

    win = outlaw ->accept(otherSquirrel);
    ASSERT_TRUE(win == false);
}