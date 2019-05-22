#pragma once

#include <QPainter>
#include <QColor>
#include "compositeentity.h"
#include "rectcollider.h"
#include "coordinate.h"

class Powerup : public CompositeEntity {
public:
    Powerup(Coordinate *position, double width, double height, double velocity, std::string name);
    Powerup(Coordinate *position, double velocity, std::string name);
    ~Powerup() override = default;

    virtual RectCollider *getCollider() override { return &collider; }

    virtual void update(bool paused, double time_since_last_frame) override;
    virtual void render(QPainter &painter) override;

    bool isMoving() { return is_moving; }

private:
    QPixmap image;
    RectCollider collider;
    double width;
    double height;
    double velocity;
    double dist_travelled;
    bool is_moving;
};
