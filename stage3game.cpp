#include "stage3game.h"
#include <QWidget>

Stage3Game::Stage3Game(GameState *state) :
    Stage2Game(state),
    default_move_speed(10)
{
    std::cout << "stage3 construct" << std::endl;
}

Stage3Game::~Stage3Game() {
    delete state;
}

void Stage3Game::render(QPainter &painter) {
    std::cout << "stage3 render" << std::endl;
    // Do what stage 2 does for render
    if (state->getBackground() != nullptr) {
        state->getBackground()->render(painter, paused || state->getPlayerColliding());
    }

    if (state->getPlayer() != nullptr) {
        state->getPlayer()->render(painter);
    }

    // Render all entities stored in the game state
    state->getRootEntity()->render(painter);
}

void Stage3Game::keyPressEvent(QKeyEvent *event) {
    // Do what stage 2 does for keyPress
    Stage2Game:: keyPressEvent(event);

    // Do whatever else you need to do
    if (event->type()==QEvent::KeyPress) {
        if (event->key() == Qt::Key_Right) {
            // Stickman Moves right, i.e. set stickman's velocity to 10 to the right

            Config::config()->getStickman()->changeVelocity(default_move_speed);
            Config::config()->getStickman()->updateStickman();
        } else if (event->key() == Qt::Key_Left) {
            Config::config()->getStickman()->changeVelocity(-default_move_speed);
            Config::config()->getStickman()->updateStickman();
        }
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
    std::cout << "s3 paint event" << std::endl;
    state->update(paused);
    std::cout << "s3 paint event" << std::endl;
    QPainter painter(this);
    render(painter);
}
