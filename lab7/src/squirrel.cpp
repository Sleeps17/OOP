#include "squirrel.hpp"

Squirrel::Squirrel(const std::string& _name, int _x, int _y): NPC(NPCType::SquirrelType, _name, _x, _y) {
    moveDistance = 5, killDistance = 5;
}

Squirrel::Squirrel(std::istream& is): NPC(NPCType::SquirrelType, is) {
    moveDistance = 5, killDistance = 5;
}

bool Squirrel::accept(const std::shared_ptr<NPC>& attacker) const {
    auto AttackerVisitor = VisitorFactory::CreateVisitor(attacker -> getType());

    std::shared_ptr<NPC> npc = std::const_pointer_cast<NPC>(shared_from_this());
    std::shared_ptr<Squirrel> defender = std::dynamic_pointer_cast<Squirrel>(npc);

    bool win = (AttackerVisitor -> visit(defender));
    attacker -> fightNotify(defender, win);

    return win;
}

void Squirrel::print() const {
    std::cout << *this;
}

void Squirrel::save(std::ostream& os) const {
    os << *this;
}

std::ostream &operator<<(std::ostream& os, const Squirrel& squirrel) {
    os << *static_cast<const NPC *>(&squirrel) << std::endl;
    return os;
}
