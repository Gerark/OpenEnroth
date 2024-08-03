#pragma once

#include <Library/Fsm/FsmState.h>
#include <GUI/UI/UIPartyCreation.h>

#include <memory>

class Character;
class GUIWindow_PartyCreation;

class PartyCreationState : public FsmState {
 public:
    PartyCreationState();
    virtual FsmAction update() override;
    virtual FsmAction enter() override;
    virtual void exit() override;

 private:
    void _prepareParty();
    void _setupCharacterBasedOnStartingSkills(Character &character);
    void _addRandomRing(Character &character);
    void _identifyAllStartingItems(Character &character);
    void _resetLastOpenedSpellBookPage(Character &character);

    std::unique_ptr<GUIWindow_PartyCreation> _uiPartyCreation;
};
