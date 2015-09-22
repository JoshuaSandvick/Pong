#include "GameState.h"
#include <iostream>
#include <string>
#include <time.h>


InGame::InGame()
{
	//Set the dimensions of the player blocks
	p1 = new Player1(20, 20, 25, 100);
	p2 = new Player2(LEVEL_WIDTH - 45, LEVEL_HEIGHT - 120, 25, 100);
	
	/*Initialize the dot*/
	//Seed the random number generator
	srand(time(NULL));
	dot = new Dot(LEVEL_WIDTH / 2, rand() % (LEVEL_HEIGHT - DOT_HEIGHT + 1));
	dotExists = true;

	//Initialize the scores to 0
	p1Score = p2Score = 0;

	//Load game background texture
	if (!gBackground.loadFromFile("Images/GameBackground.png")) {
		std::cout << "Unable to load GameBackground.png!" << std::endl;
	}

	//Load initial score texture
	if (!scoreTexture.loadFromRenderedText("Player 1: " + std::to_string(0) + "  Player 2: " + std::to_string(0), { 0, 0, 0, 255 })) {
		std::cout << "Unable to load score text!" << std::endl;
	}

	//Load dot texture
	if (!dot->dotTexture.loadFromFile("Images/dot.png")) {
		std::cout << "Unable to load dot.png!" << std::endl;
	}

	//Load block textures
	if (!p1->bTexture.loadFromFile("Images/Block.png")) {
		std::cout << "Unable to load Block.png!" << std::endl;
	}

	//Load block textures
	if (!p2->bTexture.loadFromFile("Images/Block.png")) {
		std::cout << "Unable to load Block.png!" << std::endl;
	}

	//Load sound file
	collisionSound.setSound(false, "dotCollision.wav");

	//Start the timers
	p1->computerTimer.start();
	p2->playerTimer.start();
	dot->dotTimer.start();

}


InGame::~InGame()
{
	//Free the textures
	gBackground.~LTexture();
	scoreTexture.~LTexture();
	delete dot;
	dot = NULL;

	//Free the sound file
	collisionSound.~SoundHandler();

	//Delete the players and their textures
	delete p1;
	delete p2;
}


void InGame::handle_events()
{
	//While there's events to handle
	while (SDL_PollEvent(&event)) {
		//Handle events for the player block
		p2->handleEvents(event);
		//If the user has Xed out the window
		if (event.type == SDL_QUIT) {
			//Quit the program
			set_next_state(STATE_EXIT);
		}
	}
}

void InGame::logic()
{
	//Reset the collision sound bool each frame
	playCollisionSound = false;

	//Move the computer
	p1->adjustVelForDot(dot->getCollider().y);
	p1->move(p1->computerTimer.getTicks() / 1000.f);

	//Reset the computer timer
	p1->computerTimer.start();

	//Move the player
	p2->move(p2->playerTimer.getTicks() / 1000.f);

	//Reset the timer
	p2->playerTimer.start();

	//Move the dot and set the dot time variable
	dot->setTime(dot->dotTimer.getTicks() / 1000.f);
	dot->move(dot->getTime(), p1, p2);

	//Reset the timer
	dot->dotTimer.start();

	//If the score is greater than 3
	if (p1Score > 3 || p2Score > 3) {
		set_next_state(STATE_TITLE);
	}
}

void InGame::render()
{
	//Clear screen
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);

	//Render blocks
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);

	//Render the players
	p1->render();
	p2->render();


	//If dot exists
	if (dotExists) {
		//Render objects
		dot->render();
	}
	else {
		//Change and render the score, create new dot, render it, and tell the program that a dot exists
		std::string scoreText = "Player 1: " + std::to_string(p1Score) + "  Player 2: " + std::to_string(p2Score);

		SDL_Color textColor = { 0, 0, 0, 255 };
		if (!scoreTexture.loadFromRenderedText(scoreText, textColor)) {
			printf("Unable to render score texture!\n");
		}

		delete dot;
		dot = NULL;
		if (!(p1Score > 3) && !(p2Score > 3)) {
			dot = new Dot(LEVEL_WIDTH / 2, rand() % (LEVEL_HEIGHT - DOT_HEIGHT + 1));
			//Load dot texture
			if (!dot->dotTexture.loadFromFile("Images/dot.png")) {
				std::cout << "Unable to load dot.png!" << std::endl;
			}
			dotExists = true;
			dot->render();
		}
	}

	//Render the score
	scoreTexture.render(LEVEL_WIDTH / 2 - scoreTexture.getWidth() / 2, 10);

	//If a Player has won
	if (p1Score > 3) {
		//Load and render the win message to the screen
		LTexture winMessage;
		winMessage.loadFromFile("Images/Player1WinMessage.png");
		winMessage.render(LEVEL_WIDTH / 2 - winMessage.getWidth() / 2, LEVEL_HEIGHT / 2 - winMessage.getHeight() / 2);

		//Update screen
		SDL_RenderPresent(gRenderer);

		//Delay the game to display the message and stop accepting events
		SDL_EventState(SDL_KEYDOWN, SDL_IGNORE);
		SDL_Delay(5 * 1000);
		SDL_EventState(SDL_KEYDOWN, SDL_ENABLE);
	}
	else if (p2Score > 3) {
		//Load and render the win message to the screen
		LTexture winMessage;
		winMessage.loadFromFile("Images/Player2WinMessage.png");
		winMessage.render(LEVEL_WIDTH / 2 - winMessage.getWidth() / 2, LEVEL_HEIGHT / 2 - winMessage.getHeight() / 2);

		//Update screen
		SDL_RenderPresent(gRenderer);

		//Delay the game to display the message
		SDL_Delay(5 * 1000);
	}
	//If no one won
	else {
		//Update screen
		SDL_RenderPresent(gRenderer);
	}

	//If the collision sound should play
	if (playCollisionSound) {
		//Play the collision sound
		collisionSound.playSound();
	}
}
