#include "Game.h"
#include "Menu.h"

Game* game = nullptr;

int main(int argc, char* argv[]) {
	/*
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;
	*/
	
	game = new Game();
	game->Start("Frog Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1027, 768);

	while (game->running())
	{
		//frameStart = SDL_GetTicks(); // SDL_GetTicks() is a function in the SDL library that returns the number of milliseconds since the SDL library was initialized. 
		//As soon as the program starts the SDL_Init, SDL keeps a counter this Ticks in milliseconds how much time has passed since that SDL_Init is called. 
		//SDL_GetTicks() returns the number of milliseconds since the SDL_Init was started. 
		//SDL_GetTicks() gets the amount of time passed since the SDL_Init was called.

		game->HandleEvents();
		game->update();
		game->render();

	    /*
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}*/
	
	}

	game->clean();

	return 0;
}