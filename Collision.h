#pragma once
#include "SDL.h"
#include "Game.h"
#include "ECS/Components.h"
#include "ECS/ECS.h"
#include "ECS/UILabel.h"
#include "Audio.h"

class ColliderComponent;

class Collision    : public Component
{
public:
	static int hitCount;
	static bool AABB(const SDL_Rect& rectA,const SDL_Rect& rectB);//axis aligned bounding box
	static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);
};