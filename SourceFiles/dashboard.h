#pragma once

#include "SDL.h"
#include"SDL_image.h"
#include"SDL_mixer.h"
#include <iostream>
#include <vector>
#include "Game.h"

class Dashboard
{
public:
    Dashboard();
    ~Dashboard();
    void dashInit(const char* title, int width, int height, bool fullscreen);
    void dashHandleEvents();
    void dashUpdate();
    bool dashRunning()
    {
        return isDashRunning;
    }

    void dashRender();
    void dashClean();
    static SDL_Event dashEvent;
    static SDL_Texture* dashTexture;
    static SDL_Texture* mouseTexture;
    bool isDashRunning=false;

protected:
    SDL_Window* dashWindow;
};