#include "GameObject.h"
#include "textureManager.h"

GameObject::GameObject(const char* texturesheet,int x, int y)
{
	xpos = x;
	ypos = y;
	objTexture = TextureManager::LoadTexture(texturesheet);
}

void GameObject::Update()
{
	xpos++;
	ypos++;

	scrRect.h = 32;
	scrRect.w = 32;
	scrRect.x = 0;
	scrRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = scrRect.w * 2;
	destRect.h = scrRect.h * 2;

}

void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer,objTexture, &scrRect, &destRect);
}