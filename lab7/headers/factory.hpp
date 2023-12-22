#pragma once
#include "NPC.hpp"
#include "elf.hpp"
#include "outlaw.hpp"
#include "squirrel.hpp"
#include "observers.hpp"

class Factory {
public:
    static std::shared_ptr<NPC> Create(const NPCType& type, const std::string& name, int x, int y) {
        std::shared_ptr<NPC> result;

        switch (type) {
                case NPCType::ElfType:
                    result = std::static_pointer_cast<NPC>(std::make_shared<Elf>(name, x, y));
                    break;

                case NPCType::OutlawType:
                    result = std::static_pointer_cast<NPC>(std::make_shared<Outlaw>(name, x, y));
                    break;

                case NPCType::SquirrelType:
                    result = std::static_pointer_cast<NPC>(std::make_shared<Squirrel>(name, x, y));
                    break;

                default:
                    break;
            }

        if (result) {
            result->subscribe(TextObserver::get());
            result->subscribe(FileObserver::get());
        }

        return result;
    }

    static std::shared_ptr<NPC> Create(const NPCType& type, std::istream& is) {
        std::shared_ptr<NPC> result;
        switch (type) {
            case NPCType::ElfType:
                result = std::static_pointer_cast<NPC>(std::make_shared<Elf>(is));
                break;

            case NPCType::OutlawType:
                result = std::static_pointer_cast<NPC>(std::make_shared<Outlaw>(is));
                break;

            case NPCType::SquirrelType:
                result = std::static_pointer_cast<NPC>(std::make_shared<Squirrel>(is));
                break;

            default:
                    break;
        }

        if (result) {
            result->subscribe(TextObserver::get());
            result->subscribe(FileObserver::get());
        }

        return result;
    }
};




