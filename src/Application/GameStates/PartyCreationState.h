#pragma once

#include <Library/Fsm/FSMState.h>

#include <memory>

class Character;
class GUIWindow_PartyCreation;

class PartyCreationState : public FSMState {
 public:
    PartyCreationState();
    virtual void update() override;
    virtual void enter() override;
    virtual void exit() override;

 private:
    void _goBack();
    void _prepareParty();
    void _setupCharacterBasedOnSkills(Character &character);
    void _addRandomRing(Character &character);
    void _identifyAllStartingItems(Character &character);
    void _resetLastOpenedSpellBookPage(Character &character);

    std::unique_ptr<GUIWindow_PartyCreation> _uiPartyCreation;
};
