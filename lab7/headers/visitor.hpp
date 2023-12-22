#pragma once

#include "NPC.hpp"
#include "elf.hpp"
#include "outlaw.hpp"
#include "squirrel.hpp"

class NPCVisitor {
public:
    [[nodiscard]] virtual bool visit(const std::shared_ptr<Squirrel>&) const = 0;
    [[nodiscard]] virtual bool visit(const std::shared_ptr<Elf>&) const = 0;
    [[nodiscard]] virtual bool visit(const std::shared_ptr<Outlaw>&) const = 0;
};

class ElfVisitor : public NPCVisitor {
public:
    [[nodiscard]] bool visit(const std::shared_ptr<Squirrel>&) const override { return false; }
    [[nodiscard]] bool visit(const std::shared_ptr<Elf>&) const override { return false; }
    [[nodiscard]] bool visit(const std::shared_ptr<Outlaw>&) const override { return true; }
};

class OutlawVisitor : public NPCVisitor {
public:
    [[nodiscard]] bool visit(const std::shared_ptr<Squirrel>&) const override { return true; }
    [[nodiscard]] bool visit(const std::shared_ptr<Elf>&) const override { return false; }
    [[nodiscard]] bool visit(const std::shared_ptr<Outlaw>&) const override { return false; }
};

class SquirrelVisitor : public NPCVisitor {
public:
    [[nodiscard]] bool visit(const std::shared_ptr<Squirrel>&) const override { return false; }
    [[nodiscard]] bool visit(const std::shared_ptr<Elf>&) const override { return true; }
    [[nodiscard]] bool visit(const std::shared_ptr<Outlaw>&) const override { return false; }
};

class VisitorFactory {
public:
    static std::shared_ptr<NPCVisitor> CreateVisitor(const NPCType& type) {
        std::shared_ptr<NPCVisitor> result;
        switch (type) {
            case NPCType::ElfType:
                result = std::static_pointer_cast<NPCVisitor>(std::make_shared<ElfVisitor>());
                break;

            case NPCType::OutlawType:
                result = std::static_pointer_cast<NPCVisitor>(std::make_shared<OutlawVisitor>());
                break;

            case NPCType::SquirrelType:
                result = std::static_pointer_cast<NPCVisitor>(std::make_shared<SquirrelVisitor>());
                break;
            default:
                break;
        }
        return result;
    }
};