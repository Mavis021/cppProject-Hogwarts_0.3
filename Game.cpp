#include "Game.h"
#include "textureManager.h"
#include "GameObject.h"
#include "Map.h"
#include"ECS/Components.h"
#include "Vector2D.h"
#include"Collision.h"

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

auto& Player(manager.addEntity());
auto& wall(manager.addEntity());

enum groupLables : std::size_t
{
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};

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

	Map::LoadMap("dev/pixel_16x16.map", 16, 16);

	Player.addComponent<TransformComponent>(3);   //player component render
	Player.addComponent<SpriteComponent>("dev/player_anims.png",true);
	Player.addComponent<KeyboardComtroller>();
	Player.addComponent<ColliderComponent>("Player");

	Player.addGroup(groupPlayers);

	//wall.addComponent <TransformComponent>(100.0f, 300.0f, 300, 20, 1);
	//wall.addComponent<SpriteComponent>("dev/water.png");
	//wall.addComponent<ColliderComponent>("Wall");
	//wall.addGroup(groupMap);
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

	//if (Collision::AABB(Player.getComponent<ColliderComponent>().collider,
	//	wall.getComponent<ColliderComponent>().collider))
	//{
	//	Player.getComponent<TransformComponent>().scale = 1;
	//	Player.getComponent<TransformComponent>().velocity * -1;
	//	std::cout << "wall hit!" << std::endl;
	//}
	std::cout << Player.getComponent < TransformComponent>().position.x << " , " << Player.getComponent < TransformComponent>().position.y << std::endl;

	//for (auto cc : colliders)
	//{
	//	Collision::AABB(Player.getComponent<ColliderComponent>(), *cc);
	//}
}

auto& tiles(manager.getGroup(groupMap));
auto& Players(manager.getGroup(groupPlayers));
auto& enimies(manager.getGroup(groupEnemies));

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

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Game::addTile(int id, int x, int y)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x,y,32,32,id);
	tile.addGroup(groupMap);
}