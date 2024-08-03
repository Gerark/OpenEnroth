#include "PartyCreationState.h"

#include <Engine/Engine.h>
#include <Engine/Graphics/Overlays.h>
#include <Engine/Time/Timer.h>
#include <Engine/Party.h>
#include <Engine/Random/Random.h>
#include <Engine/Spells/SpellEnumFunctions.h>
#include <Engine/Tables/ItemTable.h>
#include <Engine/TurnEngine/TurnEngine.h>
#include <GUI/UI/UIPartyCreation.h>
#include <GUI/UI/UIGame.h>
#include <Library/Logger/Logger.h>
#include <Media/Audio/AudioPlayer.h>

#include <memory>

PartyCreationState::PartyCreationState() {
}

FsmAction PartyCreationState::enter() {
    pActiveOverlayList->Reset();

    pAudioPlayer->MusicStop();
    pEventTimer->setPaused(true);

    // This call is here b/c otherwise Character::timeToRecovery will be overwritten in the main loop from the
    // turn-based queue if we're currently in turn-based combat.
    pTurnEngine->End(false);

    pParty->Reset();
    pParty->createDefaultParty();

    pNPCStats->pNPCData = pNPCStats->pOriginalNPCData;
    pNPCStats->pGroups = pNPCStats->pOriginalGroups;
    pNPCStats->pNPCData[3].uFlags |= NPC_HIRED; // Lady Margaret.

    _uiPartyCreation = std::make_unique<GUIWindow_PartyCreation>();
    _uiPartyCreation->keyboard_input_status = WINDOW_INPUT_NONE;

    // Unfortunately there's a need to set this global pointer if we don't want to refactor the entire SaveLoad UI ( not worth it right now )
    pGUIWindow_CurrentMenu = _uiPartyCreation.get();

    SetCurrentMenuID(MENU_CREATEPARTY);

    return FsmAction::none();
}

FsmAction PartyCreationState::update() {
    pMiscTimer->tick(); // This one is used for animations.

    // TODO(Gerark) Not ideal to call this function, It's preferable to manage the events directly in the state
    // And then dispatch only the relevant info to the UI. By doing so we'll be able to get rid of
    // the checks on the uGameState and return the transition instead.
    CreateParty_EventLoop();

    if (uGameState == GAME_FINISHED) {  // if click Esc in PlayerCreation Window
        uGameState = GAME_STATE_PLAYING;
        SetCurrentMenuID(MENU_MAIN);
        // TODO(Gerark) Remove this GUI_UpdateWindows once we have a proper Retained Mode UI system.
        // Right now we're forced to call this to cause the proper removal of temporary "buttons"
        GUI_UpdateWindows();
        return FsmAction::transition("back");
    }
    if (uGameState == GAME_STATE_STARTING_NEW_GAME) {  // if click OK in PlayerCreation
        uGameState = GAME_STATE_PLAYING;
        SetCurrentMenuID(MENU_NEWGAME);
        _prepareParty();
        bFlashQuestBook = true;
        // TODO(Gerark) Remove this GUI_UpdateWindows once we have a proper Retained Mode UI system.
        // Right now we're forced to call this to cause the proper removal of temporary "buttons"
        GUI_UpdateWindows();
        return FsmAction::transition("partyCreated");
    }

    return FsmAction::none();
}

void PartyCreationState::exit() {
    _uiPartyCreation->Release();
    _uiPartyCreation.reset();
    pGUIWindow_CurrentMenu = nullptr;
    pAudioPlayer->stopSounds();
}

void PartyCreationState::_prepareParty() {
    for (Character &character : pParty->pCharacters) {
        if (character.classType == CLASS_KNIGHT)
            character.sResMagicBase = 10;

        // TODO(pskelton): why just CHARACTER_BUFF_RESIST_WATER?
        character.pCharacterBuffs[CHARACTER_BUFF_RESIST_WATER].Reset();

        character.resetToFullHealth();
        character.resetToFullMana();

        _resetLastOpenedSpellBookPage(character);
        _addRandomRing(character);
        _setupCharacterBasedOnStartingSkills(character);
        _identifyAllStartingItems(character);
    }

    pParty->pPickedItem.uItemID = ITEM_NULL;

    if (engine->config->debug.NoMargaret.value()) {
        pParty->_questBits.set(QBIT_EMERALD_ISLAND_MARGARETH_OFF);
    }
}

void PartyCreationState::_addRandomRing(Character &character) {
    ItemGen item;
    pItemTable->generateItem(ITEM_TREASURE_LEVEL_2, RANDOM_ITEM_RING, &item);
    character.AddItem2(-1, &item);
}

