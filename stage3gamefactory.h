#pragma once

#include "stage2gamefactory.h"
#include "stage3game.h"
#include "stage3gamestatefactory.h"

class Stage3GameFactory : public Stage2GameFactory {
public:
    Stage3GameFactory() = default;
    ~Stage3GameFactory() override = default;

    GameDialog* createGame() override;
};

