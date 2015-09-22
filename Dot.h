#pragma once
#include <SDL.h>
#include "LTexture.h"
#include "globals.h"
#include "LTimer.h"
#include "Player1.h"
#include "Player2.h"

//A circle structure
struct Circle
{
	double x, y;
	int r;
};

class Dot
{
public:
	//Maximum axis velocity of the dot
	static const int DOT_VEL = 320;

	//Initializes the Dot
	Dot(int x, int y);

	//Destroys the Dot's resources
	~Dot();

	//Moves the dot and checks for collision
	void move(double timeForMovement, Player1* p1, Player2* p2);

	//Shows the dot on the screen
	void render();

	//Gets collision circle
	Circle& getCollider();

	//Circle/Player collision detector
	void checkCollision(Circle& a, Block* p);

	//Resolves horizontal collisions
	void resolveHCollision(Block* p);

	//Sets the time since reset
	void setTime(float time);

	//Gets the time since reset
	float getTime();

	//The Dot texture
	LTexture dotTexture;

	//The Dot timer
	LTimer dotTimer;

private:
	//The X and Y offsets of the dot
	double mPosX, mPosY;

	//The velocity of the dot
	int mVelX, mVelY;

	//Dot's collision circle
	Circle mCollider;

	//Moves the collision circle relative to the dot's offset
	void shiftColliders();

	//The time since the last timer reset
	float timeSinceReset;

	//Indicates if the Dot has already hit the top of a block
	bool hitTopOfBlock = false;
};

//Distance formula
double distanceSquared(double x1, double y1, double x2, double y2);

//The dimensions of the dot
static const int DOT_WIDTH = 20;
static const int DOT_HEIGHT = 20;

//Determines if a dot currently exists
extern bool dotExists;