void PartyCreationState::_setupCharacterBasedOnStartingSkills(Character &character) {
    for (CharacterSkillType j : allSkills()) {
        if (!character.pActiveSkills[j]) continue;

        switch (j) {
        case CHARACTER_SKILL_STAFF:
            character.AddItem(-1, ITEM_STAFF);
            break;
        case CHARACTER_SKILL_SWORD:
            character.AddItem(-1, ITEM_CRUDE_LONGSWORD);
            break;
        case CHARACTER_SKILL_DAGGER:
            character.AddItem(-1, ITEM_DAGGER);
            break;
        case CHARACTER_SKILL_AXE:
            character.AddItem(-1, ITEM_CRUDE_AXE);
            break;
        case CHARACTER_SKILL_SPEAR:
            character.AddItem(-1, ITEM_CRUDE_SPEAR);
            break;
        case CHARACTER_SKILL_BOW:
            character.AddItem(-1, ITEM_CROSSBOW);
            break;
        case CHARACTER_SKILL_MACE:
            character.AddItem(-1, ITEM_MACE);
            break;
        case CHARACTER_SKILL_BLASTER:
            logger->error("No blasters at startup :p");
            break;
        case CHARACTER_SKILL_SHIELD:
            character.AddItem(-1, ITEM_WOODEN_BUCKLER);
            break;
        case CHARACTER_SKILL_LEATHER:
            character.AddItem(-1, ITEM_LEATHER_ARMOR);
            break;
        case CHARACTER_SKILL_CHAIN:
            character.AddItem(-1, ITEM_CHAIN_MAIL);
            break;
        case CHARACTER_SKILL_PLATE:
            character.AddItem(-1, ITEM_PLATE_ARMOR);
            break;
        case CHARACTER_SKILL_FIRE:
            character.AddItem(-1, ITEM_SPELLBOOK_FIRE_BOLT);
            character.bHaveSpell[SPELL_FIRE_TORCH_LIGHT] = true;
            break;
        case CHARACTER_SKILL_AIR:
            character.AddItem(-1, ITEM_SPELLBOOK_FEATHER_FALL);
            character.bHaveSpell[SPELL_AIR_WIZARD_EYE] = true;
            break;
        case CHARACTER_SKILL_WATER:
            character.AddItem(-1, ITEM_SPELLBOOK_POISON_SPRAY);
            character.bHaveSpell[SPELL_WATER_AWAKEN] = true;
            break;
        case CHARACTER_SKILL_EARTH:
            character.AddItem(-1, ITEM_SPELLBOOK_SLOW);
            character.bHaveSpell[SPELL_EARTH_STUN] = true;
            break;
        case CHARACTER_SKILL_SPIRIT:
            character.AddItem(-1, ITEM_SPELLBOOK_BLESS);
            character.bHaveSpell[SPELL_SPIRIT_DETECT_LIFE] = true;
            break;
        case CHARACTER_SKILL_MIND:
            character.AddItem(-1, ITEM_SPELLBOOK_MIND_BLAST);
            character.bHaveSpell[SPELL_MIND_REMOVE_FEAR] = true;
            break;
        case CHARACTER_SKILL_BODY:
            character.AddItem(-1, ITEM_SPELLBOOK_HEAL);
            character.bHaveSpell[SPELL_BODY_CURE_WEAKNESS] = true;
            break;
        case CHARACTER_SKILL_LIGHT:
        case CHARACTER_SKILL_DARK:
            logger->error("No light/dark magic at startup");
            break;
        case CHARACTER_SKILL_DIPLOMACY:
            logger->error("No diplomacy in mm7 (yet)");
            break;
        case CHARACTER_SKILL_ITEM_ID:
        case CHARACTER_SKILL_REPAIR:
        case CHARACTER_SKILL_MEDITATION:
        case CHARACTER_SKILL_PERCEPTION:
        case CHARACTER_SKILL_TRAP_DISARM:
        case CHARACTER_SKILL_LEARNING:
            character.AddItem(-1, ITEM_POTION_BOTTLE);
            character.AddItem(-1, grng->randomSample(allLevel1Reagents()));
            break;
        case CHARACTER_SKILL_DODGE:
            character.AddItem(-1, ITEM_LEATHER_BOOTS);
            break;
        case CHARACTER_SKILL_UNARMED:
            character.AddItem(-1, ITEM_GAUNTLETS);
            break;
        case CHARACTER_SKILL_CLUB:
            // character.AddItem(-1, ITEM_CLUB);
            break;
        default:
            break;
        }
    }
}

void PartyCreationState::_identifyAllStartingItems(Character &character) {
    for (ItemGen &inventoryItem : character.pInventoryItemList) {
        if (inventoryItem.uItemID != ITEM_NULL)
            inventoryItem.SetIdentified();
    }
}

void PartyCreationState::_resetLastOpenedSpellBookPage(Character &character) {
    for (MagicSchool page : allMagicSchools()) {
        if (character.pActiveSkills[skillForMagicSchool(page)]) {
            character.lastOpenedSpellbookPage = page;
            break;
        }
    }
}
