#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H

#include "structs.h"

class MovingObject {
public:
    MovingObject();
    MovingObject(Point coordinates, Speed speed);
    ~MovingObject();
    
    void move(unsigned milliseconds);
    Point getCoordinates() const;
    
private:
    Point coordinates;
    Speed speed;
};

#endif /* MOVINGOBJECT_H */
