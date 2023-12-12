#pragma once

#include "NPC.hpp"

class OutlawVisitor : public NPCVisitor {
public:
    [[nodiscard]] bool visit(const std::shared_ptr<Squirrel>&) const override;
    [[nodiscard]] bool visit(const std::shared_ptr<Elf>&) const override;
    [[nodiscard]] bool visit(const std::shared_ptr<Outlaw>&) const override;
};

class Outlaw : public NPC {
public:
    Outlaw(int, int);
    explicit Outlaw(std::istream& is);

    void print() const override;
    void save(std::ostream& os) const override;
    bool accept(const std::shared_ptr<NPCVisitor>&, const std::shared_ptr<NPC>&) const override;

    friend std::ostream& operator<<(std::ostream&, const Outlaw&);

    ~Outlaw() = default;
};