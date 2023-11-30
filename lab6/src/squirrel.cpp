#include "squirrel.hpp"

void Squirrel::printType(std::ostream& os) const {
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

Squirrel::Squirrel(int _x, int _y): NPC(NPCType::SquirrelType, _x, _y) {}

Squirrel::Squirrel(std::istream& is): NPC(NPCType::SquirrelType, is) {}

bool Squirrel::accept(const std::shared_ptr<NPCVisitor>& AttackerVisitor, const std::shared_ptr<NPC>& attacker) const {

    std::shared_ptr<const NPC> npcConst = shared_from_this();
    std::shared_ptr<NPC> npc = std::const_pointer_cast<NPC>(npcConst);
    std::shared_ptr<Squirrel> defender = std::dynamic_pointer_cast<Squirrel>(npc);

    bool win = (AttackerVisitor -> visit(defender));

    attacker ->fightNotify(defender, win);

    return win;
}

void Squirrel::print() const {
    std::cout << *this;
}

void Squirrel::save(std::ostream& os) const {
    printType(os);
    NPC::save(os);
}

std::ostream &operator<<(std::ostream& os, const Squirrel& squirrel) {
    os << "Squirrel: " << *static_cast<const NPC *>(&squirrel) << std::endl;
    return os;
}

// VISITOR

bool SquirrelVisitor::visit(const std::shared_ptr<Squirrel>& defender) const {
    return false;
}

bool SquirrelVisitor::visit(const std::shared_ptr<Elf>& defender) const {
    return true;
}

bool SquirrelVisitor::visit(const std::shared_ptr<Outlaw>& defender) const {
    return false;
}
