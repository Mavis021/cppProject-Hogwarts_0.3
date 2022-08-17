#include "Game.h"
#include "textureManager.h"
#include "GameObject.h"
#include "Map.h"
#include"ECS/Components.h"
#include "Vector2D.h"
#include"Collision.h"

Map* map;
Manager manager;
SDL_Renderer* Game::renderer = nullptr;            //we can reassign
SDL_Event Game::event;
std::vector<ColliderComponent*> Game::colliders;
int tempXball, tempYball;
bool startMapMovement = false;
bool ballMoving = false;
bool mapBegin = true;

SDL_Texture* Game:: StartEndTexture = nullptr;

SDL_Rect srcStartEnd = { 0, 0, 300,640 };
SDL_Rect destStartEnd = { 0, 0, 300,640 };//600=800-200 for xpos of dest rect


auto& Player(manager.addEntity());  //creating our player
auto& Enemy(manager.addEntity());   //creating our enemy
auto& ball(manager.addEntity());    //creating our magic ball

const char* mapfile = "gameLoop/dev/map_tile.png";

enum groupLables : std::size_t
{
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};


auto& tiles(manager.getGroup(groupMap));
auto& Players(manager.getGroup(groupPlayers));
auto& enimies(manager.getGroup(groupEnemies));
auto& balls(manager.getGroup(groupColliders));

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;
	
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0 , 0);
		}

		isRunning = true;
	}
	
		map = new Map();
		static int loop;
		
		for ( loop = 0; loop <2; loop++)
		{
			/*if(loop==0)
				map->LoadMap("gameLoop/dev/startEnd.map", 5, 10, loop);
			else*/
				map->LoadMap("gameLoop/dev/pixel_16x16.map", 25, 10, loop);
		}
	
	//player
	Player.addComponent<TransformComponent>(80,85,200,200,0.48);   //player component render
	Player.addComponent<SpriteComponent>("gameLoop/gfx/finalHarry.png",true);
	Player.addComponent<ColliderComponent>("Player");
	Player.addGroup(groupPlayers);

	//enemy
	Enemy.addComponent<TransformComponent>(447,447,200,200,0.48);   //enemy component render
	Enemy.addComponent<SpriteComponent>("gameLoop/gfx/deathEater200-200.png", true);
	Enemy.addComponent<ColliderComponent>("Enemy");
	Enemy.addGroup(groupEnemies);

	//magicBall
	ball.addComponent <TransformComponent>(150, 150, 200, 200, 0.16);
	ball.addComponent<SpriteComponent>("gameloop/gfx/powerball_200.png",true);
	ball.addComponent<KeyboardComtroller>();
	ball.addComponent<ColliderComponent>("ball");
	ball.addGroup(groupColliders);
}

void Game::handleEvents()
{
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT :
		isRunning = false;
		break;
	default:
		break;
	}
}


void Game::update()
{
	manager.refresh();
	manager.update();

	if(startMapMovement==true)
	updateCounter++;
	//backround moving 
	//Vector2D pVel = Player.getComponent<TransformComponent>().velocity;
	//int pSpeed = Player.getComponent<TransformComponent>().speed;

	 //const int BGspeed= -2;
	for (auto t : tiles)
	{
		if (startMapMovement == true)
		{
			t->getComponent<TileComponent>().destRect.x += -2;//-(pVel.x * pSpeed);
			if (t->getComponent<TileComponent>().destRect.x == 0)
			{
				mapBegin = true;
			}
		}

			if (Collision::hitCount >= 3)
			{
				Enemy.getComponent<SpriteComponent>().Play("Dead");
				break;
			}
			else if (updateCounter >= 1500)
			{
				Enemy.getComponent<TransformComponent>().velocity.x = 1;
				break;
			}
			else
				continue;
	}


	if (Collision::AABB(Enemy.getComponent<ColliderComponent>().collider,
		ball.getComponent<ColliderComponent>().collider))
	{
		ballMoving = false;

		if (Collision::hitCount == 1)
		{
			Enemy.getComponent<TransformComponent>().position.x = 467;
			Enemy.getComponent<TransformComponent>().position.y = 427;
		}
		else
		{
			Enemy.getComponent<TransformComponent>().position.x = 447;
			Enemy.getComponent<TransformComponent>().position.y = 447;
		}

		if (tempXball == 150 && tempYball == 150)
		{
			ball.getComponent<TransformComponent>().position.x = 130;
			ball.getComponent<TransformComponent>().position.y = 170;
			ball.getComponent<TransformComponent>().velocity.x = 0;
			ball.getComponent<TransformComponent>().velocity.y = 0;
		}
		else
		{
			ball.getComponent<TransformComponent>().position.x = tempXball;
			ball.getComponent<TransformComponent>().position.y = tempYball;
		}

		std::cout << "returning to initial position." << std::endl;
		
		//ball.destroy();
	}

	//std::cout << ball.getComponent < TransformComponent>().position.x << " , " << ball.getComponent < TransformComponent>().position.y << std::endl;

	//for (auto cc : colliders)
	//{
	//	Collision::AABB(Player.getComponent<ColliderComponent>(), *cc);
	//}
}


void Game::render()
{
	SDL_RenderClear(renderer);

	StartEndTexture =TextureManager::LoadTexture("gameLoop/deva/startForest.png");
	TextureManager::Draw(StartEndTexture, srcStartEnd, destStartEnd, SDL_FLIP_NONE);
	if (updateCounter >= 1200)
	{
		destStartEnd.x = 600;
		StartEndTexture = TextureManager::LoadTexture("gameLoop/gfx/endForest.png");
		TextureManager::Draw(StartEndTexture, srcStartEnd, destStartEnd, SDL_FLIP_NONE);
	}


	for (auto& t : tiles)
	{
		t->draw();
	}
	for (auto& p : Players)
	{
		p->draw();
	}
	for (auto& e : enimies)
	{
		e->draw();
	}

	//if (check)
	//{
		for (auto& b : balls)
		{
			b->draw();
		}
	//}
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Game::addTile(int srcX,int srcY, int xpos, int ypos)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX,srcY,xpos+300,ypos,mapfile);
	tile.addGroup(groupMap);
}

//single tile component system
//void Game::addTile(int id, int x, int y)
//{
//	auto& tile(manager.addEntity());
//	tile.addComponent<TileComponent>(x,y,64,64,id);
//	tile.addGroup(groupMap);
//}