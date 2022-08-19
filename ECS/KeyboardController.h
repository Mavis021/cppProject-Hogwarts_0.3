#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Map.h"
#include "Components.h"
#include "collision.h"

//#include <sstream>
class KeyboardController : public Component
{
//private:
//	std::stringstream sst;
public:
	int tempXBall, tempYBall;
	TransformComponent* transform;
	SpriteComponent* sprite;
	//UILabel* text;

	int pressCount=0;
	
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
		//text = &entity->getComponent<UILabel>();
	}

	void update() override
	{
		if(Game::isComplete == false)
		{
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_RETURN:
				Map::startMapMovement = true;
				break;
			case SDLK_k:
			{
				if (Map::startMapMovement == true )//&& mapBegin == true)
				{
					Game::ballMoving = true;
					if (transform->velocity.x == 0 && transform->velocity.x == 0)
					{tempXBall = transform->position.x;
						tempYBall = transform->position.y;
					}
					transform->velocity.y = 1;
					transform->velocity.x = 1;

						sprite->Play("Move");
						break;
					}
				}
				case SDLK_a:
				{
					if (Map::startMapMovement == true && Game::ballMoving == false)
					{
						pressCount++;

						if (pressCount % 3 == 0)
						{
							transform->position.x = 170;
							transform->position.y = 130;
						}
						else if (pressCount % 3 == 1)
						{
							transform->position.x = 150;
							transform->position.y = 150;
						}
						else
						{
							transform->position.x = 130;
							transform->position.y = 170;
						}

						sprite->Play("Idle");
						break;
					}
				}
				default:
					break;
				}
			}
			if (Game::event.type == SDL_KEYUP)
			{
				switch (Game::event.key.keysym.sym)
				{
				case SDLK_RETURN:
					Map::startMapMovement = true;
					if (transform->position.x == tempXBall + 3 && transform->position.y == tempYBall + 3)
					{
						transform->velocity.y = 0;
						transform->velocity.x = 0;
						pressCount = 0;
						sprite->Play("Idle");
					}
					break;
					break;
				case SDLK_k:
				{
					if (Map::startMapMovement == true)
					{
						if (transform->position.x == tempXBall + 3 && transform->position.y == tempYBall + 3)
						{
							transform->velocity.y = 0;
							transform->velocity.x = 0;
							pressCount = 0;
							sprite->Play("Idle");
						}
						break;
					}
				}
				case SDLK_a:
				{

					if (Map::startMapMovement == true && Game::ballMoving == false)
					{
						transform->velocity.y = 0;
						transform->velocity.x = 0;
						sprite->Play("Idle");
						break;
					}
				}
				default:
					break;

				}
			}
		}
	}

};