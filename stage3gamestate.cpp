#include "stage3gamestate.h"

Stage3GameState::Stage3GameState(Stage3Game *context) {
    unsigned int world_height = Config::config()->getWorldHeight();
    unsigned int world_width = Config::config()->getWorldWidth();

    Background *background = new Background(Coordinate(0, world_height, world_height, world_width));
    StickmanPlayer* player = new StickmanPlayer(new Coordinate(Config::config()->getStickman()->getXPosition() - (Config::config()->getStickman()->getWidth()*0.5),
                                                               0 + Config::config()->getStickman()->getHeight(),
                                                               world_height,
                                                               world_width),
                                                "stickman");
    Coordinate *pos = new Coordinate(0, 0, world_height, world_width);
    Stage3Config config(*Config::config());

    //setup level_data
    // get all obstacle datas
    std::vector<std::vector<ObstacleConfig *> *> all_level_obstacle_data = config.getAllLevelObstacleData();
    // get all powerup datas
    std::vector<std::vector<PowerupConfig *> *> all_level_powerup_data = config.getAllLevelPowerupData();
    // get all coin datas
    std::vector<std::vector<CoinConfig *> *> all_level_coin_data = config.getAllLevelCoinData();


    std::vector<std::vector<ObstacleConfig *> *>::iterator obstacle_it;
    std::vector<std::vector<PowerupConfig *> *>::iterator powerup_it;
    std::vector<std::vector<CoinConfig *> *>::iterator coin_it;

    int num_levels = 0;

    for (obstacle_it = all_level_obstacle_data.begin(), powerup_it = all_level_powerup_data.begin(), coin_it = all_level_coin_data.begin();
         obstacle_it != all_level_obstacle_data.end() && powerup_it != all_level_powerup_data.end(), coin_it != all_level_coin_data.end();
         obstacle_it++, powerup_it++, coin_it++) {
       //std::cout << "gamestatefactory things 4" << std::endl;

        std::vector<ObstacleConfig *> *obstacle_configuation = *obstacle_it;
        std::vector<PowerupConfig *> *powerup_configuration = *powerup_it;
        std::vector<CoinConfig *> *coin_configuration = *coin_it;

       //std::cout << "gamestatefactory things 5" << std::endl;

        // Create a new root
        EmptyEntity *root = new EmptyEntity(pos, "root");

       //std::cout << "gamestatefactory things 6" << std::endl;

        // Create obstacles
        double previous_x = world_width;
        int count = 0;
        // For every obstacle in the level
        for (ObstacleConfig *o_config : *obstacle_configuation) {
            previous_x += o_config->offset_x;
            std::stringstream name;
            name << "obstacle_" << count;
            Coordinate *obs_pos = new Coordinate(previous_x, o_config->position_y, world_height, world_width);
            Obstacle *obs = new Obstacle(obs_pos, o_config->width, o_config->height,
                                         -Config::config()->getStickman()->getVelocity(), -1,
                                         QColor(o_config->colour_red, o_config->colour_green, o_config->colour_blue), name.str());
            root->addChild(obs);
            count++;
        }

        // Create the checkpoint
        Coordinate *checkpoint_pos = new Coordinate(previous_x + 200, 50, world_height, world_width);
        Checkpoint *chk = new Checkpoint(checkpoint_pos, -Config::config()->getStickman()->getVelocity(), "checkpoint");
        root->addChild(chk);

       //std::cout << "gamestatefactory things 7" << std::endl;

        // Create Powerups
        previous_x = world_width;
        count = 0;
        // for every powerup in the level
        for (PowerupConfig *power_config : *powerup_configuration) {
            previous_x += power_config->offset_x;
            std::stringstream name;
            name << "powerup_" << count;
            Coordinate *pow_pos = new Coordinate(previous_x, power_config->position_y, world_height, world_width);
            Powerup *pow = new Powerup(pow_pos, -Config::config()->getStickman()->getVelocity(), name.str());
            root->addChild(pow);
            count++;
        }
       //std::cout << "gamestatefactory things 8" << std::endl;

        // Create coins
        previous_x = world_width;
        count = 0;
        // for every coin in the level
        for (CoinConfig *coin_config : *coin_configuration) {
            previous_x += coin_config->offset_x;
            std::stringstream name;
            name << "coin_" << count;
           Coordinate *coin_pos = new Coordinate(previous_x, coin_config->position_y, world_height, world_width);
           Coin *coin = new Coin(coin_pos, -Config::config()->getStickman()->getVelocity(), name.str());
           root->addChild(coin);
           count++;
        }

       //std::cout << "gamestatefactory things 9" << std::endl;

        level_data.push_back(root);
       //std::cout << "gamestatefactory things 10" << std::endl;

        num_levels += 1;
    }

    setLevel(1);
    setPlayerMoving(false);
    setBackground(background);
    setPlayer(player);
    setNumLevels(num_levels);

    Config::config()->getStickman()->changeVelocity(0);
    Config::config()->getStickman()->updateStickman();

    state_num = 0;

    current_context = context;
}

