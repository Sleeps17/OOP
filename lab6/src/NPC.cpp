#include "NPC.hpp"

#include<cmath>
#include<istream>

NPC::NPC(NPCType type, int x, int y): type(type), x(x), y(y) {}
NPC::NPC(NPCType type, std::istream &is): type(type) {
    is >> x >> y;
}

bool NPC::is_close(const std::shared_ptr<NPC>& other, size_t distance) const {
    if (std::pow(x - other->x, 2) + std::pow(y - other->y, 2) <= std::pow(distance, 2))
        return true;
    else
        return false;
}

void NPC::subscribe(const std::shared_ptr<NPCObserver>& observer) {
    observers.push_back(observer);
}

void NPC::fightNotify(const std::shared_ptr<NPC>& defender, bool win) {
    for (auto &o : observers)
        o->onFight(shared_from_this(), defender, win);
}

void NPC::save(std::ostream& os) const {
    os << x << std::endl;
    os << y << std::endl;
}

std::ostream& operator<<(std::ostream &os, const NPC &npc) {
    os << "{ x:" << npc.x << ", y:" << npc.y << "} ";
    return os;
}
