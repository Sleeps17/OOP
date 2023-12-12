#include <gtest/gtest.h>
#include <memory>
#include <fstream>

#include "NPC.hpp"
#include "squirrel.hpp"
#include "elf.hpp"
#include "outlaw.hpp"

TEST(TestSquirrel, TestSquirrelConstructorWithCoords) {
    auto squirrel = std::make_shared<Squirrel>(3, 5);

    ASSERT_TRUE(squirrel -> x == 3 && squirrel -> y == 5 && squirrel -> type == NPCType::SquirrelType);
}

TEST(TestSquirrel, TestSquirrelConstructorWithStream) {
    std::ifstream fs("../data.txt");
    auto squirrel = std::make_shared<Squirrel>(fs);

    ASSERT_TRUE(squirrel -> x == 1 && squirrel -> y == 2 && squirrel -> type == NPCType::SquirrelType);
}

TEST(TestElf, TestElfConstructorWithCoords) {
    auto elf = std::make_shared<Elf>(3, 5);

    ASSERT_TRUE(elf -> x == 3 && elf -> y == 5 && elf -> type == NPCType::ElfType);
}

TEST(TestElf, TestElfConstructorWithStream) {
    std::ifstream fs("../data.txt");
    auto elf = std::make_shared<Elf>(fs);

    ASSERT_TRUE(elf -> x == 1 && elf -> y == 2 && elf -> type == NPCType::ElfType);
}

TEST(TestOutlaw, TestOutlawConstructorWithCoords) {
    auto outlaw = std::make_shared<Outlaw>(3, 5);

    ASSERT_TRUE(outlaw -> x == 3 && outlaw -> y == 5 && outlaw -> type == NPCType::OutlawType);
}

TEST(TestOutlaw, TestOutlawConstructorWithStream) {
    std::ifstream fs("../data.txt");
    auto outlaw = std::make_shared<Outlaw>(fs);

    ASSERT_TRUE(outlaw -> x == 1 && outlaw -> y == 2 && outlaw -> type == NPCType::OutlawType);
}