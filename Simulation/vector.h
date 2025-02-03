#pragma once
#include <iostream>
#include <sstream>
#include <random>
#include <string>

constexpr double INF = 1e99;

struct PositionTuple {
    double x = INF, y = INF, z = INF;
};

class Vector {
private:
    PositionTuple positionTuple;
public:
    // Constructors
    Vector();
    Vector(double ax, double ay, double az);

    // Member functions
    double getValueOnAxis(char axis) const;
    void setValueOnAxis(char axis, double value);
    void moveValueOnAxis(char axis, double value);

    // Static functions
    static Vector add(const Vector& v1, const Vector& v2);
    static Vector subtract(const Vector& v1, const Vector& v2);
    static double dot2D(const Vector& v1, const Vector& v2);
    static std::mt19937 gen;
    static Vector randomise(int minX, int minZ, int maxX, int maxZ, bool debug = false);
    static double random(double start = 0, double end = 0);

    // Debug and File Output
    std::string stringDebugRepresentation() const;
    std::string stringFileRepresentation() const;
};
