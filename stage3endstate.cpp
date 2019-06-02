#include "stage3endstate.h"

Stage3EndState::Stage3EndState(Stage3Game *context, bool win) {
    unsigned int world_height = Config::config()->getWorldHeight();
    unsigned int world_width = Config::config()->getWorldWidth();
    Background *background;
    if (win) {
        background = new Background(Coordinate(0, world_height, world_height, world_width), 1);
    } else {
        background = new Background(Coordinate(0, world_height, world_height, world_width), 2);
    }

    StickmanPlayer *player = nullptr;

    setPlayer(player);
    setBackground(background);

    current_context = context;
    state_num = 1;
}

Entity *Stage3EndState::getRootEntity() {
    return nullptr;
}

void Stage3EndState::handle() {
    return;
}

void Stage3EndState::setContext(Stage3Game *context) {
    current_context = context;
}


void Stage3EndState::update(bool paused) {
    // Does not need to do anything
    return;
}

void Stage3EndState::setPointDisplay(PointDisplay *pd) {
    // Does not need to display anything
    return;
}

PointDisplay *Stage3EndState::getPointDisplay() {
    // Does not need to display anything
    return nullptr;
}


