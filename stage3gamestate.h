#pragma once

#include "gamestate.h"
#include "emptyentity.h"
#include "entity.h"
#include <vector>
#include "background.h"
#include "player.h"
#include <sstream>
#include "stickmanplayer.h"
#include "rectcollider.h"
#include "stage3config.h"
#include "checkpoint.h"
#include "obstacle.h"
#include "stage3game.h"
#include "stage3endstate.h"
#include "stage3abstractstate.h"
#include "coin.h"
#include "pointdisplay.h"
#include "lifedisplay.h"

class Stage3GameState : public Stage3AbstractState {
public:

    Stage3GameState();
    void setContext(Stage3Game *context) override;

    std::vector<Entity *> getLevelData();
    Entity *getLevelRoot(int level);

    Entity *findLevelEntityByName(const std::string &name, Entity *root);
    //std::vector<Entity *> findLevelEntitiesByNameContains(const std::string *string, Entity *root);

    std::vector<Entity *> findEntitiesByNameContains(const std::string &string) override;
    void update(bool paused) override;

    std::vector<Entity *> level_data;
    virtual Entity *getRootEntity();

    virtual void handle();

    void setLevel(int level) { current_level = level; }
    int getLevel() { return current_level; }
    void nextLevel();

    void setNumLevels(int num) { num_levels = num; }
    int getNumLevels() {return num_levels; }

    bool isLastLevel() { return on_last_level; }

    int getPoints() { return points; }

    void setPointDisplay(PointDisplay *pd) override;//{ pointDisplay = pd; }
    PointDisplay *getPointDisplay() override;//{ return pointDisplay; }

    void resetLevel();

protected:
    virtual Entity *findEntityByNameRecursive(const std::string &name, Entity *root);
    virtual void findEntitiesByNameContainsRecursive(const std::string &string, Entity *root, std::vector<Entity *>& list);

    void checkObstacleCollision();
    void checkPowerupCollision();
    void checkCheckpointCollision();
    void checkCoinCollision();

    void lowerLife();

private:

    int num_levels;
    bool on_last_level;
    bool checkpoint_collide;
    bool coin_collected;
    int current_level;

    int points;
    bool alive;

};

