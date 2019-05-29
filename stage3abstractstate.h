#pragma once

#include "gamestate.h"

class Stage3AbstractState : public GameState
{
public:
    virtual void handle() = 0;
};

