#include <gtest/gtest.h>
#include "NPC.hpp"
#include "elf.hpp"
#include "outlaw.hpp"
#include "squirrel.hpp"


class NPCTest : public testing::Test {
protected:
    void SetUp() override {
        elf = std::make_shared<Elf>(0, 15);
        outlaw = std::make_shared<Outlaw>(50, 15);
        squirrel = std::make_shared<Squirrel>(100, 15);
    }

    std::shared_ptr<NPC> elf, outlaw, squirrel;
};

TEST_F(NPCTest, AcceptTest) {
    ASSERT_TRUE(outlaw->accept(elf));
    ASSERT_FALSE(elf->accept(elf));
    ASSERT_FALSE(squirrel->accept(elf));
    ASSERT_TRUE(squirrel->accept(outlaw));
    ASSERT_FALSE(elf->accept(outlaw));
    ASSERT_FALSE(outlaw->accept(outlaw));
    ASSERT_TRUE(elf->accept(squirrel));
    ASSERT_FALSE(outlaw->accept(squirrel));
    ASSERT_FALSE(squirrel->accept(squirrel));
}

TEST_F(NPCTest, IsCloseTest) {
    ASSERT_TRUE(elf->is_close(outlaw, 50));
    ASSERT_TRUE(elf->is_close(squirrel, 100));
    ASSERT_FALSE(elf->is_close(outlaw, 25));
    ASSERT_FALSE(elf->is_close(squirrel, 50));
}


