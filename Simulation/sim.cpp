//#pragma region Code Environment Setup
//
//#include <iostream>
//#include <sstream>
//#include <map>
//#include <cmath>
//#include <ctime>
//#include <chrono>
//#include <string>
//#include <memory>
//#include <vector>
//#include <array>
//#include <random>
//#include <fstream>
//
////constant variable for pi 
//#ifndef PI
//#define PI 3.14159265358979323846
//#endif
//#ifndef DEBUG
//#define DEBUG false
//#endif 
//
//
//
//
//using namespace std;
//using namespace chrono;
//#pragma endregion
//
//#pragma region Data Structures
////initialize the static random number generator globally
//mt19937 Vector::gen(static_cast<unsigned int>(time(0)));
//#pragma endregion
//
//#pragma region Objects
//
//
//
////base object class that any physical "thing" inherits from
//
//
//
//
//
////represents a simple organism that can move
//class SimpleLife : public Object {
//private:
//    const double movementPerTick;
//    const double mass;
//    const double meetRadius;
//    const double TPS;
//    const string identifier;
//    vector<tuple<int, Vector>> points;
//    vector<Vector> justPoints;
//
//public:
//    SimpleLife(string identifier, double avgSpeed, Vector startingPosition, double mass, double meetRadius, double TPS)
//        : Object(startingPosition), identifier(identifier), mass(mass), meetRadius(meetRadius), TPS(TPS), movementPerTick(avgSpeed / TPS) {
//        //get the average movement per tick
//        points.push_back({ 0 ,startingPosition });
//    }
//    //return meet radius
//    double getMeetRadius() {
//        return meetRadius;
//    }
//    //return the generated path
//    vector<tuple<int, Vector>>* getPath() {
//        return &points;
//    }
//    //randomly generate a walk
//    void createRandomPath(double time, double width, double length) {
//        points.reserve(time * TPS + 10);
//        //inita turn from the center
//        int lastTurn = Vector::random(-360, 360);
//
//        //move every tick
//        for (int i = 0; i < int(TPS * time); i++) {
//            while (true) {
//                //limit degree of motion to create realism
//                int randomDeviation = Vector::random(-5, 5);
//                //add or subtract to create new angle as all angles are bearings and ensure angle in range
//                lastTurn = (lastTurn + randomDeviation) % 360;
//                //get trig values of the angle
//                double cosLastTurn = cos((lastTurn + 360) * PI / 180.0);
//                double sinLastTurn = sin((lastTurn + 360) * PI / 180.0);
//                //CAH adjacent=hypotenuse*cos(theta) cahnge in x = move per tick*cos(lastTurn)
//                double moveX = (movementPerTick * cosLastTurn);
//                //SOH opposite=hypotenuse*cossintheta) cahnge in y = move per tick*sin(lastTurn)
//                double moveZ = (movementPerTick * sinLastTurn);
//
//                //get new x and y co ordinates
//                double newX = getPositionOnAxis('x') + moveX;
//                double newZ = getPositionOnAxis('z') + moveZ;
//
//                //check if new co ordintaes are within the bounds of the space
//                if (abs(newX) <= width / 2 && abs(newZ) <= length / 2) {
//                    //move to new position
//                    moveInDirection('x', moveX);
//                    moveInDirection('z', moveZ);
//                    //add the new position and the tick to the list of paths
//                    points.push_back({ i, Vector{ getPositionOnAxis('x'), getPositionOnAxis('y'), getPositionOnAxis('z') } });
//                    justPoints.push_back(Vector{ getPositionOnAxis('x'), getPositionOnAxis('y'), getPositionOnAxis('z') });
//                    break;
//                }
//            }
//        }
//        //create file of points
//        string filename = "./outputs/paths/generatedPaths/random_" + identifier + ".txt";
//        string points = "";
//        for (auto point : justPoints) {
//            points += point.stringFileRepresentation() + "\n";
//        }
//        FileHandler::writeToFile(filename, points);
//    }
//    //create a path to a target
//    void createTargetPath(double time, double width, double length, Vector target) {
//        points.reserve(time * TPS + 10);
//
//        double dx = target.getValueOnAxis('x') - getPositionOnAxis('x');
//        double dz = target.getValueOnAxis('z') - getPositionOnAxis('z');
//        double angle;
//
//        if (dx < 0 && dz < 0) {
//            angle = atan(dx / dz) * 180 / PI;
//            angle = 270 - abs(angle);
//            //cout<<"top right"<<endl;
//        }
//        else if (dx > 0 && dz < 0) {
//            angle = atan(dx / dz) * 180 / PI;
//            angle = 270 + abs(angle);
//            //cout<<"top left"<<endl;
//        }
//        else if (dx < 0 && dz>0) {
//            angle = atan(dx / dz) * 180 / PI;
//            angle = 90 + abs(angle);
//            //cout<<"bottom right"<<endl;
//        }
//        else if (dx > 0 && dz > 0) {
//            angle = atan(dx / dz) * 180 / PI;
//            angle = (90 - abs(angle));
//            //cout<<"bottom left"<<endl;
//        }
//
//        string filename = "./outputs/debug/angles/angle_" + identifier + ".txt";
//        ostringstream oss;
//        oss
//            << "target: " << target.stringDebugRepresentation() << "\n"
//            << "Current Position: " << getPosition().stringDebugRepresentation() << "\n"
//            << "Difference : " << "dx: " << dx << "dz: " << dz << "\n"
//            << "Angle: " << angle << "\n";
//        FileHandler::writeToFile(filename, oss.str());
//
//        //move every tick
//        for (int i = 0; i < int(TPS * time); i++) {
//            if (round(getPositionOnAxis('x') * 3) / 3 == round(target.getValueOnAxis('x') * 3) / 3 &&
//                round(getPositionOnAxis('z') * 3) / 3 == round(target.getValueOnAxis('z') * 3) / 3) {
//                break;
//            }
//            //get trig values of the angle
//            double cosLastTurn = cos((angle + 360) * PI / 180.0);
//            double sinLastTurn = sin((angle + 360) * PI / 180.0);
//            //CAH adjacent=hypotenuse*cos(theta) cahnge in x = move per tick*cos(lastTurn)
//            double moveX = (movementPerTick * cosLastTurn);
//            //SOH opposite=hypotenuse*cossintheta) cahnge in y = move per tick*sin(lastTurn)
//            double moveZ = (movementPerTick * sinLastTurn);
//
//            //get new x and y co ordinates
//            double newX = getPositionOnAxis('x') + moveX;
//            double newZ = getPositionOnAxis('z') + moveZ;
//
//            //move to new position
//            moveInDirection('x', moveX);
//            moveInDirection('z', moveZ);
//            //add the new position and the tick to the list of paths
//            points.push_back({ i, Vector{ getPositionOnAxis('x'), getPositionOnAxis('y'), getPositionOnAxis('z') } });
//            justPoints.push_back(Vector{ getPositionOnAxis('x'), getPositionOnAxis('y'), getPositionOnAxis('z') });
//        }
//        //create file of points
//        filename = "./outputs/paths/generatedPaths/target_" + identifier + ".txt";
//        string points = "";
//        for (auto point : justPoints) {
//            points += point.stringFileRepresentation() + "\n";
//        }
//        FileHandler::writeToFile(filename, points);
//    }
//    //reset all values and reutrn to a specified position
//    void resetLifeForm(Vector startingPosition) {
//        move(startingPosition);
//        points.clear();
//        points.push_back({ 0 ,startingPosition });
//    }
//    //debug: returns a string of the movement per tick and amount of points in the path
//    string getDetails() {
//        ostringstream oss;
//        oss << "ID:" << identifier << ", MPT: " << movementPerTick << ", Points: " << points.size();
//        return oss.str();
//    }
//};
//
//
//
//#pragma endregion
//
//vector<string> generateNames(int x) {
//    vector<string> names;
//    for (int i = 1; i <= x; ++i) {
//        names.push_back("person" + to_string(i));
//    }
//    return names;
//}
//
//
//int main() {
//    Timer timer;
//    Confinement space(1000, 1000, "m", 20);
//
//    vector<string> names = generateNames(100);
//
//    timer.start();
//    for (const auto& name : names) {
//        space.addSimpleLife(name, 2.0, Vector::randomise(-space.getLength() / 2, -space.getWidth() / 2, space.getLength() / 2, space.getWidth() / 2), 80, 1);
//    }
//
//    auto lifes = space.getAllLifeForms();
//    for (auto life : lifes) {
//        life->createRandomPath(1000, space.getLength(), space.getWidth());
//    }
//    space.removeAllLife();
//
//
//    for (const auto& name : names) {
//        space.addSimpleLife(name, 2.0, Vector::randomise(-space.getLength() / 2, -space.getWidth() / 2, space.getLength() / 2, space.getWidth() / 2), 80, 1);
//    }
//
//    lifes = space.getAllLifeForms();
//    Vector target = Vector::randomise(-space.getLength() / 2, -space.getWidth() / 2, space.getLength() / 2, space.getWidth() / 2, true);
//
//    for (auto life : lifes) {
//        life->createTargetPath(1000, space.getLength(), space.getWidth(), target);
//    }
//    cout << timer.elapsed() << endl;
//
//    return 0;
//
//}