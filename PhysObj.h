#pragma once
#include <iostream>
#include <math.h>
#include <ctime>

class PhysObj {											// base class that handels mass, health, and position
public:
	int hit(int damage);
	int giveM() { return mass; };
	virtual int* loCal() { static int local[2] = { xPos,yPos }; return local; }	// all loCal functions return int* to allow for array of ints: [x,y]
protected:
	int mass, health;
	int xPos, yPos;										// position is relative to X,Y grid centered at the sun
};


class SunRing : public PhysObj {						// sun / ring world class, optional peramiters for mass and health
public:
	SunRing(int m = 19890000000, int h = 1000);
	int* loCal() { static int local[2] = { xPos,yPos }; return local; }
};


class Planet : public PhysObj {							// planet class, has additional orbit radius and angle peramiters
public:
	Planet(int r = 1490000, double a = 0, int m = 1000, int h = 200);
	int* loCal();
protected:
	int orbRad;
	double angle;
};


class Ship : public PhysObj {							// ships have a velocity, acceleration, and direction angle relative to grid
public:
	int* loCal(static PhysObj(&masses)[], int numOfMass, int t, int xA = 0, int yA = 0);
protected:
	double shipAngle;
	double xVel, yVel;
	double xAccel, yAccel;
};


class Alien : public Ship {								// alien class
public:
	Alien(int health = 1, int r = 75000000);
};


class Hero : public Ship {								// player class, has option to fire a weapon
public:
	Hero();
	int* fire();
};
