#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <set>
#include <fstream>
#include <iostream>

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
    virtual void onFight(const std::shared_ptr<NPC>&, const std::shared_ptr<NPC>&, bool) = 0;
};

class NPCVisitor;

class NPC: public std::enable_shared_from_this<NPC>{
private:
    void printType(std::ostream& os) const;
public:
    NPCType type;
    int x{0};
    int y{0};
    std::vector<std::shared_ptr<NPCObserver>> observers;

    NPC(NPCType, int, int);
    NPC(NPCType, std::istream& is);

    void subscribe(const std::shared_ptr<NPCObserver>&);
    void fightNotify(const std::shared_ptr<NPC>&, bool);

    virtual bool is_close(const std::shared_ptr<NPC>&, size_t) const;
    virtual bool accept(const std::shared_ptr<NPC>&) const = 0;

    virtual void print() const = 0;
    virtual void save(std::ostream&) const;

    friend std::ostream& operator<<(std::ostream &os, const NPC &npc);


    ~NPC() = default;
};
