#pragma once

#include <iostream>
#include <memory>
#include <vector>

enum class NPCType {
    SquirrelType,
    ElfType,
    OutlawType,
};

class Squirrel;
class Elf;
class Outlaw;
class NPC;

class NPCObserver {
public:
    virtual void onFight(const std::shared_ptr<NPC>&, const std::shared_ptr<NPC>&, bool) = 0;
};

class NPCVisitor {
public:
    [[nodiscard]] virtual bool visit(const std::shared_ptr<Squirrel>&) const = 0;
    [[nodiscard]] virtual bool visit(const std::shared_ptr<Elf>&) const = 0;
    [[nodiscard]] virtual bool visit(const std::shared_ptr<Outlaw>&) const = 0;
};


class NPC: public std::enable_shared_from_this<NPC>{
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
    virtual bool accept(const std::shared_ptr<NPCVisitor>&, const std::shared_ptr<NPC>&) const = 0;

    virtual void print() const = 0;
    virtual void save(std::ostream&) const;

    friend std::ostream& operator<<(std::ostream &os, const NPC &npc);


    ~NPC() = default;
};
