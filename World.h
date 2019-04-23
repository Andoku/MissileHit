#ifndef WORLD_H
#define WORLD_H

#include <memory>

#include "MovingObject.h"

class World {
public:
    World();
    ~World();
    
    void createWorld();
    void runSimulation();
    
private:
    std::unique_ptr<MovingObject> airplane;
    std::unique_ptr<MovingObject> missile;
    StartParameters startParameters;
    unsigned simulationTime;
    
    void printSimulationState() const;
    bool checkExitCondition() const;
    bool checkMissileHit() const;
    bool checkDistanceDecreased(double previousDistance) const;
};

#endif /* WORLD_H */
