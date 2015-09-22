#include "LTexture.h"
#include <SDL.h>
#include "globals.h"

#pragma once

class Block
{
public:
	Block(int x, int y, int w, int h);
	Block();

	~Block();

	//Gets the Block's Rect
	SDL_Rect getRect();

	//Sets the Block's dimensions
	void setDim(int x, int y, int w, int h);

	//Set's the coordinates and dimensions of bRect
	void shiftColliders();

	//Moves the player block
	void move(double timeForMovement);

	//Checks for top and bottom collision
	void checkCollision();

	//Handles keyboard events
	void handleEvents(SDL_Event& e);

	//Render the Block
	void render();

	//The texture for the block
	LTexture bTexture;

private:
	//The SDL_Rect that the players will control
	SDL_Rect bCollider;

protected:
	//Position of the Block
	float bPosX, bPosY;

	//Velocity of the Block
	int bVelY = 0;

	//Speed of Block
	const int BLOCK_VELOCITY = 300;

	//Dimensions of Block
	int bWidth, bHeight;
};

