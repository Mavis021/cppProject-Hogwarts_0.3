#include "Collision.h"
#include "ECS\ColliderComponent.h"

int Collision::hitCount = 0;
bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB)
{
	if (
		//recA.x + recA.w >= recB.x &&
		//recA.x + recB.w >= recA.x &&
		//recA.y + recA.h >= recB.y &&
		//recB.y + recB.h >= recA.y
	recB.x >= recA.x +15 &&
		 recB.y >= recA.y +15
		)
	{
		if (recB.x == recA.x + 15 &&
			recB.y == recA.y + 15)
		{
			Audio a;
			hitCount++;
			if(hitCount != 3)
			a.playEffects("gameLoop/effects/ouch.wav");

			std::cout << "ball hit enemy" << std::endl;
		}
		else
		std::cout << "ball le hit bhaena" << std::endl;
		return true;
	}
	return false;
}
bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB)
{
	if (AABB(colA.collider, colB.collider))
	{
		std::cout << colA.tag << "hit: " << colB.tag << std::endl;
		return true;
	}
	else
		return false;
 }

