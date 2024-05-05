#include "InGameState.h"

#include <Application/Game.h>
#include <Arcomage/Arcomage.h>
#include <Engine/Engine.h>
#include <Engine/Events/Processor.h>
#include <Engine/Objects/Actor.h>
#include <Engine/Graphics/ParticleEngine.h>
#include <Engine/Graphics/DecalBuilder.h>
#include <Engine/Graphics/LightmapBuilder.h>
#include <Engine/Graphics/LightsStack.h>
#include <Engine/Graphics/Overlays.h>
#include <Engine/Graphics/TurnBasedOverlay.h>
#include <Engine/Party.h>
#include <Engine/Random/Random.h>
#include <Engine/Tables/AwardTable.h>
#include <Engine/TurnEngine/TurnEngine.h>
#include <Io/KeyboardInputHandler.h>
#include <Media/Audio/AudioPlayer.h>
#include <Media/MediaPlayer.h>
#include <GUI/UI/UIStatusBar.h>
#include <GUI/UI/UIGame.h>

#include <string>

InGameState::InGameState(Game &game) : _game(game) {
}

void InGameState::enter() {
}

void InGameState::update() {
    engine->particle_engine->UpdateParticles();
    engine->decal_builder->bloodsplat_container->uNumBloodsplats = 0;
    if (engine->uNumStationaryLights_in_pStationaryLightsStack != pStationaryLightsStack->uNumLightsActive) {
        engine->uNumStationaryLights_in_pStationaryLightsStack = pStationaryLightsStack->uNumLightsActive;
    }

    keyboardInputHandler->GenerateInputActions();
    _game.processQueuedMessages();

    // TODO(Gerark) ArcomageGame should have its own state
    /*
    if (pArcomageGame->bGameInProgress) {
        ArcomageGame::Loop();
        render->Present();
        return;
    }
    */

    pMediaPlayer->HouseMovieLoop();

    pEventTimer->tick();
    pMiscTimer->tick();

    if (pMiscTimer->isPaused() && !pEventTimer->isPaused())
        pMiscTimer->setPaused(false);
    if (pEventTimer->isTurnBased() && !pParty->bTurnBasedModeOn)
        pEventTimer->setTurnBased(false);
    if (!pEventTimer->isPaused() && uGameState == GAME_STATE_PLAYING) {
        onTimer();

        if (!pEventTimer->isTurnBased()) {
            _494035_timed_effects__water_walking_damage__etc(pEventTimer->dt());
        } else {
            // Need to process party death in turn-based mode.
            maybeWakeSoloSurvivor();
            updatePartyDeathState();
        }

        if (dword_6BE364_game_settings_1 & GAME_SETTINGS_SKIP_WORLD_UPDATE) {
            dword_6BE364_game_settings_1 &= ~GAME_SETTINGS_SKIP_WORLD_UPDATE;
        } else {
            Actor::UpdateActorAI();
            UpdateUserInput_and_MapSpecificStuff();
        }
    }

    pAudioPlayer->UpdateSounds();

    GameUI_WritePointedObjectStatusString();
    engine->_statusBar->update();
    turnBasedOverlay.update(pMiscTimer->dt(), pTurnEngine->turn_stage);

    if (uGameState == GAME_STATE_PLAYING) {
        engine->Draw();
        return;
    }

    if (uGameState == GAME_STATE_CHANGE_LOCATION) {
        // TODO(Gerark) this should be a transition to loading state
        pAudioPlayer->stopSounds();
        PrepareWorld(0);
        uGameState = GAME_STATE_PLAYING;
        return;
    }

    //TODO(Gerark) Not the final version. Some of these transitions should happen elsewhere.
    //For example: starting a new game from the pause menu should be a transition happening in a PauseMenuState.
    //The IngameState shouldn't even be aware of that.
    if (uGameState == GAME_STATE_LOADING_GAME ||
        uGameState == GAME_STATE_5) {
        executeTransition("loadGame");
        return;
    } else if (uGameState == GAME_STATE_NEWGAME_OUT_GAMEMENU) {
        executeTransition("newGame");
        return;
    } else if (
        uGameState == GAME_STATE_GAME_QUITTING_TO_MAIN_MENU ||
        uGameState == GAME_FINISHED) {
        executeTransition("back");
        return;
    }

    if (uGameState == GAME_STATE_FINAL_WINDOW) {
        // TODO(Gerark) this should be a transition to a new state
        //render->BeginScene2D();
        //GUI_UpdateWindows();
        //render->Present();
        return;
    }
    if (uGameState != GAME_STATE_PARTY_DIED) {
        // TODO(Gerark) I'm going to drop this after a little investigation to confirm it's useless
        engine->Draw();  // when could this occur - can it be dropped?
        return;
    }
    if (uGameState == GAME_STATE_PARTY_DIED) {
        // TODO(Gerark) this should be a transition to another state
        _onPartyDied();
    }
}