Stage3GameState::Stage3GameState() {
    unsigned int world_height = Config::config()->getWorldHeight();
    unsigned int world_width = Config::config()->getWorldWidth();

    Background *background = new Background(Coordinate(0, world_height, world_height, world_width));
    StickmanPlayer* player = new StickmanPlayer(new Coordinate(Config::config()->getStickman()->getXPosition() - (Config::config()->getStickman()->getWidth()*0.5),
                                                               0 + Config::config()->getStickman()->getHeight(),
                                                               world_height,
                                                               world_width),
                                                "stickman");
    Coordinate *pos = new Coordinate(0, 0, world_height, world_width);
    Stage3Config config(*Config::config());

    //setup level_data
    // get all obstacle datas
    std::vector<std::vector<ObstacleConfig *> *> all_level_obstacle_data = config.getAllLevelObstacleData();
    // get all powerup datas
    std::vector<std::vector<PowerupConfig *> *> all_level_powerup_data = config.getAllLevelPowerupData();
    // get all coin datas
    std::vector<std::vector<CoinConfig *> *> all_level_coin_data = config.getAllLevelCoinData();


    std::vector<std::vector<ObstacleConfig *> *>::iterator obstacle_it;
    std::vector<std::vector<PowerupConfig *> *>::iterator powerup_it;
    std::vector<std::vector<CoinConfig *> *>::iterator coin_it;

    int num_levels = 0;

    for (obstacle_it = all_level_obstacle_data.begin(), powerup_it = all_level_powerup_data.begin(), coin_it = all_level_coin_data.begin();
         obstacle_it != all_level_obstacle_data.end() && powerup_it != all_level_powerup_data.end(), coin_it != all_level_coin_data.end();
         obstacle_it++, powerup_it++, coin_it++) {
       //std::cout << "gamestatefactory things 4" << std::endl;

        std::vector<ObstacleConfig *> *obstacle_configuation = *obstacle_it;
        std::vector<PowerupConfig *> *powerup_configuration = *powerup_it;
        std::vector<CoinConfig *> *coin_configuration = *coin_it;

       //std::cout << "gamestatefactory things 5" << std::endl;

        // Create a new root
        EmptyEntity *root = new EmptyEntity(pos, "root");

       //std::cout << "gamestatefactory things 6" << std::endl;

        // Create obstacles
        double previous_x = world_width;
        int count = 0;
        // For every obstacle in the level
        for (ObstacleConfig *o_config : *obstacle_configuation) {
            previous_x += o_config->offset_x;
            std::stringstream name;
            name << "obstacle_" << count;
            Coordinate *obs_pos = new Coordinate(previous_x, o_config->position_y, world_height, world_width);
            Obstacle *obs = new Obstacle(obs_pos, o_config->width, o_config->height,
                                         -Config::config()->getStickman()->getVelocity(), -1,
                                         QColor(o_config->colour_red, o_config->colour_green, o_config->colour_blue), name.str());
            root->addChild(obs);
            count++;
        }

        // Create the checkpoint
        Coordinate *checkpoint_pos = new Coordinate(previous_x + 200, 50, world_height, world_width);
        Checkpoint *chk = new Checkpoint(checkpoint_pos, -Config::config()->getStickman()->getVelocity(), "checkpoint");
        root->addChild(chk);

       //std::cout << "gamestatefactory things 7" << std::endl;

        // Create Powerups
        previous_x = world_width;
        count = 0;
        // for every powerup in the level
        for (PowerupConfig *power_config : *powerup_configuration) {
            previous_x += power_config->offset_x;
            std::stringstream name;
            name << "powerup_" << count;
            Coordinate *pow_pos = new Coordinate(previous_x, power_config->position_y, world_height, world_width);
            Powerup *pow = new Powerup(pow_pos, -Config::config()->getStickman()->getVelocity(), name.str());
            root->addChild(pow);
            count++;
        }
       //std::cout << "gamestatefactory things 8" << std::endl;

        // Create coins
        previous_x = world_width;
        count = 0;
        // for every coin in the level
        for (CoinConfig *coin_config : *coin_configuration) {
            previous_x += coin_config->offset_x;
            std::stringstream name;
            name << "coin_" << count;
           Coordinate *coin_pos = new Coordinate(previous_x, coin_config->position_y, world_height, world_width);
           Coin *coin = new Coin(coin_pos, -Config::config()->getStickman()->getVelocity(), name.str());
           root->addChild(coin);
           count++;
        }

       //std::cout << "gamestatefactory things 9" << std::endl;

        level_data.push_back(root);
       //std::cout << "gamestatefactory things 10" << std::endl;

        num_levels += 1;
    }

    setLevel(1);
    setPlayerMoving(false);
    setBackground(background);
    setPlayer(player);
    setNumLevels(num_levels);

    Config::config()->getStickman()->changeVelocity(0);
    Config::config()->getStickman()->updateStickman();

    state_num = 0;
    level_points = 0;
}

