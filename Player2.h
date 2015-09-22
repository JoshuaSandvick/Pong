#pragma once
#include "Block.h"
#include "globals.h"
#include "LTimer.h"


class Player2 :
	public Block
{
public:
	Player2(int x, int y, int w, int h);
	Player2();
	~Player2();

	//Timer for the player
	LTimer playerTimer;
};
