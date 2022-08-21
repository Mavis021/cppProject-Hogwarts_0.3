#include"button.h"

SDL_Rect Button::srcRect = { 0 ,0, 200, 50 }; //SAME FOR ALL THE BUTTONS
SDL_Event Button::buttonEvent;

Button::Button()
{
}

Button::Button(std::string path, int xpos, int ypos, int width, int height)
{
    buttonPath = path;
    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = width;
    destRect.h = height;
}

void Button::displayButton()
{
    SDL_Surface* tempSurface = IMG_Load(buttonPath.c_str());
    buttonTexture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    SDL_RenderCopyEx(Game::renderer, buttonTexture, &srcRect, &destRect, NULL, NULL, SDL_FLIP_NONE);
}

void Button::handleEvents()
{
    SDL_PollEvent(&buttonEvent);
    if (SDL_MOUSEMOTION == buttonEvent.type)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        std::cout << x << " : " << y << std::endl;
        if (x >= destRect.x && x <= destRect.x + destRect.w && y >= destRect.y && y <= destRect.y + destRect.h)
        {
            isSelected = true;
        }
        else
            isSelected = false;
    }
}

