#pragma once

#include "ECS.h"
#include"../textureManager.h"
#include "../Game.h"

#include<SDL.h>
#include<SDL_ttf.h>
#include<string>


class UILabel : public Component
{
public:
	UILabel(int xpos, int ypos, std::string text, std::string path,int fontSize, SDL_Colour& colour) :
		labelText(text), labelFont(path),labelSize(fontSize), textColour(colour)
	{
		position.x = xpos;
		position.y = ypos;

		SetLabelText(labelText, labelFont,labelSize);
	}
	~UILabel() {}


	void SetLabelText(std::string text, std::string font,int size)
	{
		SDL_Surface* surf = TTF_RenderText_Blended(TTF_OpenFont(font.c_str(), size), text.c_str(), textColour);
		labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surf);
		SDL_FreeSurface(surf);

		//we dont know the width and height of the texture we created so using sdlquery 
		SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
	}

	void draw() override
	{
		SDL_RenderCopy(Game::renderer, labelTexture, nullptr, &position);  //drawing texture
	}
private:
	SDL_Rect position;
	std::string labelText;
	std::string labelFont;
	int labelSize;
	SDL_Colour textColour;
	SDL_Texture* labelTexture;
};
