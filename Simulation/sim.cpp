#pragma region Code Environment Setup

#include <iostream>
#include <sstream>
#include <map>
#include <cmath>
#include <ctime>
#include <chrono>
#include <string>
#include <memory>
#include <vector>
#include <array>
#include <random>
#include <fstream>

//constant variable for pi 
#ifndef PI
#define PI 3.14159265358979323846
#endif
#ifndef DEBUG
#define DEBUG false
#endif 

#define inf double(1e99)


using namespace std;
using namespace chrono;
#pragma endregion

#pragma region Data Structures



//custom struct to represent co ordinates 
struct PositionTuple {
    double x = inf, y = inf, z = inf;
};

//custom data structure to store and manipulate co ordinates
class Vector {
private:
    PositionTuple positionTuple;
public:
    //empty constructor for null Vectors
    Vector() {}
    Vector(double ax, double ay, double az) {
        positionTuple.x = ax;
        positionTuple.y = ay;
        positionTuple.z = az;
    }
    //return the value on a specified axis
    double getValueOnAxis(char axis) {
        if (axis == 'x') return positionTuple.x;
        else if (axis == 'y') return positionTuple.y;
        else if (axis == 'z') return positionTuple.z;
        return 0;
    }
    //set the value on a specified axis
    void setValueOnAxis(char axis, double value) {
        if (axis == 'x') positionTuple.x = value;
        else if (axis == 'y') positionTuple.y = value;
        else if (axis == 'z') positionTuple.z = value;
    }
    //add or subtract to the current value of a specified axis
    void moveValueOnAxis(char axis, double value) {
        if (axis == 'x') positionTuple.x += +value;
        else if (axis == 'y') positionTuple.y += value;
        else if (axis == 'z') positionTuple.z += value;
    }
    //add 2 vectors
    static Vector add(Vector v1, Vector v2) {
        return Vector{
            (v1.getValueOnAxis('y') == inf) ? inf : v1.getValueOnAxis('x') + v2.getValueOnAxis('x'),
            (v1.getValueOnAxis('y') == inf) ? inf : v1.getValueOnAxis('y') + v2.getValueOnAxis('y'),
            (v1.getValueOnAxis('y') == inf) ? inf : v1.getValueOnAxis('z') + v2.getValueOnAxis('z'),
        };
    }
    //subtract 2 vectors
    static Vector subtract(Vector v1, Vector v2) {
        return Vector{
            (v1.getValueOnAxis('y') == inf) ? inf : v1.getValueOnAxis('x') - v2.getValueOnAxis('x'),
            (v1.getValueOnAxis('y') == inf) ? inf : v1.getValueOnAxis('y') - v2.getValueOnAxis('y'),
            (v1.getValueOnAxis('y') == inf) ? inf : v1.getValueOnAxis('z') - v2.getValueOnAxis('z'),
        };
    }
    //dot product of 2 vectors x and z only
    static double  dot2D(Vector v1, Vector v2) {
        return v1.getValueOnAxis('x') * v2.getValueOnAxis('x') + v1.getValueOnAxis('z') * v2.getValueOnAxis('z');
    }
    static Vector randomise(int minX, int minZ, int maxX, int maxZ, bool debug = false) {
        Vector a = Vector(Vector::random(minX, maxX), inf, Vector::random(minZ, maxZ));
        if (debug) {
            cout << a.stringDebugRepresentation() << endl;
        }
        return a;
    }
    //global random number generator
    static mt19937 gen;
    static double random(double start = 0, double end = 0) {
        uniform_real_distribution<> dist(start, end);
        return dist(gen);
    }
    //debug: return a string of each of the values of the axis
    string stringDebugRepresentation() {
        ostringstream oss;
        oss << "x: " << positionTuple.x
            << ", y: " << positionTuple.y
            << ", z: " << positionTuple.z;
        return oss.str();
    }
    string stringFileRepresentation() {
        ostringstream oss;
        oss << positionTuple.x << " " << positionTuple.y << " " << positionTuple.z;
        return oss.str();
    }
};

class Timer {
private:
    chrono::high_resolution_clock::time_point startTime;

public:
    void start() {
        startTime = chrono::high_resolution_clock::now();
    }
    double elapsed() {
        auto endTime = chrono::high_resolution_clock::now();
        return chrono::duration<double>(endTime - startTime).count();
    }
};

//initialize the static random number generator globally
mt19937 Vector::gen(static_cast<unsigned int>(time(0)));
#pragma endregion

#pragma region Objects

class FileHandler {
public:
    static void writeToFile(string filename, string data) {

        ofstream file(filename, ios::out | ios::app);
        file << data;
    }
};

//base object class that any physical "thing" inherits from
class Object {
private:
    //where the object is
    Vector position;

public:
    Object(Vector startingPosition)
        : position(startingPosition) {
    }
    //rellocate the object to a new position
    void move(Vector newPosition) {
        position = newPosition;
    }

