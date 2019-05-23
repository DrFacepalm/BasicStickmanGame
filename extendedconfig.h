#pragma once

#include <vector>

#include "config.h"
#include "configuration.h"

class ExtendedConfig : public Configuration {
public:
    ExtendedConfig(Config& config);
    ~ExtendedConfig() override;

    virtual unsigned int getWorldWidth() override;
    virtual unsigned int getWorldHeight() override;
    virtual std::vector<ObstacleConfig*> getObstacleData() override;

    //////// STAGE3TESTING ///////////////
    virtual std::vector<PowerupConfig *> getPowerupData();

protected:
    virtual void setupConfig() override;

private:
    Config& config;
    std::vector<ObstacleConfig*> obstacle_data;
    std::vector<PowerupConfig*> powerup_data;
};

