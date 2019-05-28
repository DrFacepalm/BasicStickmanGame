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

#include <vector>

class Stage3EndState : public GameState {
public:
    Stage3EndState(Stage3Game* context);
    virtual void handle();

private:
    int state_num;
    Stage3Game *current_context;

};
