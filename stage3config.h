#pragma once

#include <vector>
#include "config.h"
#include "configuration.h"
#include <QString>
#include <QRegularExpression>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <iostream>

class Stage3Config : public Configuration {
public:
    Stage3Config(Config &config);
    ~Stage3Config() override;

    virtual unsigned int getWorldWidth() override;
    virtual unsigned int getWorldHeight() override;

    // Cannot use with this config, need modified version.
    // This will only get the obstacle data of the first level
    virtual std::vector<ObstacleConfig *> getObstacleData() override;

    // Gets a list of all the level data.
    std::vector<std::vector<ObstacleConfig *> *> getAllLevelObstacleData();

    // Gets the obstacle data for a certain level.
    std::vector<ObstacleConfig *> getLevelObstacle(int level);

    // sets current level
    void setCurrentLevel(int level);

protected:
    // Actually read stuff
    virtual void setupConfig() override;

private:
    Config &config;
    std::vector<std::vector<ObstacleConfig *> *> level_obstacle_data;
    std::vector<std::vector<PowerupConfig *> *> level_powerup_data;
    int current_level;
};
