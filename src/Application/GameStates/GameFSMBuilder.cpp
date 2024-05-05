#include "GameFSMBuilder.h"

#include <Engine/Engine.h>
#include <Engine/SaveLoad.h>
#include <Library/Fsm/FSMBuilder.h>

#include <utility>
#include <memory>

#include "CreditsState.h"
#include "InGameState.h"
#include "LoadSlotState.h"
#include "LoadStep2State.h"
#include "MainMenuState.h"
#include "PartyCreationState.h"
#include "VideoState.h"

std::unique_ptr<FSM> GameFSMBuilder::buildFSM() {
    FSMBuilder fsmBuilder;
    _buildIntroVideoSequence(fsmBuilder);
    _buildMainMenu(fsmBuilder);
    auto fsm = fsmBuilder.build();
    _setStartingState(*fsm);
    return std::move(fsm);
}

void GameFSMBuilder::_setStartingState(FSM &fsm) {
    GameConfig::Debug &debugConfig = engine->config->debug;
    std::string_view initialState = "LoadStep2";
    if (!debugConfig.NoVideo.value()) {
        if (!debugConfig.NoLogo.value()) {
            initialState = "3DOVideo";
        } else if (!debugConfig.NoIntro.value()) {
            initialState = "IntroVideo";
        }
    }
    fsm.jumpToState(initialState);
}

void GameFSMBuilder::_buildIntroVideoSequence(FSMBuilder &builder) {
    builder
    .state<VideoState>("3DOVideo", "3dologo")
        .on("videoEnd").jumpTo("NWCVideo")

    .state<VideoState>("NWCVideo", "new world logo")
        .on("videoEnd").jumpTo("JVCVideo")

    .state<VideoState>("JVCVideo", "jvc")
        .on("videoEnd")
            .jumpTo([]() { return !engine->config->debug.NoIntro.value(); }, "IntroVideo")
            .jumpTo(FSM::exitState)

    .state<VideoState>("IntroVideo", "Intro")
        .on("videoEnd").jumpTo("LoadStep2")

    .state<LoadStep2State>("LoadStep2")
        .on("done").jumpTo("MainMenu");
}

void GameFSMBuilder::_buildMainMenu(FSMBuilder &builder) {
    builder
    .state<MainMenuState>("MainMenu")
        .on("newGame").jumpTo("PartyCreation")
        .on("loadGame").jumpTo("LoadGame")
        .on("credits").jumpTo("Credits")
        .on("exit").jumpTo(FSM::exitState)

    .state<PartyCreationState>("PartyCreation")
        .on("partyCreated").jumpTo("NewGameIntro")
        .on("back").jumpTo("MainMenu")

    .state<VideoState>("NewGameIntro", "Intro Post")
        .on("videoEnd")
            .execute([](){ SaveNewGame(); })
            .jumpTo(FSM::exitState)

    .state<LoadSlotState>("LoadGame")
        .on("slotConfirmed").jumpTo(FSM::exitState)
        .on("back").jumpTo("MainMenu")

    .state<CreditsState>("Credits")
        .on("back").jumpTo("MainMenu");
        /*
    .state<PrepareGame>()
        on("proceed").jumpTo("Game")

    .state<InGameState>("Game")
        .on("backToMainMenu").jumpTo("MainMenu");
        */
}

void GameFSMBuilder::_buildGame(FSMBuilder &builder) {
}
