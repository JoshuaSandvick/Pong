#pragma once

#include <SDL.h>
#include "Block.h"
#include "LTexture.h"
#include "SoundHandler.h"
#include "Player1.h"
#include "Player2.h"
#include "Dot.h"


//Game states
enum GameStates
{
	STATE_NULL,
	STATE_TITLE,
	STATE_INGAME,
	STATE_EXIT,
};


//Game state base class (virtual so that sub-class overloaded methods can be called)
class GameState
{
public:
	GameState();
	virtual ~GameState();

	//Handles keyboard events
	virtual void handle_events() = 0;

	//Handles the game logic of a state
	virtual void logic() = 0;

	//Renders the images of the state
	virtual void render() = 0;
};

//State status manager
void set_next_state(int newState);

//State changer
void change_state();

//State variables
extern int stateID;
extern int nextState;

//Game state object
extern GameState* currentState;

//Event variable
extern SDL_Event event;


class InGame : public GameState
{
public:
	//Loads game resources
	InGame();
	//Frees game resources
	~InGame();

	//Main loop functions
	void handle_events();
	void logic();
	void render();

private:
	//Level dimensions
	const static int LEVEL_WIDTH = 640;
	const static int LEVEL_HEIGHT = 480;
	
	//Game background
	LTexture gBackground;

	//The score texture
	LTexture scoreTexture;

	//The Blocks
	Player1* p1;
	Player2* p2;

	//The Dot
	Dot* dot;

	//The handler for collision sound
	SoundHandler collisionSound;

	//Sets Dot as a friend class to access the score and collision variables
	friend class Dot;
};
//The game score
extern int p1Score, p2Score;

//The boolean that determines if the collision sound will be played
extern bool playCollisionSound;


class Title : public GameState
{
public:
	//Loads intro resources
	Title();
	//Frees intro resources
	~Title();

	//Main loop functions
	void handle_events();
	void logic();
	void render();

private:
	//Screen dimensions
	const static int SCREEN_WIDTH = 640;
	const static int SCREEN_HEIGHT = 480;

	//Intro background
	LTexture iBackground;

	//Intro message
	LTexture messageTexture;

	//Lambda symbol
	LTexture lambdaTexture;

	//Enter message
	LTexture enterTexture;
};
