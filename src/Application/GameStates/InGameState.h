#pragma once

#include <Library/Fsm/FSMState.h>

class Game;

class InGameState : public FSMState {
 public:
    explicit InGameState(Game &game);
    virtual void update() override;
    virtual void enter() override;
    virtual void exit() override;

 private:
    void _onPartyDied();
    // TODO(Gerark) We're going to keep a reference to the game class but the idea is to remove it in the future.
    Game &_game;
};
