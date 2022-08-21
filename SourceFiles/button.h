#pragma once
#include "SDL.h"
#include <string>
#include "dashboard.h"
#include<string>

class Button :public Dashboard
{
public:
    SDL_Texture* buttonTexture;
    static SDL_Rect srcRect;
    SDL_Rect destRect;
    bool isSelected ;
    bool returnIsSelected() { return isSelected; }
    std::string buttonPath;
    Button();
    Button(std::string path, int xpos, int ypos, int width, int height);
    static SDL_Event buttonEvent;
    void handleEvents();
    void displayButton();
};