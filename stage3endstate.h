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

class Stage3EndState : public Stage3AbstractState {
public:
    Stage3EndState(Stage3Game* context);
    virtual void handle();
    virtual void setContext(Stage3Game *context);

    void update(bool paused) override;

    Entity *getRootEntity() override;
private:

};
