#include "stage3gamefactory.h"
#include <iostream>

GameDialog* Stage3GameFactory::createGame() {

    Stage3GameStateFactory *factory = new Stage3GameStateFactory();
    std::cout << "im what awhoieafj" << std::endl;
    GameState *state = factory->createGameState();
    std::cout << "im hereee" << std::endl;
    return new Stage3Game(state);
}
