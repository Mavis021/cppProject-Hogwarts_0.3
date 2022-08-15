#pragma once
#include "SDL.h"


class ColliderComponent;

class Collision
{

public:
	static int hitCount;
	static bool AABB(const SDL_Rect& rectA,const SDL_Rect& rectB);//axis aligned bounding box
	static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);
};