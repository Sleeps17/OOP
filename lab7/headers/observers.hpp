#pragma once

#include <fstream>
#include <iostream>

#include "NPC.hpp"

class TextObserver: public NPCObserver {

private:
    TextObserver() = default;

public:
    static std::shared_ptr<NPCObserver> get() {
        static TextObserver instance;
        return {&instance, [](NPCObserver *) {}};
    }

    void onFight(const std::shared_ptr<const NPC>& attacker, const std::shared_ptr<NPC>& defender, bool win) override {
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
    FileObserver() = default;
public:
    static std::shared_ptr<NPCObserver> get() {
        static FileObserver instance;
        return {&instance, [](NPCObserver *) {}};
    }

    void onFight(const std::shared_ptr<const NPC>& attacker, const std::shared_ptr<NPC>& defender, bool win) override {
        if(win) {
            std::ofstream fs("log.txt", std::ios::app);
            fs << std::endl
               << "Murder --------" << std::endl;
            attacker->save(fs);
            defender->save(fs);
            fs.close();
        }
    }
};