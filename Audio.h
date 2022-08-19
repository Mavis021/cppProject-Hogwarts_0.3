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
		backgroundMusic = Mix_LoadMUS(bgpath.c_str());
		soundEffect = Mix_LoadWAV(sepath.c_str());
	}
	~Audio()
	{}

	//void SetAudio(std::string mp3,std::string wav)
	//{
	//	backgroundMusic = Mix_LoadMUS(mp3.c_str());
	//	soundEffect = Mix_LoadWAV(wav.c_str());
	//}

	//void ChangeSoundEffects(std::string wav)
	//{
	//	soundEffect = Mix_LoadWAV(wav.c_str());
	//}
	//void ChangeBackgroundMusic(std::string mp3)
	//{
	//	backgroundMusic = Mix_LoadMUS(mp3.c_str());
	//}
	void playMusic()
	{
		Mix_PlayMusic(backgroundMusic, -1);
	}
	void playMusic(std::string mp3)
	{
		backgroundMusic = Mix_LoadMUS(bgpath.c_str());
		Mix_PlayMusic(backgroundMusic, -1);
	}
	void playEffects()
	{
		Mix_PlayChannel(-1, soundEffect, 0);
	}
	void playEffects(std::string wav)
	{
		soundEffect = Mix_LoadWAV(wav.c_str());
		Mix_PlayChannel(-1, soundEffect, 0);
	}
};

