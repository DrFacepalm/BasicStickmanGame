#include "powerup.h"

Powerup::Powerup(Coordinate *position, double width, double height, double velocity, std::string name)
    : CompositeEntity(position, name),
      image(image),
      collider(RectCollider(new Coordinate(position->getXCoordinate() - width/2.0, position->getYCoordinate() - height/2.0, position->getFrameHeight(), position->getFrameWidth()),
                            new Coordinate(position->getXCoordinate() + width/2.0, position->getYCoordinate() + height/2.0, position->getFrameHeight(), position->getFrameWidth()))),
      velocity(velocity),
      dist_travelled(0),
      is_moving(true)
{
    if (width > 0) {
        this->width = width;
    } else {
        width = 1;
    }

    if (height > 0) {
        this->height = height;
    } else {
        this->height = 1;
    }

    image.load(":img/powerups/star.png");
}

Powerup::Powerup(Coordinate *position, double velocity, std::string name)
    : CompositeEntity(position, name),
      collider(RectCollider(new Coordinate(position->getXCoordinate() - width/2.0, position->getYCoordinate() - height/2.0, position->getFrameHeight(), position->getFrameWidth()),
                            new Coordinate(position->getXCoordinate() + width/2.0, position->getYCoordinate() + height/2.0, position->getFrameHeight(), position->getFrameWidth()))),
      velocity(velocity),
      dist_travelled(0),
      is_moving(true)
{
    this->width = 20;
    this->height = 20;
    image.load(":img/powerups/star.png");

}

void Powerup::update(bool paused, double time_since_last_frame) {
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

void Powerup::render(QPainter &painter) {

    if (getPosition() != nullptr) {
        double x = this->getPosition()->getQtRenderingXCoordinate();
        double y = this->getPosition()->getQtRenderingYCoordinate();
        painter.drawPixmap(x - width/2.0, y - height/2.0, width, height, image)
    }

    renderChildren(painter);
}


