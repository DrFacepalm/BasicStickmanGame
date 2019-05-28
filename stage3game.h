#pragma once

#include "entity.h"
#include "player.h"
#include "stage2game.h"
#include "gamestate.h"

class GameState;

class Stage3Game : public Stage2Game {
public:
    Stage3Game(GameState *state);
    ~Stage3Game() override;

    void render(QPainter &painter);

    void setState(GameState *state);

    void handle();

protected:

    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    int default_move_speed;
    GameState *current_state;
};
