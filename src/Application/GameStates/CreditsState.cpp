#include "CreditsState.h"

#include <Media/Audio/AudioPlayer.h>
#include <Engine/Engine.h>
#include <GUI/GUIMessageQueue.h>
#include <GUI/UI/UICredits.h>

#include <memory>

CreditsState::CreditsState() {
}

void CreditsState::enter() {
    pAudioPlayer->MusicStop();
    engine->_messageQueue->clear();

    pAudioPlayer->MusicPlayTrack(MUSIC_CREDITS);

    _uiCredits = std::make_unique<GUICredits>([this]() {
        _goBack();
    });
    current_screen_type = SCREEN_CREATORS;
    SetCurrentMenuID(MENU_CREDITSPROC);
}

void CreditsState::update() {
    while (engine->_messageQueue->haveMessages()) {
        UIMessageType messageType;
        engine->_messageQueue->popMessage(&messageType, nullptr, nullptr);

        if (messageType == UIMSG_Escape) {
            _goBack();
        }
    }
}

void CreditsState::exit() {
    _uiCredits->Release();
    _uiCredits.reset();

    pAudioPlayer->MusicStop();
    pAudioPlayer->stopSounds();
}

void CreditsState::_goBack() {
    executeTransition("back");
    SetCurrentMenuID(MENU_MAIN);
}