#pragma once

#include <QPainter>
#include <QColor>
#include "compositeentity.h"
#include "rectcollider.h"
#include "coordinate.h"

class Checkpoint : public CompositeEntity {
public:
    Checkpoint(Coordinate *position, double velocity, std::string name);
    ~Checkpoint() override = default;

    virtual RectCollider *getCollider() override { return &collider; }

    virtual void update(bool paused, double time_since_last_frame) override;
    virtual void render(QPainter &painter) override;

    bool isMoving() { return is_moving; }

    void set_reached(bool val) { reached = val; }
    bool has_reached() { return reached; }

private:
    QPixmap image;
    RectCollider collider;
    double width;
    double height;
    double velocity;
    double dist_travelled;
    bool is_moving;
    bool reached;

};
