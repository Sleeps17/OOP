#include<memory>
#include<set>
#include<map>
#include <unordered_map>
#include <random>
#include <iostream>
#include <fstream>

#include "NPC.hpp"
#include "squirrel.hpp"
#include "outlaw.hpp"
#include "elf.hpp"

using set_t = std::set<std::shared_ptr<NPC>>;

class TextObserver: public NPCObserver {

private:
    TextObserver() {}

public:
    static std::shared_ptr<NPCObserver> get() {
        static TextObserver instance;
        return {&instance, [](NPCObserver *) {}};
    }

    void onFight(const std::shared_ptr<NPC>& attacker, const std::shared_ptr<NPC>& defender, bool win) override {
        if(win) {
            std::cout << std::endl
                      << "Murder --------" << std::endl;
            attacker->print();
            defender->print();
        }
    }
};

class FileObserver: public NPCObserver {
private:
    FileObserver() {}
public:
    static std::shared_ptr<NPCObserver> get() {
        static FileObserver instance;
        return {&instance, [](NPCObserver *) {}};
    }

    void onFight(const std::shared_ptr<NPC>& attacker, const std::shared_ptr<NPC>& defender, bool win) override {
        if(win) {
            std::ofstream fs("log.txt");
            fs << std::endl
                      << "Murder --------" << std::endl;
            attacker->save(fs);
            defender->save(fs);
        }
    }
};

class Factory {
public:
    static std::shared_ptr<NPC> Create(const NPCType& npcType, int x, int y) {
        std::shared_ptr<NPC> result;
        switch (npcType) {
            case NPCType::SquirrelType:
                result = std::make_shared<Squirrel>(x, y);
            case NPCType::OutlawType:
                result = std::make_shared<Outlaw>(x, y);
            case NPCType::ElfType:
                result = std::make_shared<Elf>(x, y);
            default:
                result = nullptr;
        }

        if (result) {
            result ->subscribe(TextObserver::get());
            result ->subscribe(FileObserver::get());
        }

        return result;
    }
    static std::shared_ptr<NPC> Create(const NPCType& npcType, std::istream& is) {
        std::shared_ptr<NPC> result;
        switch (npcType) {
            case NPCType::SquirrelType:
                result = std::make_shared<Squirrel>(is);
            case NPCType::OutlawType:
                result = std::make_shared<Outlaw>(is);
            case NPCType::ElfType:
                result =  std::make_shared<Elf>(is);
            default:
                result = nullptr;
        }

        if (result) {
            result ->subscribe(TextObserver::get());
            result ->subscribe(FileObserver::get());
        }

        return result;
    }
};

std::unordered_map<int, std::shared_ptr<NPCVisitor>> map1;

void printNPCType(int type) {
    switch (type) {
        case 0:
            std::cout << "Squirrel" << " ";
            break;
        case 1:
            std::cout << "Outlaw" << " ";
            break;
        case 2:
            std::cout << "Elf" << " ";
            break;
        default:
            break;

    }
}

void printNPC(const std::shared_ptr<NPC>& npc) {
    printNPCType(int(npc -> type));
    std::cout << npc -> x << " " << npc -> y << std::endl;
}

int main() {
    map1[0] = std::make_shared<SquirrelVisitor>();
    map1[1] = std::make_shared<OutlawVisitor>();
    map1[2] = std::make_shared<ElfVisitor>();

    std::map<std::shared_ptr<NPC>, std::shared_ptr<NPCVisitor>> map2;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 500);

    set_t array;
    for(int i = 0; i < 20; ++i) {
        int npcType = dis(gen) % 3;

        std::shared_ptr<NPC> npc = Factory::Create(NPCType(npcType), dis(gen), dis(gen));
        array.insert(npc);
        map2[npc] = map1[npcType];
    }


    for (auto& i : array) {
        std::cout << int(i -> type) << " " << i -> x << " " << i -> y << std::endl;
    }

    std::shared_ptr<NPC> defender = *(++array.begin());
    std::shared_ptr<NPC> attacker = *(++array.begin());

    printNPC(defender);
    printNPC(attacker);

    bool success = defender -> accept(map2[attacker], attacker);

    std::cout << (success ? "Success" : "No success") << std::endl;
}
