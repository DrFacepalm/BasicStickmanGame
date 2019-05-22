#include "stage3gamefactory.h"

GameDialog* Stage3GameFactory::createGame() {
    Stage3GameStateFactory *factory = new Stage2GameStateFactory();
    GameState *state = factory->createGameState();
    return new Stage3Game(state);
}