    //add ior subtract from a specified axis
    void moveInDirection(char axis, double amount) {
        position.moveValueOnAxis(axis, amount);
    }
    //return the position vector
    Vector getPosition() const {
        return position;
    }
    //return the value on a specified axis
    double getPositionOnAxis(char axis) {
        return position.getValueOnAxis(axis);
    }


};




//represents a simple organism that can move
class SimpleLife : public Object {
private:
    const double movementPerTick;
    const double mass;
    const double meetRadius;
    const double TPS;
    const string identifier;
    vector<tuple<int, Vector>> points;
    vector<Vector> justPoints;

public:
    SimpleLife(string identifier, double avgSpeed, Vector startingPosition, double mass, double meetRadius, double TPS)
        : Object(startingPosition), identifier(identifier), mass(mass), meetRadius(meetRadius), TPS(TPS), movementPerTick(avgSpeed / TPS) {
        //get the average movement per tick
        points.push_back({ 0 ,startingPosition });
    }
    //return meet radius
    double getMeetRadius() {
        return meetRadius;
    }
    //return the generated path
    vector<tuple<int, Vector>>* getPath() {
        return &points;
    }
    //randomly generate a walk
    void createRandomPath(double time, double width, double length) {
        points.reserve(time * TPS + 10);
        //inita turn from the center
        int lastTurn = Vector::random(-360, 360);

        //move every tick
        for (int i = 0; i < int(TPS * time); i++) {
            while (true) {
                //limit degree of motion to create realism
                int randomDeviation = Vector::random(-5, 5);
                //add or subtract to create new angle as all angles are bearings and ensure angle in range
                lastTurn = (lastTurn + randomDeviation) % 360;
                //get trig values of the angle
                double cosLastTurn = cos((lastTurn + 360) * PI / 180.0);
                double sinLastTurn = sin((lastTurn + 360) * PI / 180.0);
                //CAH adjacent=hypotenuse*cos(theta) cahnge in x = move per tick*cos(lastTurn)
                double moveX = (movementPerTick * cosLastTurn);
                //SOH opposite=hypotenuse*cossintheta) cahnge in y = move per tick*sin(lastTurn)
                double moveZ = (movementPerTick * sinLastTurn);

                //get new x and y co ordinates
                double newX = getPositionOnAxis('x') + moveX;
                double newZ = getPositionOnAxis('z') + moveZ;

                //check if new co ordintaes are within the bounds of the space
                if (abs(newX) <= width / 2 && abs(newZ) <= length / 2) {
                    //move to new position
                    moveInDirection('x', moveX);
                    moveInDirection('z', moveZ);
                    //add the new position and the tick to the list of paths
                    points.push_back({ i, Vector{ getPositionOnAxis('x'), getPositionOnAxis('y'), getPositionOnAxis('z') } });
                    justPoints.push_back(Vector{ getPositionOnAxis('x'), getPositionOnAxis('y'), getPositionOnAxis('z') });
                    break;
                }
            }
        }
        //create file of points
        string filename = "./outputs/paths/generatedPaths/random_" + identifier + ".txt";
        string points = "";
        for (auto point : justPoints) {
            points += point.stringFileRepresentation() + "\n";
        }
        FileHandler::writeToFile(filename, points);
    }
    //create a path to a target
    void createTargetPath(double time, double width, double length, Vector target) {
        points.reserve(time * TPS + 10);

        double dx = target.getValueOnAxis('x') - getPositionOnAxis('x');
        double dz = target.getValueOnAxis('z') - getPositionOnAxis('z');
        double angle;

        if (dx < 0 && dz < 0) {
            angle = atan(dx / dz) * 180 / PI;
            angle = 270 - abs(angle);
            //cout<<"top right"<<endl;
        }
        else if (dx > 0 && dz < 0) {
            angle = atan(dx / dz) * 180 / PI;
            angle = 270 + abs(angle);
            //cout<<"top left"<<endl;
        }
        else if (dx < 0 && dz>0) {
            angle = atan(dx / dz) * 180 / PI;
            angle = 90 + abs(angle);
            //cout<<"bottom right"<<endl;
        }
        else if (dx > 0 && dz > 0) {
            angle = atan(dx / dz) * 180 / PI;
            angle = (90 - abs(angle));
            //cout<<"bottom left"<<endl;
        }

        string filename = "./outputs/debug/angles/angle_" + identifier + ".txt";
        ostringstream oss;
        oss
            << "target: " << target.stringDebugRepresentation() << "\n"
            << "Current Position: " << getPosition().stringDebugRepresentation() << "\n"
            << "Difference : " << "dx: " << dx << "dz: " << dz << "\n"
            << "Angle: " << angle << "\n";
        FileHandler::writeToFile(filename, oss.str());

        //move every tick
        for (int i = 0; i < int(TPS * time); i++) {
            if (round(getPositionOnAxis('x') * 3) / 3 == round(target.getValueOnAxis('x') * 3) / 3 &&
                round(getPositionOnAxis('z') * 3) / 3 == round(target.getValueOnAxis('z') * 3) / 3) {
                break;
            }
            //get trig values of the angle
            double cosLastTurn = cos((angle + 360) * PI / 180.0);
            double sinLastTurn = sin((angle + 360) * PI / 180.0);
            //CAH adjacent=hypotenuse*cos(theta) cahnge in x = move per tick*cos(lastTurn)
            double moveX = (movementPerTick * cosLastTurn);
            //SOH opposite=hypotenuse*cossintheta) cahnge in y = move per tick*sin(lastTurn)
            double moveZ = (movementPerTick * sinLastTurn);

            //get new x and y co ordinates
            double newX = getPositionOnAxis('x') + moveX;
            double newZ = getPositionOnAxis('z') + moveZ;

            //move to new position
            moveInDirection('x', moveX);
            moveInDirection('z', moveZ);
            //add the new position and the tick to the list of paths
            points.push_back({ i, Vector{ getPositionOnAxis('x'), getPositionOnAxis('y'), getPositionOnAxis('z') } });
            justPoints.push_back(Vector{ getPositionOnAxis('x'), getPositionOnAxis('y'), getPositionOnAxis('z') });
        }
        //create file of points
        filename = "./outputs/paths/generatedPaths/target_" + identifier + ".txt";
        string points = "";
        for (auto point : justPoints) {
            points += point.stringFileRepresentation() + "\n";
        }
        FileHandler::writeToFile(filename, points);
    }
    //reset all values and reutrn to a specified position
    void resetLifeForm(Vector startingPosition) {
        move(startingPosition);
        points.clear();
        points.push_back({ 0 ,startingPosition });
    }
    //debug: returns a string of the movement per tick and amount of points in the path
    string getDetails() {
        ostringstream oss;
        oss << "ID:" << identifier << ", MPT: " << movementPerTick << ", Points: " << points.size();
        return oss.str();
    }
};

