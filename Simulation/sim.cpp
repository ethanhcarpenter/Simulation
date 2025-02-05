#include <iostream>
#include "simpleLife.h"
#include "vector.h"
#include "confinement.h"


class Simulation {
private:
    std::unique_ptr<Confinement> confinement;
    const int TPS;

public:
    Simulation(int TPS) : TPS(TPS), confinement(nullptr) {}

    void createConfinement(double length, double width, std::string metric) {
        confinement = std::make_unique<Confinement>(length, width, metric, TPS);
    }
    Confinement& getConfinement() {
        return *confinement;
    }
	void generateRandomPath(string identifier,double time) {
        SimpleLife* life = confinement->getLifeForm(identifier);
        int lastTurn = Vector::random(-360, 360);
        for (int tick = 0; tick < time * TPS; tick++) {
		    lastTurn=life->createRandomPath(confinement->getWidth(), confinement->getLength(),tick,lastTurn);
            //renderer entry point
        }
        string filename = "random_" + identifier + ".txt";
        string points = "";
        for (auto point : *life->getJustPoints()) {
            points += point.stringFileRepresentation() + "\n";
        }
        FileHandler::writeToFile(filename, points);
	}

    void generateTargetPath(string identifier,double time,Vector target) {
        SimpleLife* life = confinement->getLifeForm(identifier);
		double angle = calculateAngle(life->getPosition(), target);
        for (int tick = 0; tick < time * TPS; tick++) {
            if (checkIfReached(life->getPosition(), target)) {
				break;
            }
            life->createTargetPath(confinement->getWidth(), confinement->getLength(), tick,angle);
            //renderer entry point
        }
        string filename = "target_" + identifier + ".txt";
        string points = "";
        for (auto point : *life->getJustPoints()) {
            points += point.stringFileRepresentation() + "\n";
        }
        FileHandler::writeToFile(filename, points);
        
    }


    double calculateAngle(Vector current,Vector target) {
        double dx = target.getValueOnAxis('x') - current.getValueOnAxis('x');
        double dz = target.getValueOnAxis('z') - current.getValueOnAxis('z');
        double angle;

        if (dx < 0 && dz < 0) {
            angle = atan(dx / dz) * 180 / PI;
            angle = 270 - abs(angle);
        }
        else if (dx > 0 && dz < 0) {
            angle = atan(dx / dz) * 180 / PI;
            angle = 270 + abs(angle);
        }
        else if (dx < 0 && dz > 0) {
            angle = atan(dx / dz) * 180 / PI;
            angle = 90 + abs(angle);
        }
        else if (dx > 0 && dz > 0) {
            angle = atan(dx / dz) * 180 / PI;
            angle = (90 - abs(angle));
        }
        else if (dz == 0 && dx > 0) {
            angle = 0;
        }
        else if (dz == 0 && dx < 0) {
            angle = 180;
        }
        else if (dx == 0 && dz > 0) {
            angle = 90;
        }
        else if (dx == 0 && dz < 0) {
            angle = 270;
        }
        return angle;
    }

	bool checkIfReached(Vector current, Vector target) {
        if (round(current.getValueOnAxis('x') * 3) / 3 == round(target.getValueOnAxis('x') * 3) / 3 &&
            round(current.getValueOnAxis('z') * 3) / 3 == round(target.getValueOnAxis('z') * 3) / 3) {
            return true;
        }
		return false;
	}

};





int main() {

    double time = 600;

	Simulation sim(30);
	sim.createConfinement(1000.0, 1000.0, "meters");

    Vector startPos(10.0, INF, 0.0);
    sim.getConfinement().addSimpleLife("Life1", 2.0, startPos, 80.0, 2.0);

    sim.generateRandomPath("Life1", time);

	sim.getConfinement().removeAllLife();
    sim.getConfinement().addSimpleLife("Life1", 2.0, startPos, 80.0, 2.0);

    sim.generateTargetPath("Life1", time,Vector::randomise(
        -sim.getConfinement().getWidth()/2, 
        -sim.getConfinement().getLength() / 2, 
        sim.getConfinement().getWidth() / 2, 
        sim.getConfinement().getLength() / 2)
    );

    return 0;
}
