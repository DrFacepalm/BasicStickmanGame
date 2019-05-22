#pragma once

#include "stage2gamestatefactory.h"
#include "stage2game.h"
#include "obstacle.h"
#include "gamestate.h"
#include "stickmanplayer.h"
#include "extendedconfig.h"
#include "emptyentity.h"
#include "stage3config.h"
#include "stage3gamestate.h"
#include <vector>
#include <sstream>

class Stage3GameStateFactory : public Stage2GameStateFactory
{
public:
    Stage3GameStateFactory() = default;
    ~Stage3GameStateFactory() = default;
    virtual GameState* createGameState() override;
};
