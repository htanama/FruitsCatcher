#include "Player.h"

Player::Player(const char* texturefile, int pX, int pY)
{
	mPlayerTexture = TextureManager::LoadTexture(texturefile);

	m_xpos = pX;
	m_ypos = pY;

	SDL_QueryTexture(mPlayerTexture, NULL, NULL, &textureWidth, &textureHeight);

	frameWidth = textureWidth / 5;
	frameHeight = textureHeight / 3;
	
	m_srcRect.x = m_srcRect.y = 0;
	m_srcRect.w = frameWidth;
	m_srcRect.h = frameHeight;
}

Player::~Player()
{
	SDL_DestroyTexture(mPlayerTexture);
}

void Player::PlayerUpdate()
{
	m_destRect.x = m_xpos; // make sure the x posistion is updated. 
	//m_destRect.y = m_ypos;

	PlayerBoundary();
	
	m_destRect.x = m_xpos;
	m_destRect.y = m_ypos;
	m_destRect.w = 64 * scale; // double scale
	m_destRect.h = 64 * scale; // double scale

	PlayerAnimation();
	
}

void Player::PlayerDisplay()
{	
	SDL_RenderCopy(Game::GameRenderer, mPlayerTexture, &m_srcRect, &m_destRect);
}

void Player::PlayerBoundary()
{	// check left boundary
	if (m_destRect.x < 0)
		m_xpos = 0;
	
	// check right boundary
	if (m_destRect.x + m_destRect.w > Game::windowWidth)
		m_xpos = Game::windowWidth - m_destRect.w;
}

void Player::PlayerLeftMove(int pXaxis)
{	
	// move player posistion 10 pixels to the left
	// m_xpos = m_xpos - 10
	m_xpos -= pXaxis;
}

void Player::PlayerRightMove(int pXaxis)
{
	// m_xpos = m_xpos + 10
	m_xpos += pXaxis;
}

void Player::PlayerAnimation()
{	// getting each frame from the sprite sheet

	if (m_playerIdle)
	{
		frameTime++; // every 5 game loops (20/5 = 4), we get a new frame to be place for drawing
		if ((FPS / frameTime) == 4)
		{
			frameTime = 0;
			m_srcRect.y = frameWidth * 0;
			m_srcRect.x += frameWidth; // 0 = 0 + 64; 64 = 64 + 64; 128 = 128 + 64; 
			if (m_srcRect.x >= textureWidth) //m_srcRect=320 >= textureWidth=320
				m_srcRect.x = 0; // back to first frame 
			/*
			m_srcRect.x will get the first frame from the sprite sheet
			and then it goes to the next frame using this formula m_srcRect = m_srcRect + textureWidth
			we send the m_srcRect to the SDL_RenderCopy to be render.
			*/
			m_playerMoveLeft = false;
			m_playerMoveRight = false;
		}
	}

	if (m_playerMoveLeft) 
	{
		frameTime++;
		if ((FPS / frameTime) == 4)
		{
			frameTime = 0;
			m_srcRect.y = frameHeight * 1;
			m_srcRect.x += frameWidth;
			if (m_srcRect.x >= textureWidth) //m_srcRect=320 >= textureWidth=320
				m_srcRect.x = 0;

			m_playerIdle = false;
			m_playerMoveRight = false;
		}
	}

	if (m_playerMoveRight)
	{
		frameTime++;
		if ((FPS / frameTime) == 4)
		{
			frameTime = 0;
			m_srcRect.y = frameHeight * 2;
			m_srcRect.x += frameWidth;
			if (m_srcRect.x >= textureWidth) //m_srcRect=320 >= textureWidth=320
				m_srcRect.x = 0;

			m_playerIdle = false;
			m_playerMoveLeft = false;
		}
	}
}

void Player::PlayerIdleAnimation()
{
	m_playerIdle = true;
}

SDL_Rect Player::PlayerLocation(void)
{
	return m_destRect;
}
