#include "GameState.h"

#include <string>

Title::Title()
{
	iBackground.loadFromFile("Images/TitleBackground.png");
	messageTexture.loadFromFile("Images/Message.png");
	lambdaTexture.loadFromFile("Images/LambdaSymbol.png");
	enterTexture.loadFromFile("Images/EnterMessage.png");
}


Title::~Title()
{
	iBackground.free();
	messageTexture.free();
	lambdaTexture.free();
	enterTexture.free();
}


void Title::handle_events()
{
	//While there is events to handle
	while (SDL_PollEvent(&event)) {
		//If the user has Xed out the window
		if (event.type == SDL_QUIT) {
			set_next_state(STATE_EXIT);
		}
		//If the user pressed enter
		else if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_RETURN)) {
			//Go in to the game
			set_next_state(STATE_INGAME);
		}
	}
}


void Title::logic()
{}


void Title::render()
{
	//Clear screen
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(gRenderer);

	//Show the background
	iBackground.render(20, 20);

	//Show the lambda symbol
	lambdaTexture.render(SCREEN_WIDTH - 20 - lambdaTexture.getWidth(), SCREEN_HEIGHT - 20 - lambdaTexture.getHeight());

	//Show the message
	messageTexture.render(SCREEN_WIDTH / 2 - iBackground.getWidth() / 2, SCREEN_HEIGHT / 2 - iBackground.getHeight() / 2);

	//Show the enter message
	enterTexture.render(20, 220);

	//Render to the screen
	SDL_RenderPresent(gRenderer);
}
