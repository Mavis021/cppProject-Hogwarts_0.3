#include "dashboard.h"
#include"textureManager.h"
#include"Button.h"
#include<cstdlib>


SDL_Event Dashboard::dashEvent;
SDL_Texture* Dashboard::dashTexture = nullptr;
SDL_Rect srcRect = { 0, 0, 800, 640 };
SDL_Rect destRect = { 0, 0, 800, 640 };

SDL_Texture* Dashboard::mouseTexture = nullptr;
SDL_Rect srcmouse = { NULL,NULL,64,64 };
SDL_Rect destmouse = { NULL,NULL,32,32};
Button* buttonArray;

Dashboard::Dashboard()
{}
Dashboard::~Dashboard()
{}
void Dashboard::dashInit(const char* title, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        dashWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
        Game::renderer = SDL_CreateRenderer(dashWindow, -1, 0);
        if (Game::renderer)
        {
            SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 0);
        }
        isDashRunning = true;
    }


    SDL_ShowCursor(false);
    buttonArray = new Button[6];
    buttonArray[0] = Button("gameLoop/gfx/buttonPlay.png", 30, 30, 200, 50);
    buttonArray[1] = Button("gameLoop/gfx/buttonQuit.png", 30, 110, 200, 50);
    buttonArray[2] = Button("gameLoop/gfx/buttonHelp.png", 30, 190, 200, 50);
    for (int i = 0; i < 3; i++)
    {
        buttonArray[i].isSelected = false; // all blue buttons
    }
    buttonArray[3] = Button("gameLoop/gfx/buttonPlay2.png", 30, 30, 200, 50);
    buttonArray[4] = Button("gameLoop/gfx/buttonQuit2.png", 30, 110, 200, 50);
    buttonArray[5] = Button("gameLoop/gfx/buttonHelp2.png", 30, 190, 200, 50);
}

void Dashboard::dashHandleEvents()
{
    SDL_PollEvent(&dashEvent);
    for (int i = 0; i < 3; i++)
    {
        buttonArray[i].handleEvents();
    }
}
void Dashboard::dashUpdate()
{
    SDL_GetMouseState(&destmouse.x, &destmouse.y);
}
void Dashboard::dashRender()
{
    SDL_RenderClear(Game::renderer);
    SDL_Surface* tempSurface = IMG_Load("gameLoop/dev/dashboard-min.png");
    dashTexture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    SDL_RenderCopyEx(Game::renderer, dashTexture, &srcRect, &destRect, NULL, NULL, SDL_FLIP_NONE);
    if (buttonArray[0].isSelected == false)
        buttonArray[0].displayButton();
    else
        buttonArray[3].displayButton();
    if (buttonArray[1].isSelected == false)
        buttonArray[1].displayButton();
    else
        buttonArray[4].displayButton();
    if (buttonArray[2].isSelected == false)
        buttonArray[2].displayButton();
    else
        buttonArray[5].displayButton();
    
    SDL_Surface* temp = IMG_Load("gameLoop/gfx/hand.png");
    mouseTexture = SDL_CreateTextureFromSurface(Game::renderer, temp);
    SDL_RenderCopyEx(Game::renderer, mouseTexture, &srcmouse, &destmouse, NULL, NULL, SDL_FLIP_NONE);

    SDL_RenderPresent(Game::renderer);
}

void Dashboard::dashClean()
{
    delete[] buttonArray;
    SDL_DestroyWindow(dashWindow);
    SDL_DestroyRenderer(Game::renderer);
    SDL_Quit();
}

