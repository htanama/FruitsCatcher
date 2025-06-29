#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#include <SDL.h>
#include "TextureManager.h"

class Object
{
public:
	Object(const char* texturefile, int pX, int pY, bool canBeCapture);
	~Object();
	void ObjectUpdate();
	void ObjectDisplay();
	SDL_Rect ObjectLocation(void);

	void setNewSpeed(int);
	float getSpeed();
	void CollisionTesting(SDL_Rect pObject, SDL_Rect player);
	bool isCollide();
	bool isScoreAlreadyRecorded();
	int ObjectCaptured();
	
private:
	SDL_Texture* mObjectTexture;
	SDL_Rect m_destRect;
	
	int m_xpos;
	int m_ypos;
	int m_gravity;
	int m_speed = 2;
	int m_objectCapture = 0;
	int scale = 2;
	bool m_collision = false;
	bool m_canBeCapture = true;
	bool flag_already_captured = false;
	bool m_isScoreAlreadyRecorded = false;
};
#endif

