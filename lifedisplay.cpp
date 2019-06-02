#include "lifedisplay.h"

LifeDisplay::LifeDisplay(Coordinate *position, int lives)
    : CompositeEntity(position, "life_display"),
      lives(lives)
{}

void LifeDisplay::update(bool paused, double time_since_last_frame) {
    return;
}

void LifeDisplay::render(QPainter &painter) {
    QPen pen;
    pen.setColor(Qt::red);
    painter.setPen(pen);

    std::stringstream output;
    output << "Lives: " << lives;
    painter.drawText(800, 115, QString::fromStdString(output.str()));

}

void LifeDisplay::setLives(int val) {
    lives = val;
}

int LifeDisplay::getLives() {
    return lives;
}

void LifeDisplay::lowerLife() {
    lives--;
}



