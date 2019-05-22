#include "stage3gamestate.h"

Stage3GameState::Stage3GameState()
{

}

std::vector<Entity *> Stage3GameState::getLevelData() {
    return level_data;
}

Entity *Stage3GameState::getLevelRoot(int level) {
    return level_data.at(level - 1);
}

Entity *Stage3GameState::findLevelEntityByName(const std::string &name, Entity *root) {
    return findEntityByNameRecursive(name, root);
}
