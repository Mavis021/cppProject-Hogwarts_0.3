#include "Game.h"
#include "textureManager.h"
#include "GameObject.h"
#include "Map.h"
#include"ECS/Components.h"
#include "Vector2D.h"
#include"Collision.h"
#include <sstream>

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;            //we can reassign
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

bool Game::isComplete = false;
//int Collision::hitCount = 0;
int Game::updateCounter = 0;
bool Map::startMapMovement = false;
bool Game::ballMoving = false;

//SDL_Texture* Game:: StartEndTexture = nullptr;
//
//SDL_Rect srcStartEnd = { 0, 0, 300,640 };
//SDL_Rect destStartEnd = { 0, 0, 300,640 };//600=800-200 for xpos of dest rect


auto& Player(manager.addEntity());  //creating our player
auto& Enemy(manager.addEntity());   //creating our enemy
auto& ball(manager.addEntity());    //creating our magic ball
auto& label(manager.addEntity());   //THE TEXT LABELS

const char* mapfile = "gameLoop/dev/finalMapTile64.png";

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
	
	if (TTF_Init() == -1)
	{
		std::cout << "Error : SDL_TTF" << std::endl;
	}

	//reassets->AddTexture("Player", "gameLoop/gfx/finalHarry.png");


		map = new Map();
		static int loop;
		
		for ( loop = 0; loop <4; loop++)
		{
			if(loop==0||loop==3)
				map->LoadMap("gameLoop/dev/startEnd.map", 5, 10, loop);
			else
				map->LoadMap("gameLoop/dev/finalMap64.map", 25, 10, loop);
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

	label.addComponent<UILabel>(250, 250, "PRESS ENTER TO START ", "gameLoop/dev/8514oem.fon", 16);
	//label.addComponent<KeyboardComtroller>();

	//magicBall
	ball.addComponent <TransformComponent>(150, 150, 200, 200, 0.16);
	ball.addComponent<SpriteComponent>("gameloop/gfx/powerball_200.png",true);
	ball.addComponent<KeyboardController>();
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
{/*
	Vector2D pVel = Enemy.getComponent<TransformComponent>().velocity;
	std::stringstream sst;
	sst << "Player velocity: " << pVel;
	label.getComponent<UILabel>().SetLabelText(sst.str(), "gameLoop/dev/8514oem.fon",16);*/

	manager.refresh();
	manager.update();

	if (Map::startMapMovement == true)
	{
		for (static bool runOnce = true; runOnce; runOnce = false)
		{
			label.getComponent<UILabel>().position.x = 450;
			label.getComponent<UILabel>().position.y = 50;
			label.getComponent<UILabel>().SetLabelText("PRESS 'K' TO KILL AND 'A' TO AIM", "gameLoop/dev/8514oem.fon", 16);
		}
		updateCounter++;
	}
	 //const int BGspeed= -2;
	for (auto t : tiles)
	{
		if (Map::startMapMovement == true)
		{
			t->getComponent<TileComponent>().destRect.x += -2;//-(pVel.x * pSpeed);
			//if (t->getComponent<TileComponent>().destRect.x == 0)
			//{
			//	mapBegin = true;
			//}
			
		}

			if (Collision::hitCount >= 3)
			{
				Enemy.getComponent<SpriteComponent>().Play("Dead");
				break;
			}
			else if (updateCounter >= 1500)
			{
				Game::isComplete = true;
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
		for (bool runOnce = true; runOnce; runOnce = false)
		{
			label.getComponent<UILabel>().position.x = 500;
		}

		std::stringstream sst;
		sst << "TOTAL HIT REQUIRED:" <<3- Collision::hitCount;
		label.getComponent<UILabel>().SetLabelText(sst.str(), "gameLoop/dev/8514oem.fon", 16);
			ball.getComponent<TransformComponent>().position.x = ball.getComponent<KeyboardController>().tempXBall;
			ball.getComponent<TransformComponent>().position.y = ball.getComponent<KeyboardController>().tempYBall;

		std::cout << "returning to initial position." << std::endl;
		
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

		for (auto& b : balls)
		{
			b->draw();
		}

		label.draw();
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
	tile.addComponent<TileComponent>(srcX,srcY,xpos,ypos,mapfile);
	tile.addGroup(groupMap);
}

//single tile component system
//void Game::addTile(int id, int x, int y)
//{
//	auto& tile(manager.addEntity());
//	tile.addComponent<TileComponent>(x,y,64,64,id);
//	tile.addGroup(groupMap);
//}