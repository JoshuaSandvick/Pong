#include "GameState.h"


GameState::GameState()
{}


GameState::~GameState()
{}


void set_next_state(int newState)
{
	//If the user doesn't want to exit
	if (nextState != STATE_EXIT) {
		//Set the next state
		nextState = newState;
	}
}


void change_state()
{
	//If the state needs to be changed
	if (nextState != STATE_NULL)
	{
		//Delete the current state
		if (nextState != STATE_EXIT) {
			delete currentState;
		}
		//Change the state
		switch (nextState)
		{
		case STATE_TITLE:
			currentState = new Title();
			break;

		case STATE_INGAME:
			currentState = new InGame();
			break;
		}

		//Change the current state ID
		stateID = nextState;

		//NULL the next state ID
		nextState = STATE_NULL;
	}
}

//Initialize all of the external variables

//State variables
int stateID = STATE_NULL;
int nextState = STATE_NULL;

//Game state object
GameState* currentState = NULL;

//Event variable
SDL_Event event;

//The game score
int p1Score, p2Score;

//The boolean that determines if the collision sound will be played
bool playCollisionSound;

//Determines if a dot currently exists
bool dotExists;
