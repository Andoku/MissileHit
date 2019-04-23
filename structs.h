/** 
 * @file structs.h
 * @author anton
 * @date April 23, 2019
 */

#ifndef STRUCTS_H
#define STRUCTS_H

#include <iostream>
#include <cmath>

struct Point {
    double x;
    double y;
    
    Point() :
    x(0),
    y(0) {}
    
    Point(double x, double y) :
    x(x),
    y(y) {}
};

struct Speed {
    double Vx;
    double Vy;
    
    Speed() :
    Vx(0),
    Vy(0) {}
    
    Speed(double speedModulus, double angle) :
    Vx(std::cos(angle * M_PI / 180.0) * speedModulus),
    Vy(std::sin(angle * M_PI / 180.0) * speedModulus) {}
};

struct StartParameters {
    double airplaneHeight = 0.0;
    double airplaneDistance = 0.0;
    double airplaneSpeed = 0.0;
    double missileSpeed = 0.0;
    double missileAngle = 0.0;
    double hitRadius = 0.0;
};

inline std::ostream &operator<<(std::ostream &output, const Point &point) {
    output << "(" << point.x << ", " << point.y << ")";
    return output;
}

inline std::istream &operator>>(std::istream &input, StartParameters &startParameters) {
    std::cout << "Airplane height [m] = ";
    input >> startParameters.airplaneHeight;
    std::cout << "Airplane distance [m] = ";
    input >> startParameters.airplaneDistance;
    std::cout << "Airplane speed [m/sec] = ";
    input >> startParameters.airplaneSpeed;
    std::cout << "Missile speed [m/sec] = ";
    input >> startParameters.missileSpeed;
    std::cout << "Missile angle [deg] = ";
    input >> startParameters.missileAngle;
    std::cout << "Hit radius [m] = ";
    input >> startParameters.hitRadius;
    return input;
}

#endif /* STRUCTS_H */