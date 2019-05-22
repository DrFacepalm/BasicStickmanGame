#include "stage3config.h"

Stage3Config::Stage3Config(Config &config) :
    config(config),
    m_levelData(std::vector<std::vector<ObstacleConfig *>*>())
{
    setupConfig();
}

Stage3Config::~Stage3Config() {

}

unsigned int Stage3Config::getWorldWidth() {
    return config.getWorldWidth();
}

unsigned int Stage3Config::getWorldHeight() {
    return config.getWorldHeight();
}

std::vector<ObstacleConfig *> Stage3Config::getObstacleData() {
    return *m_levelData.at(0);
}


void Stage3Config::setupConfig() {
    QFile config_file(":config/config.txt");

    //Open the config file
    if (config_file.open(QIODevice::ReadOnly)) {

        QTextStream buffer(&config_file);

        while (!buffer.atEnd()) {

            QString line = buffer.readLine();

            QStringList split_line = line.split(":", QString::SkipEmptyParts);

            QString element = split_line.at(1);

            if (split_line.first() =="Size" || split_line.first() == "Position" || split_line.first() == "Velocity" || split_line.first() == "Background") {
                // Already handled by original config file, ignore.
                continue;

            } else if (split_line.first() == "Obstacles") {
                std::cerr << "Stage 3 should not have any Obstacles field in the config" << std::endl;
                continue;
            } else if (split_line.first().startsWith("Level")) {
                // make new vector
                std::vector<ObstacleConfig *> *level_obstacles = new std::vector<ObstacleConfig *>();

                // add vector to levelData
                m_levelData.push_back(level_obstacles);

                // Element should have format: 50,50,400,0,255,0,0|50,50,400,0,255,0,0 ...
                QStringList obstacles = element.split("|", QString::SkipEmptyParts);

                // Go through each obstacle
                for (int i = 0; i < obstacles.size(); i++) {

                    // Create new ObstacleConfig
                     ObstacleConfig *obstacle_config = new ObstacleConfig();

                     // Get the list of obstacle_fields
                     QStringList obstacle_fields = obstacles.at(i).split(",", QString::SkipEmptyParts);
                     if (obstacle_fields.size() != 7) {
                         std::cerr << "Invalid obstacle data at index " << i << std::endl;
                         continue;
                     } else {
                         try {
                            double width = obstacle_fields.at(0).toDouble();
                            double height = obstacle_fields.at(1).toDouble();
                            double offset = obstacle_fields.at(2).toDouble();
                            double y_pos = obstacle_fields.at(3).toDouble();
                            int r = obstacle_fields.at(4).toInt();
                            int g = obstacle_fields.at(5).toInt();
                            int b = obstacle_fields.at(6).toInt();

                            if (width <= 0 || height <= 0 || offset < 0 || y_pos < 0 || r < 0 || r > 255 ||g < 0 || g > 255 ||b < 0 || b > 255) {
                                std::cerr << "Invalid obstacle data at index " << i << std::endl;
                            } else {
                                // ensure no overlap
                                bool overlap = false;
                                double x_pos = 0;
                                std::vector<ObstacleConfig*>::iterator it;
                                for (it = level_obstacles->begin(); it != level_obstacles->end(); it++) {
                                    x_pos += (*it)->offset_x;
                                }

                                double cumulative_x_pos = 0;
                                for (it = level_obstacles->begin(); it != level_obstacles->end(); it++) {
                                    cumulative_x_pos += (*it)->offset_x;
                                    double old_min_x = cumulative_x_pos - (*it)->width/2.0;
                                    double old_max_x = cumulative_x_pos + (*it)->width/2.0;
                                    double old_min_y = (*it)->position_y - (*it)->height/2.0;
                                    double old_max_y = (*it)->position_y + (*it)->height/2.0;
                                    double new_min_x = x_pos + offset - width/2.0;
                                    double new_max_x = x_pos + offset + width/2.0;
                                    double new_min_y = y_pos - width/2.0;
                                    double new_max_y = y_pos + width/2.0;
                                    if (!(old_min_x > new_max_x || old_max_x < new_min_x)&&!(old_min_y > new_max_y || old_max_y < new_min_y)) {
                                        std::cerr << "Invalid obstacle data at index " << i << " due to overlap" << std::endl;
                                        overlap = true;
                                        break;
                                    }
                                }
                                if (overlap) {
                                    continue;
                                }

                                // Create the obstacle Config and put it in the level_obstacles
                                obstacle_config->width = width;
                                obstacle_config->height = height;
                                obstacle_config->offset_x = offset;
                                obstacle_config->position_y = y_pos;
                                obstacle_config->colour_red = r;
                                obstacle_config->colour_green = g;
                                obstacle_config->colour_blue = b;

                                level_obstacles->push_back(obstacle_config);
                            }

                         } catch (const std::exception &) {
                             std::cerr << "Invalid obstacle data at index " << i << std::endl;
                             continue;
                         }
                     }
                }
            }


        }

        config_file.close();
    } else {
        std::cerr << "Config file not found" << std::endl;
    }

}

std::vector<std::vector<ObstacleConfig *> *> Stage3Config::getAllLevelObstacleData() {
    return m_levelData;
}

std::vector<ObstacleConfig *> *Stage3Config::getLevelObstacle(int level) {
    return m_levelData.at(level - 1);
}
