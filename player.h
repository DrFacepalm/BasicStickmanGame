#pragma once

#include "compositeentity.h"

class Coordinate;

class Coordinate;

class Player : public CompositeEntity {

public:
    Player(Coordinate* position, std::string name);
    virtual void jump() = 0;
    virtual void setJumpHeight(int height) = 0;
};

