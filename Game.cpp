#include "Game.h"
#include "textureManager.h"
#include "GameObject.h"
#include "Map.h"
#include"ECS/Components.h"
#include "Vector2D.h"
#include"Collision.h"

Map* map;
Manager manager;
int hit;
SDL_Renderer* Game::renderer = nullptr;            //we can reassign
SDL_Event Game::event;
std::vector<ColliderComponent*> Game::colliders;


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
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}
	
		map = new Map();

		for (int i = 0; i < 3; i++)
		{
			map->LoadMap("gameLoop/dev/pixel_16x16.map", 25, 10, i);
		}
	
	//player
	Player.addComponent<TransformComponent>(100,100,32,32,2);   //player component render
	Player.addComponent<SpriteComponent>("gameLoop/gfx/harryfly1-4.png",true);
	Player.addComponent<ColliderComponent>("Player");
	Player.addGroup(groupPlayers);

	//enemy
	Enemy.addComponent<TransformComponent>(447,447,32,32,3);   //enemy component render
	Enemy.addComponent<SpriteComponent>("gameLoop/gfx/deathEater2-4.png", true);
	Enemy.addComponent<ColliderComponent>("Enemy");
	Enemy.addGroup(groupEnemies);

	//magicBall
	ball.addComponent <TransformComponent>(150, 150, 32, 32, 1);
	ball.addComponent<SpriteComponent>("gameloop/gfx/magicBall32.png",true);
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
	//backround moving 
	Vector2D pVel = Player.getComponent<TransformComponent>().velocity;
	int pSpeed = Player.getComponent<TransformComponent>().speed;

	for (auto t : tiles)
	{

			t->getComponent<TileComponent>().destRect.x += -2;//-(pVel.x * pSpeed);
			if (Collision::hitCount >= 3)
			{
				break;
			}
		
		//t->getComponent<TileComponent>().destRect.y += -1;//-()
	}

	if (Collision::AABB(Enemy.getComponent<ColliderComponent>().collider,
		ball.getComponent<ColliderComponent>().collider))
	{
		ball.getComponent<TransformComponent>().position.x = 150;
		ball.getComponent<TransformComponent>().position.y = 150;

		std::cout << "magic ball le lagyo enemy lai." << std::endl;
		
		//ball.destroy();
	}

	std::cout << ball.getComponent < TransformComponent>().position.x << " , " << ball.getComponent < TransformComponent>().position.y << std::endl;

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