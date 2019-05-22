#include "stage3game.h"

Stage3Game::Stage3Game(GameState *state) :
    Stage2Game(state) {}

Stage3Game::~Stage3Game() {
    delete state;
}

void Stage3Game::render(QPainter &painter) {
    // Do what stage 2 does for render
    Stage2Game::render(painter);
}

void Stage3Game::keyPressEvent(QKeyEvent *event) {
    // Do what stage 2 does for keyPress
    Stage2Game:: keyPressEvent(event);
}

void Stage3Game::paintEvent(QPaintEvent *event) {
    state->update(paused);

    QPainter painter(this);
    render(painter);
}
