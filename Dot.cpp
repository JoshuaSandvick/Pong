#include "Dot.h"
#include "GameState.h"
#include <cmath>
#include <string>

Dot::Dot(int x, int y)
{
	//Initializes the offsets
	mPosX = (double)x;
	mPosY = (double)y;

	//Initializes the velocity
	mVelX = DOT_VEL;
	mVelY = DOT_VEL;

	//Set collision circle size
	mCollider.r = DOT_WIDTH / 2;

	//Move collider relative to the circle
	shiftColliders();

	//Show that a Dot exists
	dotExists = true;
}


Dot::~Dot()
{
	dotTexture.~LTexture();
}


void Dot::move(double timeForMovement, Player1* p1, Player2* p2)
{
	//Move the dot left or right
	mPosX += mVelX * timeForMovement;

	//If the dot went too far to the left or right
	if (mPosX - mCollider.r < 0) {
		//Change the score
		p2Score++;
		
		//Delete this dot
		dotExists = false;
	}
	else if (mPosX + mCollider.r > SCREEN_WIDTH) {
		//Change the score
		p1Score++;
		
		//Delete this dot
		dotExists = false;
	}	


	//Move the dot up or down
	mPosY += mVelY * timeForMovement;

	//If the dot went too far up or down
	if (mPosY - mCollider.r < 0) {
		//Move back Dot and collider
		mPosY = mCollider.r;
		mVelY = -mVelY;
		mVelY -= 10 * (mVelY / -mVelY);
	}
	else if (mPosY + mCollider.r > SCREEN_HEIGHT) {
		//Move back Dot and Collider
		mPosY = SCREEN_HEIGHT - mCollider.r;
		mVelY = -mVelY;
		mVelY -= 10 * (mVelY / -mVelY);
	}
	
	//Shift the position of the collider
	shiftColliders();

	//If the Dot hasn't already rebounded off of the top of a Block
	if (!hitTopOfBlock) {
		//Check for and resolve collisions
		checkCollision(mCollider, p1);
		checkCollision(mCollider, p2);
	}	
}


void Dot::render()
{
	//Show the dot
	dotTexture.render((int)(mPosX - mCollider.r), (int)(mPosY - mCollider.r));
}

void Dot::checkCollision(Circle& a, Block* p)
{
	//Closest point on collision box
	double cX, cY;

	//The sides of the rectangle
	int leftR;
	int rightR;
	int topR;
	int bottomR;

	//Calculate the sides of the dot Rect
	leftR = p->getRect().x;
	rightR = p->getRect().x + p->getRect().w;
	topR = p->getRect().y;
	bottomR = p->getRect().y + p->getRect().h;

	//Find closest x offset
	if (a.x < leftR) {
		cX = leftR;
	}
	else if (a.x > rightR) {
		cX = rightR;
	}
	else {
		cX = a.x;
	}

	//Find closest y offset
	if (a.y < topR) {
		cY = topR;
	}
	else if (a.y > bottomR) {
		cY = bottomR;
	}
	else {
		cY = a.y;
	}

	//If the closest point is inside the circle
	if (distanceSquared(a.x, a.y, cX, cY) < a.r * a.r) {
		//If the Dot is to the side of the Block
		if (cY == a.y) {
			//If velocity is positive
			if (mVelX > 0) {
				//Resolve the collision
				resolveHCollision(p);
				//Set Dot position to oustide p2
				mPosX = p->getRect().x - mCollider.r;
			}
			else {
				//Resolve the collision
				resolveHCollision(p);
				//Set Dot position to oustide p1
				mPosX = p->getRect().x + p->getRect().w + mCollider.r;
			}
			//Reverse horizontal velocity and increase total velocity
			mVelX = -mVelX;
			mVelX += 10 * (mVelX / abs(mVelX));
		}
		//Else if the Dot is above/below the Block
		else {
			//If Dot is closer to top of Block than bottom
			if ( abs(mPosY - p->getRect().y) < abs(mPosY - (p->getRect().y + p->getRect().h)) ) {
				//Set Dot position to oustide the Block
				mPosY = p->getRect().y - 4 * mCollider.r;
			}
			//If Dot is closer to bottom of Block than top
			else {
				//Set Dot position to oustide the Block
				mPosY = p->getRect().y + p->getRect().h + 3 * mCollider.r;
			}
			//Reverse vertical velocity
			mVelY = -mVelY;

			//Indicate that the Dot hit the top of the Block
			hitTopOfBlock = true;
		}

		//Have the collision sound play
		playCollisionSound = true;
	}
}

Circle& Dot::getCollider()
{
	return mCollider;
}

void Dot::shiftColliders()
{
	mCollider.x = mPosX;
	mCollider.y = mPosY;
}

double distanceSquared(double x1, double y1, double x2, double y2)
{
	return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
}

void Dot::setTime(float time)
{
	timeSinceReset = time;
}

float Dot::getTime()
{
	return timeSinceReset;
}

void Dot::resolveHCollision(Block* p)
{	
	//Get the time until the Dot would collide with the Block horizontally
	float timeTillCollision;
	if (mVelX > 0) {
		timeTillCollision = (p->getRect().x - mPosX - mCollider.r) / mVelX;
	}
	else {
		timeTillCollision = abs( (p->getRect().x + p->getRect().w - mPosX - mCollider.r) / mVelX );
	}

	//The variable that stores the y position of the collision
	double yPosCollision = mPosY + mVelY * timeTillCollision;

	//Adjust the y velocity of the Dot	
	mVelY = -2 * DOT_VEL * (p->getRect().y + p->getRect().h / 2 - yPosCollision) / (p->getRect().h / 2);
}