void Stage3GameState::setContext(Stage3Game *context) {
    current_context = context;
}

std::vector<Entity *> Stage3GameState::getLevelData() {
    return level_data;
}

Entity *Stage3GameState::getLevelRoot(int level) {
   //std::cout << "s3gs entitiesbynamecontains " << std::endl;
    return level_data.at(level - 1);
}

Entity *Stage3GameState::findLevelEntityByName(const std::string &name, Entity *root) {
    return findEntityByNameRecursive(name, root);
}

std::vector<Entity *> Stage3GameState::findEntitiesByNameContains(const std::string &string) {
   //std::cout << "s3gs entitiesbynamecontains 1" << std::endl;
    std::vector<Entity*>list;
    findEntitiesByNameContainsRecursive(string, getLevelRoot(current_level),list);
   //std::cout << "s3gs entitiesbynamecontains 2" << std::endl;
    return list;
}

void Stage3GameState::update(bool paused) {
   //std::cout << "s3gs update " << std::endl;
    checkObstacleCollision();
   //std::cout << "s3gs update 2" << std::endl;
    checkPowerupCollision();
    checkCheckpointCollision();
    checkCoinCollision();
    if (checkpoint_collide && on_last_level) {
       //std::cout << "GAME END GAME END" << std::endl;
        handle();
    }

   //std::cout << "s3gs update 3" << std::endl;

    double deltaTimeMilliseconds = 32; // Comes from hard coded timer interval value in Stage1Game.
    getLevelRoot(current_level)->update(paused || player_colliding, deltaTimeMilliseconds);
    if (getPlayer() != nullptr) {
        getPlayer()->update(paused /*|| !playerMoving()*/, deltaTimeMilliseconds);
    }
   //std::cout << "s3gs update 4" << std::endl;
}

Entity *Stage3GameState::getRootEntity() {
    return getLevelRoot(current_level);
}

void Stage3GameState::handle() {
    current_context->setState(new Stage3EndState(current_context));
   //std::cout << "handlerhandler" << std::endl;
}

void Stage3GameState::nextLevel()
{
    if (current_level == num_levels) {
        on_last_level = true;
        return;
    } else {
        current_level += 1;
    }
}

