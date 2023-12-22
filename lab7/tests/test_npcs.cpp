#include <gtest/gtest.h>
#include "NPC.hpp"
#include "elf.hpp"
#include "outlaw.hpp"
#include "squirrel.hpp"
#include "visitor.hpp"


class VisitorTest : public testing::Test {
protected:
    void SetUp() override {
        elf = std::make_shared<Elf>("Sanya", 0, 15);
        outlaw = std::make_shared<Outlaw>("Cherchil", 50, 15);
        squirrel = std::make_shared<Squirrel>("Obama", 100, 15);

        elf_visitor = std::make_shared<ElfVisitor>();
        outlaw_visitor = std::make_shared<OutlawVisitor>();
        squirrel_visitor = std::make_shared<SquirrelVisitor>();
    }
    std::shared_ptr<NPC> elf, outlaw, squirrel;
    std::shared_ptr<NPCVisitor> elf_visitor, outlaw_visitor, squirrel_visitor;
};

TEST_F(VisitorTest, VisitTest) {
    ASSERT_FALSE(elf_visitor->visit(std::static_pointer_cast<Elf>(elf)));
    ASSERT_TRUE(elf_visitor->visit(std::static_pointer_cast<Outlaw>(outlaw)));
    ASSERT_FALSE(elf_visitor->visit(std::static_pointer_cast<Squirrel>(squirrel)));
    ASSERT_FALSE(outlaw_visitor->visit(std::static_pointer_cast<Elf>(elf)));
    ASSERT_FALSE(outlaw_visitor->visit(std::static_pointer_cast<Outlaw>(outlaw)));
    ASSERT_TRUE(outlaw_visitor->visit(std::static_pointer_cast<Squirrel>(squirrel)));
    ASSERT_TRUE(squirrel_visitor->visit(std::static_pointer_cast<Elf>(elf)));
    ASSERT_FALSE(squirrel_visitor->visit(std::static_pointer_cast<Outlaw>(outlaw)));
    ASSERT_FALSE(squirrel_visitor->visit(std::static_pointer_cast<Squirrel>(squirrel)));
}
