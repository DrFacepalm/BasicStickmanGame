#pragma once

#include "entity.h"
#include "player.h"
#include "stage2game.h"
#include "gamestate.h"
#include "stage3abstractstate.h"
#include "stage3gamestate.h"

#include <QWidget>

class GameState;

class Stage3Game : public Stage2Game {
public:
    // Create the Stage3Game
    Stage3Game(GameState *state);
    ~Stage3Game() override;

    // Render the state
    void render(QPainter &painter);

    // Set the gamestate
    void setState(GameState *s);

protected:

    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    // Value for moving stickman left or right
    int default_move_speed;
    GameState *current_state;
};
