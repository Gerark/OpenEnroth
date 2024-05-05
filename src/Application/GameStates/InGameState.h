#pragma once

#include <Library/Fsm/FSMState.h>

class InGameState : public FSMState {
 public:
    InGameState();
    virtual void update() override;
    virtual void enter() override;
    virtual void exit() override;
};
