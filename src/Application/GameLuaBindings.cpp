#include "GameLuaBindings.h"

#include <string_view>
#include <memory>
#include <vector>
#include <ranges>
#include <optional>
#include <sol/sol.hpp>

#include "Engine/Party.h"
#include "Engine/Graphics/Renderer/Renderer.h"
#include "Engine/Tables/ItemTable.h"
#include "Engine/Random/Random.h"
#include "Library/Logger/Logger.h"
#include "Media/Audio/AudioPlayer.h"
#include "Media/Audio/SoundList.h"

#include "GUI/GUIWindow.h"

Character *getCharacterByIndex(int characterIndex);
sol::table createCharacterConditionTable(sol::state_view &luaState, const Character &character);
sol::table createCharacterSkillsTable(sol::state_view &luaState, const Character &character);

GameLuaBindings::GameLuaBindings() = default;
GameLuaBindings::~GameLuaBindings() = default;

void GameLuaBindings::init(lua_State *L) {
    _luaState = std::make_unique<sol::state_view>(L);

    //TODO(Gerark) exposing the info/stats of a character this way might suggest we should expose the Character class directly to lua.
    //The idea is to wait till we'll talk about serious modding/scripting and not taking a direction upfront
    _characterInfoQueryTable = std::make_unique<ItemQueryTable<Character>>(*_luaState);
    _characterInfoQueryTable->add("name", [](auto &character) { return character.name; });
    _characterInfoQueryTable->add("xp", [](auto &character) { return character.experience; });
    _characterInfoQueryTable->add("sp", [](auto &character) { return character.uSkillPoints; });
    _characterInfoQueryTable->add("mana", [](auto &character) { return character.GetMana(); });
    _characterInfoQueryTable->add("max_mana", [](auto &character) { return character.GetMaxMana(); });
    _characterInfoQueryTable->add("hp", [](auto &character) { return character.GetHealth(); });
    _characterInfoQueryTable->add("max_hp", [](auto &character) { return character.GetMaxHealth(); });
    _characterInfoQueryTable->add("condition", [this](auto &character) { return createCharacterConditionTable(*_luaState, character); });
    _characterInfoQueryTable->add("skills", [this](auto &character) { return createCharacterSkillsTable(*_luaState, character); });

    _luaState->set_function("initMMBindings", [this, luaState = _luaState.get()]() {
        sol::table mainTable = luaState->create_table();
        _registerGameBindings(*luaState, mainTable);
        _registerPartyBindings(*luaState, mainTable);
        _registerItemBindings(*luaState, mainTable);
        _registerAudioBindings(*luaState, mainTable);
        _registerSerializationBindings(*luaState, mainTable);
        _registerRenderBindings(*luaState, mainTable);
        _registerEnums(*luaState, mainTable);
        return mainTable;
    });
}

void GameLuaBindings::_registerGameBindings(sol::state_view &luaState, sol::table &table) {
    table["game"] = luaState.create_table_with(
        "go_to_screen", [](int screenIndex) {
            SetCurrentMenuID(MenuType(screenIndex));
        }
    );
}

void GameLuaBindings::_registerPartyBindings(sol::state_view &luaState, sol::table &table) {
    table["party"] = luaState.create_table_with(
        "get_gold", []() {
            return pParty->GetGold();
        },
        "set_gold", [](int amount) {
            pParty->SetGold(amount);
        },
        "get_food", []() {
            return pParty->GetFood();
        },
        "set_food", [](int food) {
            pParty->SetFood(food);
        },
        "get_alignment", []() {
            return pParty->alignment;
        },
        "set_alignment", [](PartyAlignment alignment) {
            pParty->alignment = alignment;
            SetUserInterface(pParty->alignment);
        },
        "give_party_xp", [](int amount) {
            pParty->GivePartyExp(amount);
        },
        "get_party_size", []() {
            return pParty->pCharacters.size();
        },
        "get_active_character", []() {
            if(pParty->hasActiveCharacter()) {
                int index = pParty->activeCharacterIndex();
                assert(index != 0); //keep an assert here in case we change the 1-based index to 0 in the future so we can adjust it accordingly
                return index; //a 1-based index is totally fine for lua
            } else {
                return 0;
            }
        },
        "get_character_info", [this, &luaState](int characterIndex, const sol::object &queryTable) {
            if(Character *character = getCharacterByIndex(characterIndex - 1); character != nullptr) {
                return _characterInfoQueryTable->createTable(*character, queryTable);
            }
            return sol::make_object(luaState, sol::lua_nil);
        },
        "set_character_info", [](int characterIndex, const sol::object &info) {
            if(Character *character = getCharacterByIndex(characterIndex - 1); character != nullptr) {
                const sol::table &table = info.as<sol::table>();
                for (auto &&val : table) {
                    std::string_view key = val.first.as<std::string_view>();
                    if (key == "xp") {
                        character->experience = val.second.as<int>();
                    } else if(key == "sp") {
                        character->uSkillPoints = val.second.as<int>();
                    } else if(key == "hp") {
                        character->health = val.second.as<int>();
                    } else if(key == "mana") {
                        character->mana = val.second.as<int>();
                    } else if (key == "condition") {
                        character->SetCondition(val.second.as<Condition>(), false);
                    } else if (key == "skill") {
                        sol::table skillValueTable = val.second.as<sol::table>();
                        CombinedSkillValue current = character->getActualSkillValue(skillValueTable["id"]);
                        auto level = skillValueTable.get<std::optional<int>>("level");
                        auto mastery = skillValueTable.get<std::optional<CharacterSkillMastery>>("mastery");
                        CombinedSkillValue skillValue(
                            level ? *level : current.level(),
                            mastery ? *mastery : current.mastery()
                        );
                        character->setSkillValue(skillValueTable["id"], skillValue);
                    } else {
                        logger->warning("Invalid key for set_character_info. Used key: {}", key);
                    }
                }
            }
        },
        "add_item_to_inventory", [](int characterIndex, ItemId itemId) {
            if(Character *character = getCharacterByIndex(characterIndex - 1); character != nullptr) {
                return character->AddItem(-1, itemId) != 0;
            }
            return false;
        },
        "play_all_characters_award_sound", []() {
            for (auto &&character : pParty->pCharacters) {
                character.PlayAwardSound_Anim();
            }
        },
        "play_character_award_sound", [](int characterIndex) {
            if(Character *character = getCharacterByIndex(characterIndex - 1); character != nullptr) {
                character->PlayAwardSound_Anim();
            }
        },
        "clear_condition", [](int characterIndex, std::optional<Condition> conditionToClear) {
            if(Character* character = getCharacterByIndex(characterIndex - 1); character != nullptr) {
                if (conditionToClear) {
                    character->conditions.Reset(*conditionToClear);
                } else {
                    character->conditions.ResetAll();
                }
            }
        }
    );
}

