#pragma once

#include "gamestate.h"
#include "emptyentity.h"
#include "entity.h"
#include <vector>
#include "background.h"
#include "player.h"
#include "rectcollider.h"

class Stage3GameState : public GameState {
public:
    Stage3GameState();
    std::vector<Entity *> getLevelData();
    Entity *getLevelRoot(int level);

    Entity *findLevelEntityByName(const std::string &name, Entity *root);
    std::vector<Entity *> findLevelEntitiesByNameContains(const std::string *string, Entity *root);

    std::vector<Entity *> findEntitiesByNameContains(const std::string &string) override;
    void update(bool paused) override;

    std::vector<Entity *> level_data;
    virtual Entity *getRootEntity();

    void setLevel(int level) { current_level = level; }
    void nextLevel() { current_level += 1; }
    int getLevel() { return current_level; }

protected:
    virtual Entity *findEntityByNameRecursive(const std::string &name, Entity *root);
    virtual void findEntitiesByNameContainsRecursive(const std::string &string, Entity *root, std::vector<Entity *>& list);

private:
    int current_level;
    void checkObstacleCollision();
    void checkPowerupCollision();
};

