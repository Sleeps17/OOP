#pragma once

#include "NPC.hpp"
#include "visitor.hpp"

class Outlaw final : public NPC {
public:
    Outlaw(int, int);
    explicit Outlaw(std::istream& is);

    void print() const override;
    void save(std::ostream& os) const override;
    bool accept(const std::shared_ptr<NPC>&) const override;

    friend std::ostream& operator<<(std::ostream&, const Outlaw&);

    ~Outlaw() = default;
};