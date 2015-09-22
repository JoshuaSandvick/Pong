#pragma once
#include "Block.h"
#include "LTimer.h"

class Player1 :
	public Block
{
public:
	Player1(int x, int y, int w, int h);
	Player1();
	~Player1();

	//Adjusts computer velocity to move to dot
	void adjustVelForDot(int dotY);

	//Timer for the computer
	LTimer computerTimer;
};

