#pragma once

#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "SDL.h"

class TileComponent: public Component
{
public:

	//coordinate system
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	Vector2D position;

	TileComponent() = default;
	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}

	TileComponent(int srcX, int srcY, int xpos, int ypos, const char* path)
	{
		texture = TextureManager::LoadTexture(path);

		position.x = xpos;
		position.y = ypos;

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = 64;

		destRect.x = xpos;
		destRect.y = ypos;
		destRect.w = destRect.h = 64;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}

};

//single tile system
// 	TransformComponent* transform;
//SpriteComponent* sprite;
//
//SDL_Rect tileRect;
//int tileID;
//const char* path;
//
//TileComponent() = default;

//TileComponent(int x, int y, int w, int h, int id)
//{
//	tileRect.x = x;
//	tileRect.y = y;
//	tileRect.w = w;
//	tileRect.h = h;
//	tileID = id;
//
//	switch (tileID)
//	{
//	case 0:
//		path = "gameLoop/dev/dirt.png";
//		break;
//	case 1:
//		path = "gameLoop/dev/water.png";
//		break;
//	case 2:
//		path = "gameLoop/dev/white.png";
//		break;
//	default:
//		break;
//	}
//}
//
//void init() override
//{
//	entity->addComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y, (float)tileRect.w, (float)tileRect.h, 1);
//	transform = &entity->getComponent<TransformComponent>();
//
//	entity->addComponent<SpriteComponent>(path);
//	sprite = &entity->getComponent<SpriteComponent>();
//}