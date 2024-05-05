#include "InGameState.h"

#include <Engine/Engine.h>
#include <Engine/Graphics/ParticleEngine.h>
#include <Engine/Graphics/DecalBuilder.h>
#include <Engine/Graphics/LightmapBuilder.h>
#include <Engine/Graphics/LightsStack.h>
#include <Io/KeyboardInputHandler.h>

#include <string>

InGameState::InGameState() {
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
    processQueuedMessages();

    /* ArcomageGame should have its own state
    if (pArcomageGame->bGameInProgress) {
        ArcomageGame::Loop();
        render->Present();
        continue;
    }
    */

    /*
    MessageLoopWithWait();


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
        continue;
    }

    if (uGameState == GAME_STATE_CHANGE_LOCATION) {
        pAudioPlayer->stopSounds();
        PrepareWorld(0);
        uGameState = GAME_STATE_PLAYING;
        continue;
    }

    // if ((signed int)uGameState <= GAME_STATE_5 || uGameState ==
    // GAME_STATE_GAME_QUITTING_TO_MAIN_MENU)//GAME_STATE_NEWGAME_OUT_GAMEMENU,
    // GAME_STATE_LOADING_GAME
    if (uGameState == GAME_STATE_LOADING_GAME ||
        uGameState == GAME_STATE_NEWGAME_OUT_GAMEMENU ||
        uGameState == GAME_STATE_5 ||
        uGameState == GAME_STATE_GAME_QUITTING_TO_MAIN_MENU ||
        uGameState == GAME_FINISHED) {
        game_finished = true;
        continue;
    }
    if (uGameState == GAME_STATE_FINAL_WINDOW) {
        render->BeginScene2D();
        GUI_UpdateWindows();
        render->Present();
        continue;
    }
    if (uGameState != GAME_STATE_PARTY_DIED) {
        engine->Draw();  // when could this occur - can it be dropped?
        continue;
    }
    if (uGameState == GAME_STATE_PARTY_DIED) {
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

        if (pParty->_questBits[QBIT_ESCAPED_EMERALD_ISLE]) {
            pParty->pos = Vec3f(-17331, 12547, 465); // respawn in harmondale
            pParty->_viewYaw = 0;
            pLocationName = "out02.odm";
        } else {
            pParty->pos = Vec3f(12552, 1816, 193); // respawn on emerald isle
            pParty->_viewYaw = 512;
            pLocationName = _config->gameplay.StartingMap.value();
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

        // need to clear messages here??
    }
    */
}

void InGameState::exit() {
}
