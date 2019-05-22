#pragma once

#include "gamestate.h"
#include "emptyentity.h"
#include "entity.h"
#include <vector>

class Stage3GameState : public GameState {
public:
    Stage3GameState();
    std::vector<Entity *> getLevelData();
    Entity *getLevelRoot(int level);

    Entity *findLevelEntityByName(const std::string &name, Entity *root);
    std::vector<Entity *>findLevelEntitiesByNameContains(const std::string *string, Entity *root);

    std::vector<Entity *> level_data;

};

