#pragma once

#include"Components.h"
#include"SDL.h"
#include"../textureManager.h"
#include "animation.h"
#include <map>

class SpriteComponent : public Component
{
private:
	TransformComponent* Transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 0;
	int speed = 50; //delay

public:

	int animIndex = 0;
	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;


	SpriteComponent() = default;

	SpriteComponent(const char* path)
	{
		setText(path);
	}
	SpriteComponent(const char* path,bool isAnimated)
	{
		animated = isAnimated;

		Animation idle = Animation(0, 4, 100);
		Animation move = Animation(1, 4, 100);
		Animation dead = Animation(2, 4, 100);

		animations.emplace("Idle", idle);
		animations.emplace("Move", move);
		animations.emplace("Dead", dead);

		Play("Idle");
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

		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}
			srcRect.y = animIndex * Transform->height;

		destRect.x = static_cast<int>(Transform->position.x);
		destRect.y = static_cast<int>(Transform->position.y);
		destRect.w = Transform->width * Transform->scale;
		destRect.h = Transform->height * Transform->scale;
	}

	void draw()override
	{
		TextureManager::Draw(texture, srcRect, destRect,spriteFlip);
	}

	void Play(const char* animName)
	{
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}
};