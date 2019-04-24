#include <iostream>
#include <iomanip>
#include <thread>

#include "World.h"
#include "structs.h"

World::World() :
airplane(new MovingObject()),
missile(new MovingObject()),
startParameters(),
simulationStart(Clock::now()),
printTime(Clock::now()) {}

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
    Clock::time_point calcTime = Clock::now();
    simulationStart = Clock::now();
    
    for(;;) {
        const auto timeDiff = Clock::now() - calcTime;
        const unsigned dt = std::chrono::duration_cast<milliseconds>(timeDiff).count();
        airplane->move(dt);
        missile->move(dt);
        calcTime = Clock::now();
        
        printSimulationState();
        
        if(checkExitCondition()) {
            return;
        }

        const unsigned sleepTime = 10;
        std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
    }
}

void World::printSimulationState() const {
    const unsigned timeout = 200;
    const auto printDifference = Clock::now() - printTime;
    if(std::chrono::duration_cast<milliseconds>(printDifference).count() < timeout) {
        return;
    }
    
    const auto timeDiff = Clock::now() - simulationStart;
    const unsigned sec = std::chrono::duration_cast<seconds>(timeDiff).count();
    const unsigned millisec = std::chrono::duration_cast<milliseconds>(timeDiff).count() % 1000;
    std::cout << "time = " << sec << ".";
    std::cout << std::setfill('0') << std::setw(3) << millisec << ", ";
    std::cout << std::fixed << std::setprecision(1);
    const Point airplaneCoordinates = airplane->getCoordinates();
    std::cout << "airplane = " << airplaneCoordinates << ", ";
    const Point missileCoordinates = missile->getCoordinates();
    std::cout << "missile = " << missileCoordinates << ", ";
    const double distance = missileCoordinates.distance(airplaneCoordinates);
    std::cout << "distance = " << distance << "\n";
    printTime = Clock::now();
}

bool World::checkExitCondition() const {
    if(checkMissileHit()) {
        std::cout << "Airplane destroyed!" << "\n";
        return true;
    }

    if(!checkDistanceDecreased()) {
        std::cout << "Airplane can't be reached!" << "\n";
        return true;
    }
    
    return false;
}

bool World::checkMissileHit() const {
    const Point missileCoordinates = missile->getCoordinates();
    const Point airplaneCoordinates = airplane->getCoordinates();
    const double distance = missileCoordinates.distance(airplaneCoordinates);
    const bool hit = (distance <= startParameters.hitRadius);
    return hit;
}

bool World::checkDistanceDecreased() const {
    const Point missileCoordinates = missile->getCoordinates();
    const Point airplaneCoordinates = airplane->getCoordinates();
    const double distance = missileCoordinates.distance(airplaneCoordinates);
    previousDistances.push_back(distance);

    const int maxSize = 100;
    if(previousDistances.size() < maxSize) {
        return true;
    }

    previousDistances.pop_front();
    return previousDistances.back() < previousDistances.front();
}
