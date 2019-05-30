#pragma once

#include "gamestate.h"
#include "stage3game.h"

class Stage3AbstractState : public GameState
{
public:
    virtual void handle() = 0;
    virtual void setContext(Stage3Game *context) = 0;
protected:
    Stage3Game *current_context;
};

