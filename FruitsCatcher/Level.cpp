#include "Level.h"


Level::Level(const char* textureFile)
{
	m_TextureLevel = TextureManager::LoadTexture(textureFile);
}

Level::~Level()
{
	SDL_DestroyTexture(m_TextureLevel);
	m_TextureLevel = NULL;
}

void Level::ChangeLevel(const char* textureFile)
{
	m_TextureLevel = TextureManager::LoadTexture(textureFile);
}

void Level::setLevel(int LevelUP)
{
	m_currentLevel = LevelUP;
}

int Level::getCurrentLevel()
{
	return m_currentLevel;
}

void Level::DrawLevel()
{
	SDL_RenderCopy(Game::GameRenderer, m_TextureLevel, NULL, NULL);
}

void Level::setLevelSpeed(int pSpeed)
{
	m_speed = pSpeed;
}

int Level::getLevelSpeed()
{
	return m_speed;
}
