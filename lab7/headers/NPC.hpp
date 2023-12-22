#pragma once

#include <iostream>
#include <memory>
#include <cstring>
#include <string>
#include <random>
#include <fstream>
#include <set>
#include <shared_mutex>

class Squirrel;
class Elf;
class Outlaw;
class NPC;
using set_t = std::set<std::shared_ptr<NPC>>;

enum class NPCType {
    SquirrelType,
    ElfType,
    OutlawType,
};

class NPCObserver {
public:
    virtual void onFight(const std::shared_ptr<const NPC>&, const std::shared_ptr<NPC>&, bool) = 0;
};

class NPC: public std::enable_shared_from_this<NPC>{
private:
    void printType(std::ostream& os) const;

protected:
    std::mutex mu;

    NPCType type;
    std::string name;
    int x{0};
    int y{0};

    bool alive{true};
    int moveDistance{0};
    int killDistance{0};

    std::vector<std::shared_ptr<NPCObserver>> observers;

public:
    NPC(NPCType, std::string , int, int);
    NPC(NPCType, std::istream& is);

    NPCType getType();

    void subscribe(const std::shared_ptr<NPCObserver>&);
    void fightNotify(const std::shared_ptr<NPC>&, bool) const;
    virtual bool isClose(const std::shared_ptr<NPC>&);

    virtual bool accept(const std::shared_ptr<NPC>&) const = 0;

    std::pair<int, int> position();
    virtual void print() const = 0;
    virtual void save(std::ostream&) const;

    friend std::ostream& operator<<(std::ostream &os, const NPC &npc);

    int getMoveDistance();
    void move(int, int, int, int);

    bool isAlive();
    void mustDie();

    static int throwDice() noexcept;

    ~NPC() = default;
};
