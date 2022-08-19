#pragma once

#include "SDL.h"
#include"SDL_image.h"
#include "Audio.h"
#include <iostream>
#include "vector"

class ColliderComponent;

class Game
{
public:
	Game();
	~Game();

	bool check = true;
	void init(const char* title, int width, int height, bool fullscreen);

	
	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();

	//static AssetManager* assets;
	//static SDL_Texture* StartEndTexture;
	static bool isComplete;
	static int updateCounter;
	static bool ballMoving;
	static void addTile(int srcX,int srcY, int xpos, int yos);
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static std::vector<ColliderComponent*>colliders;

private:
	bool isRunning = false;
	int cnt = 0;
	SDL_Window *window;
};