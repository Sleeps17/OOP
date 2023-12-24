#include "NPC.hpp"

#include<cmath>
#include<istream>
#include <utility>
#include <random>

void NPC::printType(std::ostream &os) const {
    switch (NPCType(type)) {
        case NPCType::OutlawType:
            os << "Outlaw ";
            break;
        case NPCType::SquirrelType:
            os << "Squirrel ";
            break;
        case NPCType::ElfType:
            os << "Elf ";
            break;
    }
}

NPC::NPC(NPCType _type, std::string  _name, int _x, int _y): type(_type), name(std::move(_name)), x(_x), y(_y) {}
NPC::NPC(NPCType _type, std::istream &is): type(_type) {
    is >> name >> x >> y;
}

NPCType NPC::getType() {
    std::lock_guard<std::mutex> lck(mu);
    return type;
}

void NPC::subscribe(const std::shared_ptr<NPCObserver>& observer) {
    observers.push_back(observer);
}

void NPC::fightNotify(const std::shared_ptr<NPC>& defender, bool win) const {
    for (auto &o : observers)
        o->onFight(shared_from_this(), defender, win);
}

bool NPC::isClose(const std::shared_ptr<NPC>& other) {
    auto [otherX, otherY] = other->position();

    std::lock_guard<std::mutex> lck(mu);
    return ((std::pow(x - otherX, 2) + std::pow(y - otherY, 2)) <= std::pow(killDistance, 2));
}

std::pair<int, int> NPC::position() {
    std::lock_guard<std::mutex> lck(mu);
    return {x, y};
}

void NPC::save(std::ostream& os) const {
    os << "x: " << x << std::endl;
    os << "y: "<< y << std::endl;
}

std::ostream& operator<<(std::ostream &os, const NPC &npc) {
    npc.printType(os);
    os << npc.name << " ";
    os << "{ x:" << npc.x << ", y:" << npc.y << "} ";
    return os;
}

int NPC::getMoveDistance() {
    std::lock_guard<std::mutex> lck(mu);
    return moveDistance;
}

void NPC::move(int dx, int dy, int maxX, int maxY) {
    std::lock_guard<std::mutex> lck(mu);

    if (dx > moveDistance || dy > moveDistance) {
        throw std::runtime_error("Max move distance is " + std::to_string(moveDistance));
    }
    if ((x + dx >= 0) && (x + dx <= maxX))
        x += dx;
    if ((y + dy >= 0) && (y + dy <= maxY))
        y += dy;
}

bool NPC::isAlive() {
    std::lock_guard<std::mutex> lck(mu);
    return alive;
}

void NPC::mustDie() {
    std::lock_guard<std::mutex> lck(mu);
    alive = false;
}

int NPC::throwDice() noexcept {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 500);

    return dis(gen) % 6 + 1;
}

