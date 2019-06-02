#pragma once

#include <vector>
#include <sstream>

#include "gamestate.h"
#include "emptyentity.h"
#include "entity.h"
#include "background.h"
#include "player.h"
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

    // Constructor for the GameState. Sets up all obstacles, powerups and other entities
    Stage3GameState();

    // Sets the current context of the state (i.e. the Stage3Game)
    void setContext(Stage3Game *context) override;

    //std::vector<Entity *> getLevelData();
    Entity *getLevelRoot(int level);

    // Returns a list of entities that contain
    std::vector<Entity *> findEntitiesByNameContains(const std::string &string) override;

    // Updates the game state
    void update(bool paused) override;

    // All the entities in the level
    std::vector<Entity *> level_data;

    // Gets the root entity of the current_level
    virtual Entity *getRootEntity();

    // Handle's the state, notably when the game is over, changes the current_context's
    // state to Stage3EndState
    virtual void handle();

    // Sets the current level to 'level'
    void setLevel(int level) { current_level = level; }

    // Gets the current level
    int getLevel() { return current_level; }

    // Increments the level, if increments to the last level, sets 'is_last_level' to
    // true
    void nextLevel();

    // Sets the number of levels
    void setNumLevels(int num) { num_levels = num; }

    // Gets the number of levels
    int getNumLevels() {return num_levels; }

    // Returns true if currently on last level
    bool isLastLevel() { return on_last_level; }

    // Returns the current points
    int getPoints() { return points; }

    // Sets the point display, overridden from Stage3AbstractState
    void setPointDisplay(PointDisplay *pd) override;

    // Gets the point display, overridden from Stage3AbstractState
    PointDisplay *getPointDisplay() override;

    // Resets obstacle and uncollected powerup and coin positions back to the original
    // positions
    void resetLevel();

    int getLives();

protected:
    virtual Entity *findEntityByNameRecursive(const std::string &name, Entity *root);
    virtual void findEntitiesByNameContainsRecursive(const std::string &string, Entity *root, std::vector<Entity *>& list);

    // Checks collision of all the collidables
    void checkObstacleCollision();
    void checkPowerupCollision();
    void checkCheckpointCollision();
    void checkCoinCollision();

    // Removes an obstacle if collided with, and stickman is giant
    void expodingObstacleHelper();

    // Lowers the current life count
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

