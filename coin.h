#pragma once

#include <QPainter>
#include "rectcollider.h"
#include "coordinate.h"
#include "compositeentity.h"


class Coin : public CompositeEntity {
public:
    Coin(Coordinate *position, double velocity, std::string name);
    ~Coin() override = default;

    virtual RectCollider *getCollider() override {return &collider; }

    virtual void update(bool paused, double time_since_last_frame) override;
    virtual void render(QPainter &painter) override;

    bool isMoving() { return is_moving; }

    void set_isCollected(bool val) { is_collected = val; }
    bool isCollected() { return is_collected; }

private:
    QPixmap image;
    RectCollider collider;
    double width;
    double height;
    double velocity;
    double dist_travelled;
    bool is_moving;
    bool is_collected;
};
