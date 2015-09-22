#include "Block.h"

Block::Block(int x, int y, int w, int h)
{
	bPosX = x;
	bCollider.x = x;
	bPosY = y;
	
	bWidth = bCollider.w = w;
	bHeight = bCollider.h = h;

	shiftColliders();
}

Block::Block()
{}


Block::~Block()
{
	//delete bTexture;
	bTexture.~LTexture();
}


SDL_Rect Block::getRect()
{
	return bCollider;
}


void Block::setDim(int x, int y, int w, int h)
{
	bPosX = x;
	bCollider.x = x;
	bPosY = y;

	bWidth = bCollider.w = w;
	bHeight = bCollider.h = h;

	shiftColliders();
}


void Block::shiftColliders()
{
	bCollider.y = bPosY;
}


void Block::handleEvents(SDL_Event& e)
{
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_DOWN:
			bVelY += BLOCK_VELOCITY;
			break;

		case SDLK_UP:
			bVelY -= BLOCK_VELOCITY;
			break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_DOWN:
			bVelY -= BLOCK_VELOCITY;
			break; 
		
		case SDLK_UP:
			bVelY += BLOCK_VELOCITY;
			break;
		}
	}
}


void Block::checkCollision()
{
	//If the block goes off of the top of the screen
	if (bCollider.y < 0) {
		//Put the block back at the top of the screen and set its velocity to 0
		bPosY = 0;
		shiftColliders();
	}
	//If the block goes off of the bottom of the screen
	if (bCollider.y + bCollider.h > SCREEN_HEIGHT) {
		//Put the block back at the bottom of the screen and set its velocity to 0
		bPosY = SCREEN_HEIGHT - bCollider.h;
		shiftColliders();
	}
}


void Block::move(double timeForMovement)
{
	//Move the dot up or down
	bPosY += bVelY * timeForMovement;

	//Shift the colliders
	shiftColliders();

	//Deal with collisions
	checkCollision();
}


void Block::render()
{
	bTexture.render((int)bPosX, (int)bPosY);
}
