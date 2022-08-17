#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"


extern int tempXball, tempYball;
extern bool startMapMovement;
extern bool ballMoving;
extern bool mapBegin;

class KeyboardComtroller : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	int pressCount=0;
	
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override
	{
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_KP_ENTER:
				startMapMovement = true;
				break;
			case SDLK_k:
			{
				if (startMapMovement == true && mapBegin == true)
				{
					ballMoving = true;
					if (transform->velocity.x == 0 && transform->velocity.x == 0)
					{
						tempXball = transform->position.x;
						tempYball = transform->position.y;
					}
					transform->velocity.y = 1;
					transform->velocity.x = 1;

					sprite->Play("Move");
					break;
				}
			}
			case SDLK_a:
			{
				if (startMapMovement == true && ballMoving == false)
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
			case SDLK_KP_ENTER:
				startMapMovement = true;
				break;
			case SDLK_k:
			{
				if (startMapMovement == true)
				{
					if (transform->position.x == tempXball+3 && transform->position.y == tempYball+3)
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

				if (startMapMovement == true&& ballMoving == false)
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
};