#include "coin.h"

Coin::Coin(Coordinate *position, double velocity, std::string name)
    : CompositeEntity(position, name),
      collider(RectCollider(new Coordinate(position->getXCoordinate() - width/2.0, position->getYCoordinate() - height/2.0, position->getFrameHeight(), position->getFrameWidth()),
                            new Coordinate(position->getXCoordinate() + width/2.0, position->getYCoordinate() + height/2.0, position->getFrameHeight(), position->getFrameWidth()))),
      velocity(velocity),
      dist_travelled(0),
      is_moving(true),
      is_collected(false)
{
    this->width = 35;
    this->height = 35;
    image.load(":img/coins/coin.png");
}

void Coin::update(bool paused, double time_since_last_frame) {
    // update velocity each time
    velocity = -Config::config()->getStickman()->getVelocity();

    if (!paused) {
        is_moving = true;

        // Keep collider in sync with position
        this->getPosition()->changeInXCoordinate(velocity);
        collider.getV1()->setXCoordinateToZero(getPosition()->getXCoordinate() - width/2.0);
        collider.getV1()->setYCoordinateToZero(getPosition()->getYCoordinate() - height/2.0);
        collider.getV2()->setXCoordinateToZero(getPosition()->getXCoordinate() + width/2.0);
        collider.getV2()->setYCoordinateToZero(getPosition()->getYCoordinate() + height/2.0);

        updateChildren(paused, time_since_last_frame);
        dist_travelled -= velocity;
    } else {
        is_moving = false;
    }
}


void Coin::render(QPainter &painter) {
   //std::cout << "RENDINIGN I COIN OJFOAEWJFAOFJ" << std::endl;
    if (getPosition() != nullptr && !is_collected) {
        double x = this->getPosition()->getQtRenderingXCoordinate();
        double y = this->getPosition()->getQtRenderingYCoordinate();
        painter.drawPixmap(x - width/2.0, y - height/2.0, width, height, image);
    }

    renderChildren(painter);
}