class Confinement {
private:
    map<string, unique_ptr<class SimpleLife>> lifeForms;
    const double length;
    const double width;
    const string metric;
    const int TPS;

public:
    Confinement(double length, double width, string metric, int TPS)
        : length(length), width(width), metric(metric), TPS(TPS) {
    }

    //retrun ticks per second
    int getTPS() {
        return TPS;
    }
    //return length of confinement
    double getLength() {
        return length;
    }
    //return width of confinement
    double getWidth() {
        return width;
    }
    //create a simple life form within the confinement 
    void addSimpleLife(string identifier, double avgSpeed, Vector startingPosition, double mass, double meetRadius) {
        lifeForms[identifier] = make_unique<SimpleLife>(identifier, avgSpeed, startingPosition, mass, meetRadius, getTPS());
    }
    //return a life form with specified identifier
    SimpleLife* getLifeForm(string identifier) {
        return lifeForms[identifier].get();
    }
    //return all life forms
    vector<SimpleLife*> getAllLifeForms() {
        vector<SimpleLife*> allLife;
        for (int i = 0; i < lifeForms.size(); i++) {
            auto it = lifeForms.begin();
            //like a pointer advance it to the ith position
            advance(it, i);
            //add the life to the vector
            allLife.push_back(it->second.get());
        }
        return allLife;
    }
    //clea the list of life forms
    void removeAllLife() {
        lifeForms.clear();
    }
};

class Photon {
private:
    double speed = 3e8;

};

#pragma endregion

vector<string> generateNames(int x) {
    vector<string> names;
    for (int i = 1; i <= x; ++i) {
        names.push_back("person" + to_string(i));
    }
    return names;
}


int main() {
    Timer timer;
    Confinement space(1000, 1000, "m", 20);

    vector<string> names = generateNames(100);

    timer.start();
    for (const auto& name : names) {
        space.addSimpleLife(name, 2.0, Vector::randomise(-space.getLength() / 2, -space.getWidth() / 2, space.getLength() / 2, space.getWidth() / 2), 80, 1);
    }

    auto lifes = space.getAllLifeForms();
    for (auto life : lifes) {
        life->createRandomPath(1000, space.getLength(), space.getWidth());
    }
    space.removeAllLife();


    for (const auto& name : names) {
        space.addSimpleLife(name, 2.0, Vector::randomise(-space.getLength() / 2, -space.getWidth() / 2, space.getLength() / 2, space.getWidth() / 2), 80, 1);
    }

    lifes = space.getAllLifeForms();
    Vector target = Vector::randomise(-space.getLength() / 2, -space.getWidth() / 2, space.getLength() / 2, space.getWidth() / 2, true);

    for (auto life : lifes) {
        life->createTargetPath(1000, space.getLength(), space.getWidth(), target);
    }
    cout << timer.elapsed() << endl;

    return 0;

}