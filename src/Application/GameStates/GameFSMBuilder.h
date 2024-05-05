#pragma once

#include <memory>

class FSM;
class FSMBuilder;
class Game;

class GameFSMBuilder {
 public:
    static std::unique_ptr<FSM> buildFSM(Game &game);

 private:
    static void _buildIntroVideoSequence(FSMBuilder &fsmBuilder);
    static void _buildMainMenu(FSMBuilder &fsmBuilder);
    static void _buildGame(FSMBuilder &fsmBuilder, Game &game);
    static void _setStartingState(FSM &fsm);
};
