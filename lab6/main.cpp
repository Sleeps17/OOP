#include <unordered_map>
#include <random>
#include <utility>

#include "NPC.hpp"
#include "factory.hpp"

class DataSaver {
private:
    std::string filename;

public:
    explicit DataSaver(std::string  filename) : filename(std::move(filename)) {}
    void Save(const set_t& arr) const noexcept {
        std::ofstream fs(filename, std::ios::app);
        for (auto &npc: arr) {
            fs << int(npc->type) << " " << npc->x << " " << npc->y << std::endl;
        }
    }
};

class DataLoader {
private:
    std::string filename;
    void clear() const noexcept {
        std::ofstream out(filename, std::ios::trunc);
        out.close();
    }
public:
    explicit DataLoader(std::string  filename) : filename(std::move(filename)) {}
    [[nodiscard]] set_t Load() const noexcept {
        set_t arr;
        std::ifstream fs(filename);
        int npcType;
        int x;
        int y;
        while(fs >> npcType >> x >> y) {
            arr.insert(Factory::Create(NPCType(npcType), x, y));
        }

        fs.close();

        this -> clear();

        return arr;
    }
};

std::unordered_map<std::string, NPCType> types = {
    {"squirrel", NPCType::SquirrelType},
    {"elf", NPCType::ElfType},
    {"outlaw", NPCType::OutlawType}
};

set_t Fight(const set_t& array, size_t distance)
{
    set_t dead_list;

    for (const auto &attacker : array) {
        for (const auto &defender : array) {
            if ((attacker != defender) && (dead_list.find(defender) == dead_list.end()) && (attacker->is_close(defender, distance))) {
                bool win = defender ->accept(attacker);
                if (win) {
                    dead_list.insert(defender);
                }
            }
        }
    }

    return dead_list;
}

int main() {
    DataSaver saver("data.txt");
    DataLoader loader("data.txt");

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 500);

    set_t array;
    for(int i = 0; i < 7; ++i) {
        int npcType = dis(gen) % 3;

        auto npc = Factory::Create(NPCType(npcType), dis(gen), dis(gen));

        array.insert(npc);
    }

    std::cout << "\t\tUSAGE" << std::endl;
    std::cout << "1. To create a new NPC: create <NPC type> <x> <y>" << std::endl;
    std::cout << "2. To save the current state of the map: save" << std::endl;
    std::cout << "3. To load the last saved state of the map: load" << std::endl;
    std::cout << "4. To start fight: fight <range of attack>" << std::endl;

    std::string action;
    while(std::cin >> action) {
        if(action == "create") {
            std::string npcType;
            int x, y;
            std::cin >> npcType >> x >> y;
            array.insert(Factory::Create(types[npcType], x, y));
            std::cout << "created !" << std::endl;
        } else if(action == "save") {
            saver.Save(array);
            std::cout << "saved !" << std::endl;
        } else if(action == "load") {
            array = loader.Load();
            std::cout << "loaded !" << std::endl;
        } else if(action == "fight") {
            int range;
            std::cin >> range;
            set_t dead_list = Fight(array, range);
            std::cout << "\nDead: " << dead_list.size() << std::endl;
            for(auto& npc : dead_list) {
                std::cout << *npc << std::endl;
            }
            std::cout << std::endl;
            for(auto& npc : dead_list) {
                array.erase(npc);
            }
        } else {
            std::cout << "Wrong command" << std::endl;
        }
    }
}
