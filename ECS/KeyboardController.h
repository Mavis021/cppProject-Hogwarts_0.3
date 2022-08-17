#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"

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
			case SDLK_k:
				transform->velocity.y = 1;
				transform->velocity.x = 1;

				sprite->Play("move");
				break;
			case SDLK_a:
			{
			
					pressCount++;

					if (pressCount % 3 == 0)
					{
						transform->position.x = 170;
						transform->position.y = 130;
						//transform->velocity.x = 1;
						//transform->velocity.y = -1;
					}
					else if (pressCount % 3 == 1)
					{
						transform->position.x = 150;
						transform->position.y = 150;
						//transform->velocity.x = 1;
						//transform->velocity.y = -1;
					}
					else
					{
						transform->position.x = 130;
						transform->position.y = 170;
						//transform->velocity.x = -1;
						//transform->velocity.y = 1;
					}

				sprite->Play("move");
				/*sprite->spriteFlip = SDL_FLIP_HORIZONTAL*/;
				break;
			}
			//case SDLK_d:
			//	transform->velocity.x = 1;
			//	sprite->Play("move");
			//	break;
			//case SDLK_s:
			//	transform->velocity.y = 1;
			//	sprite->Play("move");
			//	break;
			default:
				break;
			}
		}
		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_k:
			{
				if (transform->position.x == 173 && transform->position.y == 133)
				{
					transform->velocity.y = 0;
					transform->velocity.x = 0;
					pressCount = 0;
					sprite->Play("move");
				}
				break;
			}
			case SDLK_a:
			{
				transform->velocity.y = 0;
				transform->velocity.x = 0;
				sprite->Play("Idle");
				//sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			}
			//case SDLK_d:
			//	transform->velocity.x = 0;
			//	sprite->Play("Idle");
			//	break;
			//case SDLK_s:
			//	transform->velocity.y = 0;
			//	sprite->Play("Idle");
			//	break;
			default:
				break;

			}
		}
	}
};