#pragma once
#include "SDL.h"
#include"SDL_image.h"
#include <iostream>
#include <vector>
#include "Game.h"

class Help
{
public:
    Help();
    ~Help();
    void helpInit(const char* title, int width, int height, bool fullscreen);
    void helpHandleEvents();
    //void helpUpdate();
    bool helpRunning()
    {
        return ishelpRunning;
    }
    void helpRender();
    void helpClean();
    //static SDL_Renderer* dashRenderer;
    static SDL_Event helpEvent;
    static SDL_Texture* helpTexture;
    //static SDL_Texture* mouseTexture;
    static SDL_Renderer* helpRenderer;
    bool ishelpRunning = false;

protected:
    SDL_Window* helpWindow;
};
