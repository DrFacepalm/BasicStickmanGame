#include "stage3game.h"

Stage3Game::Stage3Game(GameState *state) :
    Stage2Game(state),
    default_move_speed(10)
{}

Stage3Game::~Stage3Game() {}

void Stage3Game::render(QPainter &painter) {
    if (state->getBackground() != nullptr) {
        state->getBackground()->render(painter, paused || state->getPlayerColliding());
    }

    if (state->getPlayer() != nullptr) {
        state->getPlayer()->render(painter);
    }

    // Render the point Display IF in the gamestate, not the endstate
    if (state->state_num == 0) {
        Stage3GameState *s3state = static_cast<Stage3GameState *>(state);
        s3state->getPointDisplay()->render(painter, false);
    }

    // Render all entities stored in the game state IF not in endstate
    if (state->state_num != 1) {
        state->getRootEntity()->render(painter);
    }
}

void Stage3Game::setState(GameState *s) {
    state = s;
}

void Stage3Game::keyPressEvent(QKeyEvent *event) {
    // Do what stage 1 does for keyPress
    Stage1Game::keyPressEvent(event);

    // Do modified Stage2Jump
    if (event->key() == Qt::Key_Space) {
        if (state->state_num == 0) {
            state->getPlayer()->jump();
        }

    }

    if (event->key() == Qt::Key_Right) {
        // Stickman Moves right, i.e. set stickman's velocity to 10 to the right
        Config::config()->getStickman()->changeVelocity(default_move_speed);
        Config::config()->getStickman()->updateStickman();
    } else if (event->key() == Qt::Key_Left) {
        Config::config()->getStickman()->changeVelocity(-default_move_speed);
        Config::config()->getStickman()->updateStickman();
    }

}

void Stage3Game::keyReleaseEvent(QKeyEvent *event)
{
    QWidget::keyReleaseEvent(event);

    if (event->key() == Qt::Key_Right || event->key() == Qt::Key_Left) {
        Config::config()->getStickman()->changeVelocity(0);
        Config::config()->getStickman()->updateStickman();
    }
}

void Stage3Game::paintEvent(QPaintEvent *event) {
    state->update(paused);
    QPainter painter(this);
    render(painter);
}
