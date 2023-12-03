#include "outlaw.hpp"

void Outlaw::printType(std::ostream& os) const {
    switch (type) {
        case NPCType::SquirrelType:
            os << "Squirrel";
            break;
        case NPCType::OutlawType:
            os << "Outlaw";
            break;
        case NPCType::ElfType:
            os << "Elf";
            break;

    }
}

Outlaw::Outlaw(int _x, int _y): NPC(NPCType::OutlawType, _x, _y) {}

Outlaw::Outlaw(std::istream &is): NPC(NPCType::OutlawType, is) {}

bool Outlaw::accept(const std::shared_ptr<NPCVisitor>& AttackerVisitor, const std::shared_ptr<NPC>& attacker) const {
    std::shared_ptr<const NPC> npcConst = shared_from_this();
    std::shared_ptr<NPC> npc = std::const_pointer_cast<NPC>(npcConst);

    std::shared_ptr<Outlaw> defender = std::dynamic_pointer_cast<Outlaw>(npc);
    bool win = AttackerVisitor -> visit(defender);

    attacker -> fightNotify(defender, win);

    return win;
}

void Outlaw::print() const {
    std::cout << *this;
}

void Outlaw::save(std::ostream &os) const {
    os << *this;
}

std::ostream &operator<<(std::ostream& os, const Outlaw& outlaw) {
    os << *static_cast<const NPC *>(&outlaw) << std::endl;
    return os;
}

// VISITOR

bool OutlawVisitor::visit(const std::shared_ptr<Squirrel>& defender) const {
    return true;
}

bool OutlawVisitor::visit(const std::shared_ptr<Elf>& defender) const {
    return false;
}

bool OutlawVisitor::visit(const std::shared_ptr<Outlaw>& defender) const {
    return false;
}


