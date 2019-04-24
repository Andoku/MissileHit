#ifndef WORLD_H
#define WORLD_H

#include <deque>
#include <memory>
#include <chrono>

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
    
    typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::milliseconds milliseconds;
    typedef std::chrono::seconds seconds;
    Clock::time_point simulationStart;
    
    mutable std::deque<double> previousDistances;
    
    void printSimulationState() const;
    bool checkExitCondition() const;
    bool checkMissileHit() const;
    bool checkDistanceDecreased() const;
};

#endif /* WORLD_H */
