#include "vector.h"

// Static random number generator
std::mt19937 Vector::gen;  

// Constructor implementations
Vector::Vector() {}
Vector::Vector(double ax, double ay, double az) {
    positionTuple.x = ax;
    positionTuple.y = ay;
    positionTuple.z = az;
}

// Member function definitions
double Vector::getValueOnAxis(char axis) const {
    if (axis == 'x') return positionTuple.x;
    else if (axis == 'y') return positionTuple.y;
    else if (axis == 'z') return positionTuple.z;
    return 0;
}

void Vector::setValueOnAxis(char axis, double value) {
    if (axis == 'x') positionTuple.x = value;
    else if (axis == 'y') positionTuple.y = value;
    else if (axis == 'z') positionTuple.z = value;
}

void Vector::moveValueOnAxis(char axis, double value) {
    if (axis == 'x') positionTuple.x += value;
    else if (axis == 'y') positionTuple.y += value;
    else if (axis == 'z') positionTuple.z += value;
}

// Static function definitions
Vector Vector::add(const Vector& v1, const Vector& v2) {
    return Vector{
        (v1.getValueOnAxis('x') == INF) ? INF : v1.getValueOnAxis('x') + v2.getValueOnAxis('x'),
        (v1.getValueOnAxis('y') == INF) ? INF : v1.getValueOnAxis('y') + v2.getValueOnAxis('y'),
        (v1.getValueOnAxis('z') == INF) ? INF : v1.getValueOnAxis('z') + v2.getValueOnAxis('z'),
    };
}

Vector Vector::subtract(const Vector& v1, const Vector& v2) {
    return Vector{
        (v1.getValueOnAxis('x') == INF) ? INF : v1.getValueOnAxis('x') - v2.getValueOnAxis('x'),
        (v1.getValueOnAxis('y') == INF) ? INF : v1.getValueOnAxis('y') - v2.getValueOnAxis('y'),
        (v1.getValueOnAxis('z') == INF) ? INF : v1.getValueOnAxis('z') - v2.getValueOnAxis('z'),
    };
}

double Vector::dot2D(const Vector& v1, const Vector& v2) {
    return v1.getValueOnAxis('x') * v2.getValueOnAxis('x') + v1.getValueOnAxis('z') * v2.getValueOnAxis('z');
}

Vector Vector::randomise(int minX, int minZ, int maxX, int maxZ, bool debug) {
    Vector a = Vector(Vector::random(minX, maxX), INF, Vector::random(minZ, maxZ));
    if (debug) {
        std::cout << a.stringDebugRepresentation() << std::endl;
    }
    return a;
}

double Vector::random(double start, double end) {
    static std::random_device rd;   // Non-deterministic random seed
    static std::mt19937 gen(rd());  // Mersenne Twister engine

    std::uniform_real_distribution<double> dist(start, end);
    return dist(gen);
}

// Debug and File Output function definitions
std::string Vector::stringDebugRepresentation() const {
    std::ostringstream oss;
    oss << "x: " << positionTuple.x
        << ", y: " << positionTuple.y
        << ", z: " << positionTuple.z;
    return oss.str();
}

std::string Vector::stringFileRepresentation() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(3)
        << (INF==(positionTuple.x) ? std::string("1e99") : std::to_string(positionTuple.x)) << " "
        << (INF==(positionTuple.y) ? std::string("1e99") : std::to_string(positionTuple.y)) << " "
        << (INF==(positionTuple.z) ? std::string("1e99") : std::to_string(positionTuple.z));
    return oss.str();
}
