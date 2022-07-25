#pragma once
#include "SDL.h"

class Collision {

public:
	static bool AABB(const SDL_Rect& rectA,const SDL_Rect& rectB);//axis aligned bounding box
};