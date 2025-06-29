#include "ScoreSystem.h"
#include "Game.h"


ScoreSystem::ScoreSystem(): m_playerPoints(0)
{
	TTF_Init();
	m_font = TTF_OpenFont("assets/MartianMono.ttf", 50);
	m_fontColor = { 255, 255, 255 };
	
	m_text = "Total Score= " + std::to_string(m_playerPoints);
	if (!m_font)
	{
		std::cout << "ERROR creating font " << SDL_GetError() << std::endl;
	}

	m_TextSurface = TTF_RenderText_Solid(m_font, m_text.c_str(), m_fontColor);
	
	if (!m_TextSurface)
	{
		std::cout << "ERROR creating m_TextSurface " << SDL_GetError() << std::endl;
	}
	
	m_TextTexture = SDL_CreateTextureFromSurface(Game::GameRenderer, m_TextSurface);
	if (!m_TextTexture)
	{
		std::cout << "ERROR creating m_TextTexture " << SDL_GetError() << std::endl;
	}
	
	SDL_FreeSurface(m_TextSurface);
	m_ShowText = { 10, 0, 400, 100 };
}

ScoreSystem::~ScoreSystem()
{	
	SDL_DestroyTexture(m_TextTexture);
	SDL_FreeSurface(m_TextSurface);
	TTF_CloseFont(m_font);
	
	std::cout << "DEALLOCATE ScoreSystem from memory " << std::endl;
}

void ScoreSystem::UpdateScoreSystem()
{
	m_text = "Total Score= " + std::to_string(m_playerPoints);
	if (!m_font)
	{
		std::cout << "ERROR creating font " << SDL_GetError() << std::endl;
	}

	m_TextSurface = TTF_RenderText_Solid(m_font, m_text.c_str(), m_fontColor);

	if (!m_TextSurface)
	{
		std::cout << "ERROR creating m_TextSurface " << SDL_GetError() << std::endl;
	}

	m_TextTexture = SDL_CreateTextureFromSurface(Game::GameRenderer, m_TextSurface);
	if (!m_TextTexture)
	{
		std::cout << "ERROR creating m_TextTexture " << SDL_GetError() << std::endl;
	}
	
	SDL_FreeSurface(m_TextSurface);
	m_isScoreRecorded = true; // score updated
}

void ScoreSystem::DrawScoreBox()
{
	SDL_RenderCopy(Game::GameRenderer, m_TextTexture, NULL, &m_ShowText);
	m_isScoreRecorded = false; // to record a new player score	

	SDL_DestroyTexture(m_TextTexture);
	//std::cout << "DESTORY m_TextTexture from memory " << std::endl;	
}

void ScoreSystem::setTotalScore(int totalScore)
{
	m_playerPoints = totalScore;
}

int ScoreSystem::getCurrentScore()
{
	return m_playerPoints;
}

bool ScoreSystem::IsScoreRecorded()
{	
	return m_isScoreRecorded;
}
