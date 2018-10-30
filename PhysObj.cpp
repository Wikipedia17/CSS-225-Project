#include "PhysObj.h"

#define PI 3.14159265									// because math.h uses radians
#define BIG_G .667										// for when mass = m * 10^-20 and distance = d * 10^-5 (I think . . .)


int PhysObj::hit(int damage) {							// returns 0 if the object is destroied by  the hit
	health -= damage;

	if (health > 0)
		return health;
	else {
		mass = 0;
		return 0;
	}
}


SunRing::SunRing(int m, int h) {
	mass = m; health = h;
	xPos = 0; yPos = 0;
}


Planet::Planet(int r, double  a, int m, int h) {
	orbRad = r; angle = a;
	mass = m; health = h;
	xPos = r * cos(angle*PI / 180);
	yPos = r * sin(angle*PI / 180);
}

int* Planet::loCal() {									// assumes planets have perfectly circular orbits
	static int local[2];
	if (angle < 360)									// adds small value to angle at every call, resets at 360
		angle += .01;
	else
		angle = 0;

	xPos = orbRad * cos(angle*PI / 180);
	yPos = orbRad * sin(angle*PI / 180);
	local[0] = xPos;
	local[1] = yPos;

	return local;
}


int* Ship::loCal(static PhysObj (&masses)[], int numOfMass, int t, int xA, int yA) {
	static int local[3];
	int mLocal[2];

	for (int i = 0; i <= numOfMass; i++) {				// takes array of physics objects and uses their masses and distance to find force of gravity acting on the ships
		mLocal[2] = masses[i].loCal;
		double force = (BIG_G * masses[i].giveM / (pow(abs(mLocal[0] - xPos), 2) + pow(abs(mLocal[1] - xPos), 2)));		// G*M / r^2
		xAccel += force * cos(atan((mLocal[1] - xPos) / (mLocal[0] - xPos)));
		yAccel += force * sin(atan((mLocal[1] - xPos) / (mLocal[0] - xPos)));
	}

	xAccel += xA;										// adds additional acceleration if there is any
	yAccel += yA;
	xVel += xAccel * t;									// v_f = v_0 + a*t
	yVel += yAccel * t;

	xPos += xVel * t + .5*xAccel*t*t;					// x_f = x_0 + v*t + .5*a*t^2
	yPos += yVel * t + .5*yAccel*t*t;
	local[0] = xPos;
	local[1] = yPos;

	shipAngle = (180 * atan(yAccel / xAccel)) / PI;
	local[2] = shipAngle;

	return local;
}

Alien::Alien(int health, int r) {						// spawns ship at random location distance r away from sun
	xVel = 0; yVel = 0;
	xAccel = 0; yAccel = 0;
	srand((unsigned)time(NULL));

	xPos = r * cos(rand() % 360);
	yPos = r * sin(rand() % 360);
}

Hero::Hero() {
	xVel = 0; yVel = 1;
	xAccel = 0; yAccel = 0;
	xPos = 0; yPos = 5000000;
}

int* Hero::fire() {										// returns location of ship and it's angle at the moment fire is called
	static int wepFire[3];

	wepFire[0] = xPos;
	wepFire[1] = yPos;
	wepFire[2] = shipAngle;

	return wepFire;
}
