#include "pointdisplay.h"

PointDisplay::PointDisplay()
    : display_pos(new Coordinate(800, 500, Config::config()->getWorldHeight(), Config::config()->getWorldWidth())),
      current_points(0)
{}

PointDisplay::~PointDisplay() {
    delete display_pos;
}

void PointDisplay::render(QPainter &painter, bool endgame) {
    QPen pen;
    pen.setColor(Qt::red);
    painter.setPen(pen);

    if (endgame) {
        painter.drawText(450,
                         280,
                         QString::number(current_points) );
    } else {
        painter.drawText(display_pos->getQtRenderingXCoordinate(),
                         display_pos->getQtRenderingYCoordinate(),
                         QString::number(current_points) );
    }

}

void PointDisplay::setPoints(int points) {
    current_points = points;
}

