#pragma once
#include <SDL_ttf.h>
#include <string>

class ScoreSystem
{
public:
	ScoreSystem();
	~ScoreSystem();
	void UpdateScoreSystem();
	void DrawScoreBox();
	void setTotalScore(int);
	int getCurrentScore();
	bool IsScoreRecorded();

private:
	TTF_Font* m_font;
	SDL_Color m_fontColor;
	SDL_Surface* m_TextSurface;
	SDL_Texture* m_TextTexture;
	SDL_Rect m_ShowText;

	std::string m_text;
	int m_playerPoints;
	bool m_isScoreRecorded = false;
};

