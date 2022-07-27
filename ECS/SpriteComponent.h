#pragma once

#include"Components.h"
#include"SDL.h"
#include"../textureManager.h"

class SpriteComponent : public Component
{
private:
	TransformComponent* Transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
public:
	SpriteComponent() = default;

	SpriteComponent(const char* path)
	{
		setText(path);
	}
	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}
	void setText(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}

	void init() override
	{
		Transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = Transform->width;
		srcRect.h = Transform->height;
	}
	void update() override
	{
		destRect.x = static_cast<int>(Transform->position.x);
		destRect.y = static_cast<int>(Transform->position.y);
		destRect.w = Transform->width * Transform->scale;
		destRect.h = Transform->height * Transform->scale;
	}

	void draw()override
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}
};