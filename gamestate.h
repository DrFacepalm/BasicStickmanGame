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

    Entity* getRootEntity();
    void setRootEntity(Entity* root);

    Entity* findEntityByName(const std::string& name);
    std::vector<Entity*> findEntitiesByNameContains(const std::string& string);

    Background* getBackground();
    void setBackground(Background* bg);

    Player* getPlayer();
    void setPlayer(Player* player);

    void update(bool paused);
    bool getPlayerColliding() {return player_colliding; }

    ///// STAGE3TESTING /////
    void checkPowerupCollision();
    /////////////////////////
protected:
    void checkCollisions();
    Entity* findEntityByNameRecursive(const std::string& name, Entity* root);
    void findEntitiesByNameContainsRecursive(const std::string& string, Entity* root, std::vector<Entity*>& list);

private:
    Player* player;
    Background* background;
    Entity* root_entity;
    bool player_colliding;
    bool powerup_collected;
};
