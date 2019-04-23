#include "MovingObject.h"

MovingObject::MovingObject() :
coordinates(0.0, 0.0),
speed(0.0, 0.0) {}

MovingObject::MovingObject(Point coordinates, Speed speed) :
coordinates(coordinates),
speed(speed) {}

MovingObject::~MovingObject() {}

void MovingObject::move(unsigned milliseconds) {
    double seconds = milliseconds / 1000.0;
    coordinates.x += speed.Vx * seconds;
    coordinates.y += speed.Vy * seconds;
}

Point MovingObject::getCoordinates() const {
    return coordinates;
}
