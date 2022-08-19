#pragma once
#include "SDL_mixer.h"
#include "Game.h"
#include "ECS/ECS.h"
#include<string>

class Audio:public Component
{
private:
	std::string bgpath, sepath;
public:
	static Mix_Music* backgroundMusic;
	static Mix_Chunk* soundEffect;
	Audio(){}
	Audio(std::string bgm,std::string se):bgpath(bgm),sepath(se)
	{
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
			std::cout << "error:" << Mix_GetError() << std::endl;
		backgroundMusic = Mix_LoadMUS(bgpath.c_str());
		soundEffect = Mix_LoadWAV(sepath.c_str());
	}
	Audio(std::string bgm) :bgpath(bgm)
	{
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
			std::cout << "error:" << Mix_GetError() << std::endl;
		backgroundMusic = Mix_LoadMUS(bgpath.c_str());
	}
	~Audio()
	{}
	void playMusic()
	{
		Mix_PlayMusic(backgroundMusic, -1);
	}
	void playMusic(std::string mp3)
	{
		backgroundMusic = Mix_LoadMUS(bgpath.c_str());
		Mix_PlayMusic(backgroundMusic, -1);
	}
	void freeMusic()
	{
		Mix_FreeMusic(backgroundMusic);
	}
	void playEffects()
	{
		Mix_PlayChannel(2, soundEffect, 0);
	}
	void playEffects(std::string wav)
	{
		soundEffect = Mix_LoadWAV(wav.c_str());
		Mix_PlayChannel(2, soundEffect, 0);
	}
	void pauseMusic()
	{
	 Mix_HaltMusic();
	}
};