Entity *Stage3GameState::findEntityByNameRecursive(const std::string &name, Entity *root) {
    if (root->getName() == name) {
        return root;
    }
    Entity* found = nullptr;
    for (auto* child : getLevelRoot(current_level)->getChildren()) {
        found = findEntityByNameRecursive(name, child);
        if (found != nullptr) {
            return found;
        }
    }
    return nullptr;
}

void Stage3GameState::findEntitiesByNameContainsRecursive(const std::string &string, Entity *root, std::vector<Entity *> &list) {
    if (root->getName().find(string) != std::string::npos) {
        list.push_back(root);
    }

    for (auto* child : root->getChildren()) {
        findEntitiesByNameContainsRecursive(string, child, list);
    }
}

void Stage3GameState::checkObstacleCollision() {
   //std::cout << "s3gs obscol 1" << std::endl;
    bool player_collided = false;

    // Takes every entity in current level
    for(auto *entity : findEntitiesByNameContains("obstacle")) {
       //std::cout << "s3gs obscol 2" << std::endl;
        RectCollider* p_col = getPlayer()->getCollider();
        RectCollider* o_col = entity->getCollider();
       //std::cout << "s3gs obscol 3" << std::endl;
        if (p_col != nullptr && o_col != nullptr) {
            if (p_col->checkCollision(*o_col)) {
                getPlayer()->onCollision(entity);
                entity->onCollision(getPlayer());
                player_collided = true;
            }
        }
    }
    player_colliding = player_collided;
}

void Stage3GameState::checkCheckpointCollision() {
    bool checkpoint_collided = false;

    for (auto *entity : findEntitiesByNameContains("checkpoint")) {
        RectCollider *p_col = getPlayer()->getCollider();
        RectCollider *chk_col = entity->getCollider();
        if (p_col != nullptr && chk_col != nullptr) {
            if (p_col->checkCollision(*chk_col)) {
                getPlayer()->onCollision(entity);
                entity->onCollision(getPlayer());
                nextLevel();
                checkpoint_collided = true;
            }
        }
    }
    checkpoint_collide = checkpoint_collided;
}

void Stage3GameState::checkCoinCollision() {
    bool c_collected = false;

    for (auto *entity : findEntitiesByNameContains("coin")) {
        RectCollider *p_col = getPlayer()->getCollider();
        RectCollider *c_col = entity->getCollider();
        if (p_col != nullptr && c_col != nullptr) {
            if (p_col->checkCollision(*c_col)) {
                getPlayer()->onCollision(entity);
                entity->onCollision(getPlayer());
                Coin *collected_coin = static_cast<Coin *>(entity);

                if (!collected_coin->isCollected()) {
                    collected_coin->set_isCollected(true);
                    c_collected = true;
                }
            }
        }
    }
    coin_collected = c_collected;
}

void Stage3GameState::checkPowerupCollision() {
    bool power_collected = false;

    for (auto *entity : findEntitiesByNameContains("powerup")) {
        RectCollider *p_col = getPlayer()->getCollider();
        RectCollider *pow_col = entity->getCollider();
        if (p_col != nullptr && pow_col != nullptr) {
            if (p_col->checkCollision(*pow_col)) {
                getPlayer()->onCollision(entity);
                entity->onCollision(getPlayer());
                Powerup *collected_powerup = static_cast<Powerup*>(entity);
                // get current size
                std::string size = Config::config()->getStickman()->getSize();
               //std::cout << size << std::endl;
                Stickman *stickman = Config::config()->getStickman();
                if (size == "tiny" && !collected_powerup->isCollected()) {
                    stickman->changeSize("normal");
                    stickman->updateStickman();
                } else if (size == "normal" && !collected_powerup->isCollected()) {
                    stickman->changeSize("large");
                    stickman->updateStickman();
                } else if (size == "large" && !collected_powerup->isCollected()) {
                    stickman->changeSize("giant");
                    stickman->updateStickman();
                } else if (size == "giant" && !collected_powerup->isCollected()) {
                    // dont change size, increase life count?x
                }

                collected_powerup->set_isCollected(true);
                power_collected = true;
            }
        }
    }
    powerup_collected = power_collected;
}
