#include "GameObject.h"
#include "textureManager.h"

GameObject::GameObject(const char* texturesheet,int x, int y,int h, int w)
{
	xpos = x;
	ypos = y;
	height = h;
	width = w;
	objTexture = TextureManager::LoadTexture(texturesheet);
}

void GameObject::Update()
{
	xpos =0;
	ypos =0;

	scrRect.h = height;
	scrRect.w = width;
	scrRect.x = 0;
	scrRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = scrRect.w;
	destRect.h = scrRect.h;

}

void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer,objTexture, &scrRect, &destRect);
}

void GameObject::clear()
{
	SDL_DestroyTexture(objTexture);
}