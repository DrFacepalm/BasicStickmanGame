#include "stage3endstate.h"

Stage3EndState::Stage3EndState(Stage3Game *context) {

    unsigned int world_height = Config::config()->getWorldHeight();
    unsigned int world_width = Config::config()->getWorldWidth();

    Background *background = new Background(Coordinate(0, world_height, world_height, world_width), true);
    StickmanPlayer *player = nullptr;

    setPlayer(player);
    setBackground(background);

    current_context = context;
}

void Stage3EndState::handle() {
    return;
}
