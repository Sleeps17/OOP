#pragma once

#include "NPC.hpp"

class ElfVisitor : public NPCVisitor {
public:
    [[nodiscard]] bool visit(const std::shared_ptr<Squirrel>&) const override;
    [[nodiscard]] bool visit(const std::shared_ptr<Elf>&) const override;
    [[nodiscard]] bool visit(const std::shared_ptr<Outlaw>&) const override;
};

class Elf : public NPC{
private:
    void printType(std::ostream&) const;
public:
    Elf(int, int);
    explicit Elf(std::istream&);

    void print() const override;
    void save(std::ostream&) const override;
    bool accept(const std::shared_ptr<NPCVisitor>&, const std::shared_ptr<NPC>&) const override;

    friend std::ostream& operator<<(std::ostream&, const Elf&);

    ~Elf() = default;
};