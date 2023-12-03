#pragma once

#include <memory>

#include "observers.hpp"
#include "NPC.hpp"

class Factory {
public:
    static std::shared_ptr<NPC> Create(const NPCType& npcType, int x, int y) {
        std::shared_ptr<NPC> result;
        switch (npcType) {
            case NPCType::SquirrelType:
                result = std::make_shared<Squirrel>(x, y);
                break;
            case NPCType::OutlawType:
                result =  std::make_shared<Outlaw>(x, y);
                break;
            case NPCType::ElfType:
                result = std::make_shared<Elf>(x, y);
                break;
            default:
                result =  nullptr;
        }

        if (result) {
            result -> subscribe(TextObserver::get());
            result -> subscribe(FileObserver::get());
        }

        return result;
    }
    static std::shared_ptr<NPC> Create(const NPCType& npcType, std::istream& is) {
        std::shared_ptr<NPC> result;
        switch (npcType) {
            case NPCType::SquirrelType:
                result = std::make_shared<Squirrel>(is);
                break;
            case NPCType::OutlawType:
                result = std::make_shared<Outlaw>(is);
                break;
            case NPCType::ElfType:
                result =  std::make_shared<Elf>(is);
                break;
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