#include "stage3gamefactory.h"
#include <iostream>

GameDialog* Stage3GameFactory::createGame() {

    Stage3AbstractState *state = new Stage3GameState();
    Stage3Game *game = new Stage3Game(state);
    state->setContext(game);

    return game;
}
