#include "outlaw.hpp"

Outlaw::Outlaw(const std::string& _name, int _x, int _y): NPC(NPCType::OutlawType, _name, _x, _y) {
    killDistance = 5, moveDistance = 5;
}

Outlaw::Outlaw(std::istream &is): NPC(NPCType::OutlawType, is) {
    killDistance = 5, moveDistance = 5;
}

bool Outlaw::accept(const std::shared_ptr<NPC>& attacker) const {
    auto AttackerVisitor = VisitorFactory::CreateVisitor(attacker -> getType());

    std::shared_ptr<NPC> npc = std::const_pointer_cast<NPC>(shared_from_this());
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
