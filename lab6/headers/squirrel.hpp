#pragma once

#include "NPC.hpp"

class SquirrelVisitor : public NPCVisitor {
public:
    [[nodiscard]] bool visit(const std::shared_ptr<Squirrel>&) const override;
    [[nodiscard]] bool visit(const std::shared_ptr<Elf>&) const override;
    [[nodiscard]] bool visit(const std::shared_ptr<Outlaw>&) const override;
};

class Squirrel : public NPC {
public:
    Squirrel(int, int);
    explicit Squirrel(std::istream&);

    void print() const override;
    void save(std::ostream&) const override;
    bool accept(const std::shared_ptr<NPCVisitor>&, const std::shared_ptr<NPC>&) const override;

    friend std::ostream& operator<<(std::ostream&, const Squirrel&);

    ~Squirrel() = default;
};