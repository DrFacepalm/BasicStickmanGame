#pragma once

#include <QList>
#include <QPixmap>
#include <QPainter>
#include <QDialog>
#include <string>
#include <config.h>

#include "coordinate.h"


class PointDisplay {
public:
    PointDisplay();
    virtual ~PointDisplay();

    void render(QPainter &painter, bool endgame);
    void setPoints(int points);
private:
    Coordinate *display_pos;
    int current_points;
};
