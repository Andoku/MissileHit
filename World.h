#ifndef WORLD_H
#define WORLD_H

#include <deque>
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
    mutable std::deque<double> previousDistances;
    
    void printSimulationState() const;
    bool checkExitCondition() const;
    bool checkMissileHit() const;
    bool checkDistanceDecreased() const;
};

#endif /* WORLD_H */
