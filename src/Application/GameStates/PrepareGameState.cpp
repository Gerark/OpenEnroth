#include "PrepareGameState.h"

#include <Engine/Engine.h>
#include <Engine/LodTextureCache.h>
#include <Engine/Party.h>
#include <Engine/SaveLoad.h>
#include <Engine/TurnEngine/TurnEngine.h>
#include <GUI/GUIWindow.h>
#include <GUI/GUIMessageQueue.h>
#include <GUI/UI/UIGame.h>

PrepareGameState::PrepareGameState(bool isLoadedGame) : _isLoadedGame(isLoadedGame) {
}

void PrepareGameState::enter() {
    /*
    * Extracted from Game::gameLoop()
    */
    SetCurrentMenuID(MENU_NONE);
    if (_isLoadedGame) {
        uGameState = GAME_STATE_PLAYING;
        LoadGame(pSavegameList->selectedSlot);
    }

    extern bool use_music_folder;
    GameUI_LoadPlayerPortraintsAndVoices();
    pIcons_LOD->reserveLoadedTextures();

    engine->_messageQueue->clear();

    pPartyActionQueue->uNumActions = 0;

    pTurnEngine->End(false);
    pParty->bTurnBasedModeOn = false;  // Make sure turn engine and party turn based mode flag are in sync.

    DoPrepareWorld(_isLoadedGame, 1);
    pEventTimer->setPaused(false);
    dword_6BE364_game_settings_1 |= GAME_SETTINGS_0080_SKIP_USER_INPUT_THIS_FRAME;

    current_screen_type = SCREEN_GAME;

    executeTransition("proceed");
}

void PrepareGameState::update() {
}

void PrepareGameState::exit() {
}
