#pragma once

#include <Library/Fsm/FSMState.h>

class PrepareGameState : public FSMState {
 public:
    explicit PrepareGameState(bool isLoadedGame);
    virtual void update() override;
    virtual void enter() override;
    virtual void exit() override;

 private:
    bool _isLoadedGame;
};
