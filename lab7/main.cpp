#include <memory>
#include <unordered_map>
#include <random>
#include <iostream>
#include <fstream>
#include <utility>
#include <set>
#include <sstream>
#include <thread>
#include <mutex>
#include <chrono>
#include <queue>
#include <optional>
#include <array>
#include <shared_mutex>

#include "NPC.hpp"
#include "factory.hpp"

std::mutex print_mutex;

std::ostream& operator<<(std::ostream& os, const set_t& array) {
    for (auto& n : array)
        n->print();
    return os;
}

struct FightEvent {
    std::shared_ptr<NPC> attacker;
    std::shared_ptr<NPC> defender;
};

class FightManager final {
private:
    std::queue<FightEvent> events;
    std::shared_mutex mtx;

    FightManager() = default;

public:
    static FightManager& get() {
        static FightManager instance;
        return instance;
    }

    void add_event(FightEvent&& event) {
        std::lock_guard<std::shared_mutex> lock(mtx);
        events.push(event);
    }

    void operator()() {
        while (true) {
            {
                std::optional<FightEvent> event;

                {
                    std::lock_guard<std::shared_mutex> lock(mtx);
                    if (!events.empty()) {
                        event = events.back();
                        events.pop();
                    }
                }
                if (event) {
                    if (event->attacker->isAlive() && event->defender->isAlive() && (event->attacker->throwDice() > event->defender->throwDice()) && event->defender->accept(event->attacker)) {
                        event->defender->mustDie();
                    }

                } else {
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }
            }
        }
    }
};

class DataSaver {
private:
    std::string filename;

public:
    explicit DataSaver(std::string  filename) : filename(std::move(filename)) {}
    void Save(const set_t& arr) const noexcept {
        std::ofstream fs(filename, std::ios::app);
        for (auto &npc: arr) {
            fs << int(npc->getType()) << " " << npc->position().first << " " << npc->position().second << std::endl;
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
        std::string name;
        int x;
        int y;
        while(fs >> npcType >> name >> x >> y) {
            arr.insert(Factory::Create(NPCType(npcType), name, x, y));
        }

        fs.close();

        this -> clear();

        return arr;
    }
};

int main() {
    DataSaver saver("data.txt");
    DataLoader loader("data.txt");

    const int maxX{100};
    const int maxY{100};

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 500);

    set_t array;

    std::vector<std::string> names = {"Clarence", "Justin", "Travis", "Scott", "Natalie", "Valerie", "David", "Charles", "George", "Laura"};

    std::cout << "Generating ..." << std::endl;
    for (size_t i = 0; i < 100; ++i)
        array.insert(Factory::Create(NPCType(dis(gen) % 3), names[i % names.size()], dis(gen) % maxX, dis(gen) % maxY));

    std::cout << "Starting list:" << std::endl << array;

    std::thread fight_thread(std::ref(FightManager::get()));

    std::thread move_thread([&array, maxX, maxY, &dis, &gen]() {
        while (true) {
            for (const std::shared_ptr<NPC>& npc : array) {
                if (npc->isAlive()) {
                    int dx = dis(gen) % (npc->getMoveDistance() * 2) - npc->getMoveDistance();
                    int dy = dis(gen) % (npc->getMoveDistance() * 2) - npc->getMoveDistance();
                    npc->move(dx, dy, maxX, maxY);
                }
            }

            for (const std::shared_ptr<NPC>& npc : array)
                for (const std::shared_ptr<NPC>& other : array)
                    if (other != npc && npc->isAlive() && other->isAlive() && npc->isClose(other)) {
                        FightManager::get().add_event({npc, other});
                    }

            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    });

    while (true) {
        const int grid{20}, step_x{maxX / grid}, step_y{maxY / grid};
        {
            std::array<char, grid* grid> fields{0};
            for (const std::shared_ptr<NPC>& npc : array) {
                auto [x, y] = npc->position();
                int i = x / step_x;
                int j = y / step_y;

                if (npc->isAlive()) {
                    switch (npc->getType()) {
                        case NPCType::ElfType:
                            fields[i + grid * j] = 'E';
                            break;
                        case NPCType::OutlawType:
                            fields[i + grid * j] = 'O';
                            break;
                        case NPCType::SquirrelType:
                            fields[i + grid * j] = 'S';
                            break;

                        default:
                            break;
                    }
                } else
                    fields[i + grid * j] = '.';
            }

            std::lock_guard<std::mutex> lck(print_mutex);
            for (int j = 0; j < grid; ++j) {
                for (int i = 0; i < grid; ++i) {
                    char c = fields[i + j * grid];
                    if (c != 0)
                        std::cout << "[" << c << "]";
                    else
                        std::cout << "[ ]";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    fight_thread.join();
    move_thread.join();

}
