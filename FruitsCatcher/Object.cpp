#include "Object.h"
#include "ScoreSystem.h"
#include "Level.h"

Object::Object(const char* texturefile, int pX, int pY, bool canBeCapture):m_destRect{0,0,0,0}, m_gravity(0)
{
	mObjectTexture = TextureManager::LoadTexture(texturefile);

	m_xpos = pX;
	m_ypos = pY;
	m_canBeCapture = canBeCapture; // store bool canBeCapture in private data to add score and flag to avoid capturing the wrong object.
}

Object::~Object()
{
	SDL_DestroyTexture(mObjectTexture);
	m_objectCapture = NULL;
}

void Object::ObjectUpdate()
{	
	if (m_collision)
	{
		SDL_DestroyTexture(mObjectTexture);
		return;
	}

	m_destRect.x = m_xpos;
	m_destRect.y = m_ypos;
	m_destRect.w = 40 * scale; // double the size
	m_destRect.h = 40 * scale; // double the size

	m_gravity += m_speed;
	m_destRect.y += m_gravity;
	//std::cout << "m_speed " << m_speed << std::endl;
}


void Object::ObjectDisplay()
{
	if (!m_collision)
	{
		SDL_RenderCopy(Game::GameRenderer, mObjectTexture, NULL, &m_destRect);
	}
}

int Object::ObjectCaptured()
{
	m_isScoreAlreadyRecorded = true;
	return m_objectCapture;
}

SDL_Rect Object::ObjectLocation(void)
{
	return m_destRect;
}

void Object::setNewSpeed(int newSpeed)
{
	m_speed = newSpeed;
}

float Object::getSpeed()
{
	return m_speed;
}

void Object::CollisionTesting(SDL_Rect pObject, SDL_Rect player)
{	
	m_collision = SDL_HasIntersection(&pObject, &player); // return true if SDL_Rect intersect
	
	// if obj is capture add point. flag_already_capture is false as default value
	if (m_canBeCapture && m_collision && !flag_already_captured)
	{
		m_objectCapture++;
		flag_already_captured = true; // obj already captured, flag_already_captured set to true, so the player cannot add more point capturing the same object more than once. 
	}

}

bool Object::isCollide()
{
	return m_collision;
}

bool Object::isScoreAlreadyRecorded()
{
	return m_isScoreAlreadyRecorded;
}