void InGameState::exit() {
    pEventTimer->setPaused(true);
    engine->ResetCursor_Palettes_LODs_Level_Audio_SFT_Windows();
}

void InGameState::_onPartyDied() {
    pAudioPlayer->stopSounds();
    pParty->pHirelings[0] = NPCData();
    pParty->pHirelings[1] = NPCData();
    for (int i = 0; i < (signed int)pNPCStats->uNumNewNPCs; ++i) {
        if (pNPCStats->pNPCData[i].field_24)
            pNPCStats->pNPCData[i].uFlags &= ~NPC_HIRED;
    }
    pMediaPlayer->PlayFullscreenMovie("losegame");
    if (pMovie_Track)
        pMediaPlayer->Unload();
    ++pParty->uNumDeaths;
    for (Character &character : pParty->pCharacters) {
        character.SetVariable(VAR_Award, Award_Deaths);
    }
    pParty->days_played_without_rest = 0;
    pParty->GetPlayingTime() += Duration::fromDays(7);  // += 2580480
    pParty->uFlags &= ~(PARTY_FLAG_WATER_DAMAGE | PARTY_FLAG_BURNING);
    pParty->SetGold(0);
    pActiveOverlayList->Reset();
    pParty->pPartyBuffs.fill(SpellBuff());

    if (pParty->bTurnBasedModeOn) {
        pTurnEngine->End(true);
        pParty->bTurnBasedModeOn = false;
    }
    for (Character &character : pParty->pCharacters) {
        character.conditions.ResetAll();
        character.pCharacterBuffs.fill(
            SpellBuff());  // ???
        // memset(pParty->pCharacters[i].conditions_times.data(),
        // 0, 0xA0u);//(pConditions, 0, 160)
        // memset(pParty->pCharacters[i].pCharacterBuffs.data(),
        // 0, 0x180u);//(pCharacterBuffs[0], 0, 384)
        character.health = 1;
    }
    pParty->setActiveCharacterIndex(1);

    std::string pLocationName;
    std::string Source;
    if (pParty->_questBits[QBIT_ESCAPED_EMERALD_ISLE]) {
        pParty->pos = Vec3f(-17331, 12547, 465); // respawn in harmondale
        pParty->_viewYaw = 0;
        pLocationName = "out02.odm";
    } else {
        pParty->pos = Vec3f(12552, 1816, 193); // respawn on emerald isle
        pParty->_viewYaw = 512;
        pLocationName = engine->config->gameplay.StartingMap.value();
    }
    Source = pLocationName;
    pParty->uFallStartZ = pParty->pos.z;
    pParty->_viewPitch = 0;
    pParty->velocity = Vec3f();
    // change map
    if (pCurrentMapName != Source) {
        pCurrentMapName = Source;
        engine->_teleportPoint.setTeleportTarget(pParty->pos.toInt(), pParty->_viewYaw, pParty->_viewPitch, 0);
        PrepareWorld(1);
    }
    pMiscTimer->setPaused(false);
    pEventTimer->setPaused(false);

    Actor::InitializeActors();

    int playerId = pParty->getRandomActiveCharacterId(vrng);

    if (playerId != -1) {
        pParty->pCharacters[playerId].playReaction(SPEECH_CHEATED_DEATH);
    }

    engine->_statusBar->setEvent(LSTR_CHEATED_THE_DEATH);
    uGameState = GAME_STATE_PLAYING;
}
