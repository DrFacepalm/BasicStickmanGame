#pragma once

// Responsible for storing the game state of the current game, independently of rendering.

#include <string>
#include <vector>
#include "config.h"
#include "entity.h"
#include "stickman.h"

//// STAGE 3 ///////
#include "powerup.h"

class Background;
class Entity;
class Player;

class GameState {

public:
    GameState();
    virtual ~GameState();

    virtual Entity* getRootEntity();
    void setRootEntity(Entity* root);

    Entity* findEntityByName(const std::string& name);
    virtual std::vector<Entity*> findEntitiesByNameContains(const std::string& string);

    Background* getBackground();
    void setBackground(Background* bg);

    Player* getPlayer();
    void setPlayer(Player* player);

    virtual void update(bool paused);
    bool getPlayerColliding() {return player_colliding; }

    virtual void handle();

    ///// STAGE3TESTING /////

    int state_num;

    virtual void checkPowerupCollision1();
    void setPlayerMoving(bool moving) { player_moving = moving; }
    bool playerMoving() { return player_moving; }
    /////////////////////////
protected:
    virtual void checkCollisions();
    virtual Entity* findEntityByNameRecursive(const std::string& name, Entity* root);
    virtual void findEntitiesByNameContainsRecursive(const std::string& string, Entity* root, std::vector<Entity*>& list);
    bool player_colliding;
    bool powerup_collected;

private:
    Player* player;
    Background* background;
    Entity* root_entity;
    bool player_moving;
};

