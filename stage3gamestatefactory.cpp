#include "stage3gamestatefactory.h"


GameState* Stage3GameStateFactory::createGameState() {
    GameState *state = new GameState();

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

    //setup level_data
    // get all obstacle datas
    std::vector<std::vector<ObstacleConfig *> *> all_level_data = config.getAllLevelObstacleData();

    // For each thing in all_level_data, create obstacle and add it to the root (after
    // a root is created)
    std::vector<std::vector<ObstacleConfig *> *>::iterator it;
    for (it = all_level_data.begin(); it != all_level_data.end(); it++) {
        std::vector<ObstacleConfig *> *level_configuation = *it;

        // Create a new root
        EmptyEntity *root = new EmptyEntity(pos, "root");

        // Create obstacles
        double previous_x = world_width;
        int count = 0;
        for (ObstacleConfig *o_config : *level_configuation) {
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

        Stage3GameState *s3State = static_cast<Stage3GameState *>(state);
        s3State->level_data.push_back(root);

    }

    state->setBackground(background);
    state->setPlayer(player);
    return state;
}
