#pragma once

#include "NPC.hpp"
#include "visitor.hpp"

class Elf final : public NPC{
public:
    Elf(int, int);
    explicit Elf(std::istream&);

    void print() const override;
    void save(std::ostream&) const override;
    bool accept(const std::shared_ptr<NPC>&) const override;

    friend std::ostream& operator<<(std::ostream&, const Elf&);

    ~Elf() = default;
};