void GameLuaBindings::_registerAudioBindings(sol::state_view &luaState, sol::table &table) {
    table["audio"] = luaState.create_table_with(
        "playSound", [](SoundId soundId, SoundPlaybackMode mode) {
            pAudioPlayer->playSound(soundId, mode);
        },
        "playMusic", [](MusicId musicId) {
            pAudioPlayer->MusicPlayTrack(musicId);
        }
    );
}

void GameLuaBindings::_registerItemBindings(sol::state_view &luaState, sol::table &table) {
    typedef std::function<bool(ItemId)> FilteItemFunction;

    auto createItemTable = [&luaState](const ItemDesc &itemDesc) {
        return luaState.create_table_with(
            "name", itemDesc.name,
            "level", itemDesc.uItemID_Rep_St
        );
    };

    table["items"] = luaState.create_table_with(
        "get_item_info", [&luaState, createItemTable](ItemId itemId) {
            if(itemId >= ITEM_FIRST_VALID && itemId <= ITEM_LAST_VALID) {
                const ItemDesc &itemDesc = pItemTable->pItems[itemId];
                return sol::object(luaState, createItemTable(itemDesc));
            }
            return sol::make_object(luaState, sol::lua_nil);
        },
        // The get_random_item function accept an optional filter function to exclude some items from the randomization
        "get_random_item", [](const FilteItemFunction &filter) {
            if(filter) {
                std::vector<ItemId> itemsToRandomizeOn;
                Segment<ItemId> &&spawnableItems = allSpawnableItems();
                for (ItemId itemId : spawnableItems | std::views::filter(filter)) {
                    itemsToRandomizeOn.push_back(itemId);
                }
                return grng->randomSample(itemsToRandomizeOn);
            }
            return grng->randomSample(allSpawnableItems());
        }
    );
}

void GameLuaBindings::_registerSerializationBindings(sol::state_view &luaState, sol::table &table) {
    //Exposing serializations and deserializations functions to lua
    //Useful for converting command line strings to the correct types
    table["deserialize"] = luaState.create_table_with(
        "party_alignment", [](std::string_view alignment) {
            return fromString<PartyAlignment>(alignment);
        }
    );

    table["serialize"] = luaState.create_table_with(
        "party_alignment", [](PartyAlignment alignment) {
            return toString(alignment);
        }
    );
}

void GameLuaBindings::_registerRenderBindings(sol::state_view &luaState, sol::table &table) {
    table["render"] = luaState.create_table_with(
        "reload_shaders", [](std::string_view alignment) {
            render->ReloadShaders();
        }
    );
}

