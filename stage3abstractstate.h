#pragma once

#include "gamestate.h"
#include "stage3game.h"
#include "pointdisplay.h"

class Stage3Game;

// Defines an abstract state for the game, for use with Stage3Game
class Stage3AbstractState : public GameState
{
public:
    virtual void handle() = 0;
    virtual void setContext(Stage3Game *context) = 0;

    virtual void setPointDisplay(PointDisplay *pd) = 0;
    virtual PointDisplay *getPointDisplay() = 0;
protected:
    PointDisplay *pointDisplay;
    Stage3Game *current_context;
};

