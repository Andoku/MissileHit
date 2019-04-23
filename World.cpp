#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>

#include "World.h"
#include "structs.h"

World::World() :
airplane(new MovingObject()),
missile(new MovingObject()),
startParameters(),
simulationTime(0) {}

World::~World() {}

void World::createWorld() {
    std::cin >> startParameters;
    
    const Point airplaneCoordinates(startParameters.airplaneDistance, 
                                    startParameters.airplaneHeight);
    const Speed airplaneSpeed(startParameters.airplaneSpeed, 180.0);
    airplane = std::unique_ptr<MovingObject>(new MovingObject(airplaneCoordinates, airplaneSpeed));
    
    const Point missileCoordinates(0, 0);
    const Speed missileSpeed(startParameters.missileSpeed, startParameters.missileAngle);
    missile = std::unique_ptr<MovingObject>(new MovingObject(missileCoordinates, missileSpeed));
}

void World::runSimulation() {
    simulationTime = 0;
    
    for(;;) {
        if(checkExitCondition()) {
            return;
        }
        
        const unsigned dt = 10;
        airplane->move(dt);
        missile->move(dt);
        
        simulationTime += dt;
        
        printSimulationState();
        
        const unsigned sleepTime = 10;
        std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
    }
}

void World::printSimulationState() const {
    const unsigned seconds = simulationTime / 1000;
    const unsigned milliseconds = simulationTime % 1000;
    std::cout << "time = " << seconds << ".";
    std::cout << std::setfill('0') << std::setw(3) << milliseconds << ", ";
    const Point airplaneCoordinates = airplane->getCoordinates();
    std::cout << "airplane = " << airplaneCoordinates << ", ";
    const Point missileCoordinates = missile->getCoordinates();
    std::cout << "missile = " << missileCoordinates << ", ";
    const double distance = missileCoordinates.distance(airplaneCoordinates);
    std::cout << "distance = " << distance << "\n";
}

bool World::checkExitCondition() const {
    if(missileHit()) {
        std::cout << "Airplane destroyed!" << "\n";
        return true;
    }
    
    return false;
}

bool World::missileHit() const {
    const Point missileCoordinates = missile->getCoordinates();
    const Point airplaneCoordinates = airplane->getCoordinates();
    const double distance = missileCoordinates.distance(airplaneCoordinates);
    const bool hit = distance <= startParameters.hitRadius;
    return hit;
}
