#pragma once
#include<string>

class Map
{
private:

public:
	Map();
	~Map();

	static bool startMapMovement;
	static void LoadMap(std::string path, int sizex, int sizey,int loop);

};