#pragma once
#include "Game.h"

class Level
{
public:
	Level(const char* textureFile);
	~Level();
	void ChangeLevel(const char* textureFile);
	void setLevel(int);
	int getCurrentLevel();
	void DrawLevel();
	void setLevelSpeed(int);
	int getLevelSpeed();

private:
	SDL_Texture* m_TextureLevel;
	int m_currentLevel = 1; // current level is set to 1
	int m_speed = 2;
};

