#include "stage3gamestatefactory.h"


GameState* Stage3GameStateFactory::createGameState() {
    Stage3GameState *state = new Stage3GameState();

    unsigned int world_height = Config::config()->getWorldHeight();
    unsigned int world_width = Config::config()->getWorldWidth();

    // Create background and player
    Background *background = new Background(Coordinate(0, world_height, world_height, world_width));
    StickmanPlayer* player = new StickmanPlayer(new Coordinate(Config::config()->getStickman()->getXPosition() - (Config::config()->getStickman()->getWidth()*0.5),
                                                               0 + Config::config()->getStickman()->getHeight(),
                                                               world_height,
                                                               world_width),
                                                "stickman");
    Coordinate *pos = new Coordinate(0, 0, world_height, world_width);

    Stage3Config config(*Config::config());
    // Load obstacle data from file

    std::cout << "gamestatefactory things" << std::endl;
    //setup level_data
    // get all obstacle datas
    std::vector<std::vector<ObstacleConfig *> *> all_level_obstacle_data = config.getAllLevelObstacleData();
    // get all powerup datas
    std::vector<std::vector<PowerupConfig *> *> all_level_powerup_data = config.getAllLevelPowerupData();

    std::cout << "gamestatefactory things 2" << std::endl;

    // For each thing in all_level_data, create obstacle and add it to the root (after
    // a root is created)
    std::vector<std::vector<ObstacleConfig *> *>::iterator obstacle_it;
    std::vector<std::vector<PowerupConfig *> *>::iterator powerup_it;

    std::cout << "gamestatefactory things 3" << std::endl;

    for (obstacle_it = all_level_obstacle_data.begin(), powerup_it = all_level_powerup_data.begin();
         obstacle_it != all_level_obstacle_data.end() && powerup_it != all_level_powerup_data.end();
         obstacle_it++, powerup_it++) {
        std::cout << "gamestatefactory things 4" << std::endl;

        std::vector<ObstacleConfig *> *obstacle_configuation = *obstacle_it;
        std::vector<PowerupConfig *> *powerup_configuration = *powerup_it;

        std::cout << "gamestatefactory things 5" << std::endl;

        // Create a new root
        EmptyEntity *root = new EmptyEntity(pos, "root");

        std::cout << "gamestatefactory things 6" << std::endl;

        // Create obstacles
        double previous_x = world_width;
        int count = 0;
        // For every obstacle in the level
        for (ObstacleConfig *o_config : *obstacle_configuation) {
            previous_x = previous_x + o_config->offset_x;
            std::stringstream name;
            name << "obstacle_" << count;
            Coordinate *obs_pos = new Coordinate(previous_x, o_config->position_y, world_height, world_width);
            Obstacle *obs = new Obstacle(obs_pos, o_config->width, o_config->height,
                                         -Config::config()->getStickman()->getVelocity(), -1,
                                         QColor(o_config->colour_red, o_config->colour_green, o_config->colour_blue), name.str());
            root->addChild(obs);
            count++;
        }

        std::cout << "gamestatefactory things 7" << std::endl;

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
        std::cout << "gamestatefactory things 8" << std::endl;

        //Stage3GameState *s3State = static_cast<Stage3GameState *>(state);

        std::cout << "gamestatefactory things 9" << std::endl;

        state->level_data.push_back(root);
        std::cout << "gamestatefactory things 10" << std::endl;
    }

    state->setLevel(1);
    state->setPlayerMoving(false);
    state->setBackground(background);
    state->setPlayer(player);

    Config::config()->getStickman()->changeVelocity(0);
    Config::config()->getStickman()->updateStickman();

    std::cout << "gamestatefactory things 11 end" << std::endl;
    return state;
}
