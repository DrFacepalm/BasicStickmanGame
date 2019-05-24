#include "stage3gamestate.h"

Stage3GameState::Stage3GameState()
{

}

std::vector<Entity *> Stage3GameState::getLevelData() {
    return level_data;
}

Entity *Stage3GameState::getLevelRoot(int level) {
    std::cout << "s3gs entitiesbynamecontains " << std::endl;
    return level_data.at(level - 1);
}

Entity *Stage3GameState::findLevelEntityByName(const std::string &name, Entity *root) {
    return findEntityByNameRecursive(name, root);
}

std::vector<Entity *> Stage3GameState::findEntitiesByNameContains(const std::string &string) {
    std::cout << "s3gs entitiesbynamecontains 1" << std::endl;
    std::vector<Entity*>list;
    findEntitiesByNameContainsRecursive(string, getLevelRoot(current_level),list);
    std::cout << "s3gs entitiesbynamecontains 2" << std::endl;
    return list;
}

void Stage3GameState::update(bool paused) {
    std::cout << "s3gs update " << std::endl;
    checkObstacleCollision();
    std::cout << "s3gs update 2" << std::endl;
    checkPowerupCollision();
    std::cout << "s3gs update 3" << std::endl;
    double deltaTimeMilliseconds = 32; // Comes from hard coded timer interval value in Stage1Game.
    getLevelRoot(current_level)->update(paused || player_colliding, deltaTimeMilliseconds);
    if (getPlayer() != nullptr) {
        getPlayer()->update(paused /*|| !playerMoving()*/, deltaTimeMilliseconds);
    }
    std::cout << "s3gs update 4" << std::endl;
}

Entity *Stage3GameState::getRootEntity() {
    return getLevelRoot(current_level);
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
    std::cout << "s3gs obscol 1" << std::endl;
    bool player_collided = false;

    // Takes every entity in current level
    for(auto *entity : findEntitiesByNameContains("obstacle")) {
        std::cout << "s3gs obscol 2" << std::endl;
        RectCollider* p_col = getPlayer()->getCollider();
        RectCollider* o_col = entity->getCollider();
        std::cout << "s3gs obscol 3" << std::endl;
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
                std::cout << size << std::endl;
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
