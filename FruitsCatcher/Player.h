#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "TextureManager.h"

class Player
{
public:
	Player(const char* texturefile, int pX, int pY);
	~Player();
	void PlayerUpdate();
	void PlayerDisplay();
	void PlayerBoundary();
	void PlayerLeftMove(int pXaxis);
	void PlayerRightMove(int pXaxis);
	void PlayerAnimation();
	void PlayerIdleAnimation();

	SDL_Rect PlayerLocation(void);
	
private:
	SDL_Rect mPlayerRect;
	SDL_Texture *mPlayerTexture;	
	SDL_Rect m_srcRect, m_destRect;
	int m_xpos;
	int m_ypos;
	int scale = 2;

	bool m_playerMoveLeft = false;
	bool m_playerMoveRight = false;
	bool m_playerIdle = true;
	SDL_Rect m_SpriteFrame;
	int frameWidth, frameHeight;
	int textureWidth, textureHeight;
	
	const int FPS = 60;
	int frameTime = 0;
};

#endif 
