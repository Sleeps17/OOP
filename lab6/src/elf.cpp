#include "elf.hpp"

void Elf::printType(std::ostream& os) const {
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

Elf::Elf(int _x, int _y): NPC(NPCType::ElfType, _x, _y) {}

Elf::Elf(std::istream& is): NPC(NPCType::ElfType, is) {}

bool Elf::accept(const std::shared_ptr<NPCVisitor>& attackerVisitor, const std::shared_ptr<NPC>& attacker) const {
    std::shared_ptr<const NPC> npcConst = shared_from_this();
    std::shared_ptr<NPC> npc = std::const_pointer_cast<NPC>(npcConst);

    std::shared_ptr<Elf> defender = std::dynamic_pointer_cast<Elf>(npc);

    bool win = attackerVisitor -> visit(defender);

    attacker ->fightNotify(defender, win);

    return win;
}

void Elf::print() const {
    std::cout << *this;
}

void Elf::save(std::ostream& os) const {
    printType(os);
    NPC::save(os);
}

std::ostream &operator<<(std::ostream& os, const Elf& elf) {
    os << "Elf: " << *static_cast<const NPC *>(&elf) << std::endl;
    return os;
}

bool ElfVisitor::visit(const std::shared_ptr<Squirrel>& defender) const {
    return false;
}

bool ElfVisitor::visit(const std::shared_ptr<Elf>& defender) const {
    return false;
}

bool ElfVisitor::visit(const std::shared_ptr<Outlaw>& defender) const {
    return true;
}
