#pragma once

#include <QPainter>
#include <QColor>
#include "compositeentity.h"
#include "config.h"
#include <QPen>
#include <string>
#include <sstream>


class LifeDisplay : public CompositeEntity {
public:
    LifeDisplay(Coordinate *position, int lives);
    ~LifeDisplay() override = default;

    virtual void update(bool paused, double time_since_last_frame);
    virtual void render(QPainter &painter) override;

    virtual void setLives(int val);
    virtual int getLives();
    void lowerLife();
private:
    int lives;
};
