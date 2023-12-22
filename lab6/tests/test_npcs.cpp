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

        elfV = std::make_shared<ElfVisitor>();
        outlawV = std::make_shared<OutlawVisitor>();
        squirrelV = std::make_shared<SquirrelVisitor>();
    }

    std::shared_ptr<NPC> elf, outlaw, squirrel;
    std::shared_ptr<NPCVisitor> elfV, outlawV, squirrelV;
};

TEST_F(NPCTest, AcceptTest) {
    ASSERT_TRUE(outlaw->accept(elfV, elf));
    ASSERT_FALSE(elf->accept(elfV, elf));
    ASSERT_FALSE(squirrel->accept(elfV, elf));
    ASSERT_TRUE(squirrel->accept(outlawV, outlaw));
    ASSERT_FALSE(elf->accept(outlawV, outlaw));
    ASSERT_FALSE(outlaw->accept(outlawV, outlaw));
    ASSERT_TRUE(elf->accept(squirrelV, squirrel));
    ASSERT_FALSE(outlaw->accept(squirrelV, squirrel));
    ASSERT_FALSE(squirrel->accept(squirrelV, squirrel));
}

TEST_F(NPCTest, IsCloseTest) {
    ASSERT_TRUE(elf->is_close(outlaw, 50));
    ASSERT_TRUE(elf->is_close(squirrel, 100));
    ASSERT_FALSE(elf->is_close(outlaw, 25));
    ASSERT_FALSE(elf->is_close(squirrel, 50));
}


