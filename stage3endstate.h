#pragma once

#include "gamestate.h"
#include "emptyentity.h"
#include "entity.h"
#include "background.h"
#include "player.h"
#include "rectcollider.h"
#include "stage3game.h"
#include "stickmanplayer.h"
#include "stage3gamestate.h"
#include "stage3abstractstate.h"

#include <vector>

// State that defines what the game should look like when either won or lost
class Stage3EndState : public Stage3AbstractState {
public:
    Stage3EndState(Stage3Game* context, bool win);

    // Does nothing in this state
    virtual void handle();

    // Sets the context of the state, i.e. the Stage3Game
    virtual void setContext(Stage3Game *context);

    // Updates the state
    void update(bool paused) override;

    // Sets point display
    virtual void setPointDisplay(PointDisplay *pd) override;

    // Gets point display
    virtual PointDisplay *getPointDisplay() override;

    Entity *getRootEntity() override;
private:

};
