#include "Player1.h"


Player1::Player1(int x, int y, int w, int h) : Block(x, y, w, h)
{}

Player1::Player1()
{}

Player1::~Player1()
{}


void Player1::adjustVelForDot(int dotY)
{
	//Set variables to determine if the velocity has already been adjusted in the same direction
	bool upVel = false;
	bool downVel = false;

	//If y-coord of Block is above the Dot's
	if (bPosY + bHeight / 2 < dotY && !downVel) {
		//If the block is stationary
		if (bVelY == 0) {
			bVelY += BLOCK_VELOCITY;
			downVel = true;
			upVel = false;
		}
		//If the block is moving downward
		else if (bVelY == -BLOCK_VELOCITY) {
			bVelY += 2 * BLOCK_VELOCITY;
			downVel = true;
			upVel = false;
		}
	}
	else if (bPosY + bHeight / 2 > dotY && !upVel) {
		//If the block is stationary
		if (bVelY == 0) {
			bVelY -= BLOCK_VELOCITY;
			upVel = true;
			downVel = false;
		}
		//If the block is moving downward
		else if (bVelY == BLOCK_VELOCITY) {
			bVelY -= 2 * BLOCK_VELOCITY;
			upVel = true;
			downVel = false;
		}
	}
}