void GameLuaBindings::_registerEnums(sol::state_view &luaState, sol::table &table) {
    //TODO(captainurist): Use serialization tables to automate this.
    table.new_enum<false>("PartyAlignment",
        "Good", PartyAlignment::PartyAlignment_Good,
        "Neutral", PartyAlignment::PartyAlignment_Neutral,
        "Evil", PartyAlignment::PartyAlignment_Evil
    );

    table.new_enum<false>("CharacterCondition",
        "Cursed", CONDITION_CURSED,
        "Weak", CONDITION_WEAK,
        "Sleep", CONDITION_SLEEP,
        "Fear", CONDITION_FEAR,
        "Drunk", CONDITION_DRUNK,
        "Insane", CONDITION_INSANE,
        "Poison_weak", CONDITION_POISON_WEAK,
        "Disease_weak", CONDITION_DISEASE_WEAK,
        "Poison_medium", CONDITION_POISON_MEDIUM,
        "Disease_medium", CONDITION_DISEASE_MEDIUM,
        "Poison_severe", CONDITION_POISON_SEVERE,
        "Disease_severe", CONDITION_DISEASE_SEVERE,
        "Paralyzed", CONDITION_PARALYZED,
        "Unconscious", CONDITION_UNCONSCIOUS,
        "Dead", CONDITION_DEAD,
        "Petriefied", CONDITION_PETRIFIED,
        "Eradicated", CONDITION_ERADICATED,
        "Zombie", CONDITION_ZOMBIE,
        "Good", CONDITION_GOOD
    );

    table.new_enum<false>("SkillType",
        "Staff", CHARACTER_SKILL_STAFF,
        "Sword", CHARACTER_SKILL_SWORD,
        "Dagger", CHARACTER_SKILL_DAGGER,
        "Axe", CHARACTER_SKILL_AXE,
        "Spear", CHARACTER_SKILL_SPEAR,
        "Bow", CHARACTER_SKILL_BOW,
        "Mace", CHARACTER_SKILL_MACE,
        "Blaster", CHARACTER_SKILL_BLASTER,
        "Shield", CHARACTER_SKILL_SHIELD,
        "Leather", CHARACTER_SKILL_LEATHER,
        "Chain", CHARACTER_SKILL_CHAIN,
        "Plate", CHARACTER_SKILL_PLATE,
        "Fire", CHARACTER_SKILL_FIRE,
        "Air", CHARACTER_SKILL_AIR,
        "Water", CHARACTER_SKILL_WATER,
        "Earth", CHARACTER_SKILL_EARTH,
        "Spirit", CHARACTER_SKILL_SPIRIT,
        "Mind", CHARACTER_SKILL_MIND,
        "Body", CHARACTER_SKILL_BODY,
        "Light", CHARACTER_SKILL_LIGHT,
        "Dark", CHARACTER_SKILL_DARK,
        "Item_ID", CHARACTER_SKILL_ITEM_ID,
        "Merchant", CHARACTER_SKILL_MERCHANT,
        "Repair", CHARACTER_SKILL_REPAIR,
        "Bodybuilding", CHARACTER_SKILL_BODYBUILDING,
        "Meditation", CHARACTER_SKILL_MEDITATION,
        "Perception", CHARACTER_SKILL_PERCEPTION,
        "Diplomacy", CHARACTER_SKILL_DIPLOMACY,
        "Thievery", CHARACTER_SKILL_THIEVERY,
        "Trap_Disarm", CHARACTER_SKILL_TRAP_DISARM,
        "Dodge", CHARACTER_SKILL_DODGE,
        "Unarmed", CHARACTER_SKILL_UNARMED,
        "Monster_ID", CHARACTER_SKILL_MONSTER_ID,
        "Armsmaster", CHARACTER_SKILL_ARMSMASTER,
        "Stealing", CHARACTER_SKILL_STEALING,
        "Alchemy", CHARACTER_SKILL_ALCHEMY,
        "Learning", CHARACTER_SKILL_LEARNING,
        "Club", CHARACTER_SKILL_CLUB,
        "Misc", CHARACTER_SKILL_MISC
    );

    table.new_enum<false>("SkillMastery",
        "None", CHARACTER_SKILL_MASTERY_NONE,
        "Novice", CHARACTER_SKILL_MASTERY_NOVICE,
        "Expert", CHARACTER_SKILL_MASTERY_EXPERT,
        "Master", CHARACTER_SKILL_MASTERY_MASTER,
        "Grandmaster", CHARACTER_SKILL_MASTERY_GRANDMASTER
    );
}

Character *getCharacterByIndex(int characterIndex) {
    if (characterIndex >= 0 && characterIndex < pParty->pCharacters.size()) {
        return &pParty->pCharacters[characterIndex];
    }

    logger->warning("Invalid character index. Asked for: {} but the party size is: {}", characterIndex, pParty->pCharacters.size());
    return nullptr;
}

sol::table createCharacterConditionTable(sol::state_view &luaState, const Character &character) {
    sol::table result = luaState.create_table();

    // I would have preferred to iterate over the internal IndexedArray keeping track of all the conditions but it's private.
    for (int i = (int)Condition::CONDITION_FIRST; i < (int)Condition::CONDITION_LAST; ++i) {
        if (character.conditions.Has(static_cast<Condition>(i))) {
            result[i] = true;
        }
    }
    return result;
}

sol::table createCharacterSkillsTable(sol::state_view &luaState, const Character &character) {
    sol::table result = luaState.create_table();
    for (CharacterSkillType skillType : character.pActiveSkills.indices()) {
        if (character.HasSkill(skillType)) {
            CombinedSkillValue skillValue = character.getActualSkillValue(skillType);
            result[skillType] = luaState.create_table_with(
                "level", skillValue.level(),
                "mastery", skillValue.mastery()
            );
        }
    }
    return result;
}
