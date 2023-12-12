#include<gtest/gtest.h>

#include "NPC.hpp"
#include "factory.hpp"
#include "elf.hpp"
#include "squirrel.hpp"
#include "outlaw.hpp"

TEST(TestVisitor, TestFight) {
    auto squirrel = Factory::Create(NPCType::SquirrelType, 3, 5);
    auto otherSquirrel = Factory::Create(NPCType::SquirrelType, 3, 5);
    auto elf = Factory::Create(NPCType::ElfType, 5, 7);
    auto otherElf = Factory::Create(NPCType::ElfType, 5, 7);
    auto outlaw = Factory::Create(NPCType::OutlawType, 7, 7);
    auto otherOutlaw = Factory::Create(NPCType::OutlawType, 7, 7);

    auto squirrelVisitor = std::make_shared<SquirrelVisitor>();
    auto elfVisitor = std::make_shared<ElfVisitor>();
    auto outlawVisitor = std::make_shared<OutlawVisitor>();

    bool win = squirrel -> accept(elfVisitor, elf);
    ASSERT_TRUE(win == false);

    win = squirrel -> accept(outlawVisitor, outlaw);
    ASSERT_TRUE(win == true);

    win = squirrel -> accept(squirrelVisitor, otherSquirrel);
    ASSERT_TRUE(win == false);

    win = elf -> accept(elfVisitor, otherElf);
    ASSERT_TRUE(win == false);

    win = elf -> accept(outlawVisitor, outlaw);
    ASSERT_TRUE(win == false);

    win = elf -> accept(squirrelVisitor, otherSquirrel);
    ASSERT_TRUE(win == true);

    win = outlaw -> accept(elfVisitor, otherElf);
    ASSERT_TRUE(win == true);

    win = outlaw -> accept(outlawVisitor, outlaw);
    ASSERT_TRUE(win == false);

    win = outlaw ->accept(squirrelVisitor, otherSquirrel);
    ASSERT_TRUE(win == false);

}