#pragma once

#include "NPC.hpp"
#include "visitor.hpp"

class Squirrel final : public NPC {
public:
    Squirrel(int, int);
    explicit Squirrel(std::istream&);

    void print() const override;
    void save(std::ostream&) const override;
    bool accept(const std::shared_ptr<NPC>&) const override;

    friend std::ostream& operator<<(std::ostream&, const Squirrel&);

    ~Squirrel() = default;
};