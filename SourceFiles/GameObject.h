#pragma once

#include "Game.h"

class GameObject
{
private:
	int xpos;
	int ypos;
	int height;
	int width;

	SDL_Texture* objTexture;
	SDL_Rect scrRect, destRect;

public:

	GameObject(const char* texturesheet,int x,int y,int h,int w);
		~GameObject()
		{}

	void Update();
	void Render();
	void clear();
};