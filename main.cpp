#include "Game.h"
#include "Audio.h"

Game *game = nullptr;

int main(int argc, char *argv[])
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	unsigned int frameStart;
	int frameTime;
	Audio a;

	game = new Game();
	game->init("GameWindow", 800, 640, false);

	while (game->running())
	{
		frameStart = SDL_GetTicks();

		
		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}

		if (!Mix_PlayingMusic())
		{
			a.playMusic();
		}
	}

	game->clean();
	return 0;
}