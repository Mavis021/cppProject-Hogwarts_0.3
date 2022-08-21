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
SDL_Event Game::event;
SDL_Renderer* Game::renderer = nullptr;
SDL_Texture* Game::winLoseTexture = nullptr;
SDL_Rect srcWinLose = { 0, 0, 400,300 };
SDL_Rect destWinLose = { 200, 180, 400,300 }; 

Mix_Music* Audio::backgroundMusic = nullptr;
Mix_Chunk* Audio::soundEffect = nullptr;
bool Game::isComplete = false;
int Game::updateCounter = 0;
bool Map::startMapMovement = false;
bool Game::ballMoving = false;
bool Game::isRunning = false;
bool Game::runOnce = true;

std::vector<ColliderComponent*> Game::colliders;
auto& Player(manager.addEntity());  //creating our player
auto& Enemy(manager.addEntity());   //creating our enemy
auto& ball(manager.addEntity());    //creating our magic ball
auto& label(manager.addEntity());   //THE TEXT LABELS
auto& Sound(manager.addEntity());   //the audio entity

const char* mapfile = "gameLoop/dev/finalMapTile64.png";

auto& tiles(manager.getGroup(Game::groupMap));
auto& Players(manager.getGroup(Game::groupPlayers));
auto& enemies(manager.getGroup(Game::groupEnemies));
auto& balls(manager.getGroup(Game::groupColliders));
auto& sounds(manager.getGroup(Game::groupSound));

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
	Sound.addComponent<Audio>("gameloop/effects/hedwigsTheme8-bit.mp3","gameloop/effects/gameClick.wav");

	if (TTF_Init() == -1)
	{
		std::cout << "Error : SDL_TTF" << std::endl;
	}


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

	label.addComponent<UILabel>(250, 250, "PRESS ENTER TO START", "gameLoop/dev/8514oem.fon", 16);
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
		clean();
		break;
	default:
		break;
	}
	switch (event.key.keysym.sym)
	{
	case SDLK_ESCAPE:
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

	if (Map::startMapMovement == true)
	{
		while(runOnce == true)
		{
			label.getComponent<UILabel>().position.x = 500;
			label.getComponent<UILabel>().position.y = 50;
			label.getComponent<UILabel>().SetLabelText("HITS REQUIRED:5", "gameLoop/dev/8514oem.fon", 16);
			runOnce = false;
		}
		updateCounter++;
	}
	for (auto t : tiles)
	{
		if (Map::startMapMovement == true)
		{
			t->getComponent<TileComponent>().destRect.x += -2;
		}

			if (Collision::hitCount >= 5)
			{
				Enemy.getComponent<SpriteComponent>().Play("Dead");
				break;
			}
			else if (updateCounter >= 1500)   //lose game
			{
				Game::isComplete = true;
				for (static bool runOnce = true; runOnce; runOnce = false)
				{
					Sound.getComponent<Audio>().playEffects("gameLoop/effects/enemyRunAway.wav");
					Sound.getComponent<Audio>().playEffects("gameLoop/effects/loseGame.wav");
				}
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
		
		if (Collision::hitCount % 2 ==0)
		{
			Enemy.getComponent<TransformComponent>().position.x = 447;
			Enemy.getComponent<TransformComponent>().position.y = 447;   
		}
		else
		{
			Enemy.getComponent<TransformComponent>().position.x = 467;
			Enemy.getComponent<TransformComponent>().position.y = 427;
		}

		std::stringstream sst;
		sst << "HITS REQUIRED:" <<5- Collision::hitCount;
		label.getComponent<UILabel>().SetLabelText(sst.str(), "gameLoop/dev/8514oem.fon", 16);
			ball.getComponent<TransformComponent>().position.x = ball.getComponent<KeyboardController>().tempXBall;
			ball.getComponent<TransformComponent>().position.y = ball.getComponent<KeyboardController>().tempYBall;

			if (Collision::hitCount == 5)
			{
				isComplete = true;

				ball.getComponent<TransformComponent>().velocity.x=0;
				ball.getComponent<TransformComponent>().velocity.y =0;
				Sound.getComponent<Audio>().playEffects("gameLoop/effects/gameLevelComplete.wav");
			}

		std::cout << "returning to initial position." << std::endl;
		
	}

	if (isComplete == true)
	{
		winLoseTexture = TextureManager::LoadTexture("gameLoop/dev/lose.png");
		TextureManager::Draw(winLoseTexture, srcWinLose, destWinLose, SDL_FLIP_NONE);
		while (runOnce == false)
		{
			Sound.getComponent<Audio>().freeMusic();
			label.getComponent<UILabel>().SetLabelText("", "gameLoop/dev/8514oem.fon", 16);
			Sound.addComponent<Audio>("gameLoop/effects/hedwigsTheme.mp3");
			runOnce = true;
		}
	}
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
	for (auto& e : enemies)
	{
		e->draw();
	}

	for (auto& b : balls)
	{
		b->draw();
	}

	label.draw();
	if (Collision::hitCount>=5)
	{
		winLoseTexture = TextureManager::LoadTexture("gameLoop/dev/winFinal.png");
		TextureManager::Draw(winLoseTexture, srcWinLose, destWinLose, SDL_FLIP_NONE);
	}
	if (updateCounter >= 1600 && Collision::hitCount<5)
	{
		winLoseTexture = TextureManager::LoadTexture("gameLoop/dev/loseFinal.png");
		TextureManager::Draw(winLoseTexture, srcWinLose, destWinLose, SDL_FLIP_NONE);
	}
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	Mix_FreeChunk(Audio::soundEffect);
	Mix_FreeMusic(Audio::backgroundMusic);

	Audio::soundEffect = NULL;
	Audio::backgroundMusic = NULL;

	Mix_Quit();
	SDL_Quit();
	
}

void Game::addTile(int srcX,int srcY, int xpos, int ypos)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX,srcY,xpos,ypos,mapfile);
	tile.addGroup(groupMap);
}