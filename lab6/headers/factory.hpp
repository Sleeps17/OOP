#pragma once

#include "NPC.hpp"
#include "elf.hpp"
#include "squirrel.hpp"
#include "outlaw.hpp"
#include "observers.hpp"


class Factory {
public:
    static std::shared_ptr<NPC> Create(const NPCType& npcType, int x, int y) {
        std::shared_ptr<NPC> result;
        switch (npcType) {
            case NPCType::SquirrelType:
                result = std::static_pointer_cast<NPC>(std::make_shared<Squirrel>(x, y));
                break;
            case NPCType::OutlawType:
                result =  std::static_pointer_cast<NPC>(std::make_shared<Outlaw>(x, y));
                break;
            case NPCType::ElfType:
                result = std::static_pointer_cast<NPC>(std::make_shared<Elf>(x, y));
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
                result = std::static_pointer_cast<NPC>(std::make_shared<Squirrel>(is));
                break;
            case NPCType::OutlawType:
                result = std::static_pointer_cast<NPC>(std::make_shared<Outlaw>(is));
                break;
            case NPCType::ElfType:
                result = std::static_pointer_cast<NPC>(std::make_shared<Elf>(is));
                break;
            default:
                result = nullptr;
        }

        if (result) {
            result -> subscribe(TextObserver::get());
            result -> subscribe(FileObserver::get());
        }

        return result;
    }
};