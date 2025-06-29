#include "Game.h"
#include "Level.h"
#include "ScoreSystem.h"
#include <vector>

SDL_Renderer* Game::GameRenderer = nullptr;
int Game::windowWidth;
int Game::windowHeight;

Player* frog;
Object *apple, *banana, *strawberry, *grape1, *grape2, *wood1, *wood2, *wood3, *wood4;
Level* LevelMap;
ScoreSystem* playerScore;
int tmpTotalScore = 0;

TTF_Font* font = NULL;
SDL_Surface* text = NULL;

Game::Game():mGameWindow(nullptr),m_isRunning(false)
{
}

Game::~Game()
{	
	SDL_DestroyWindow(mGameWindow);
	SDL_DestroyRenderer(GameRenderer);
}

bool Game::running()
{
	return m_isRunning;
}

void Game::Start(const char* title, int xpos, int ypos, int width, int height)
{
	int random; 

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "CANNOT INITIALIZE SDL" << SDL_GetError() << std::endl;
		return;
	}

	SDL_DisplayMode display_mode;
	SDL_GetCurrentDisplayMode(0, &display_mode);
	windowWidth = display_mode.w;
	windowHeight = display_mode.h;

	mGameWindow = SDL_CreateWindow("Fruit Frog", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_BORDERLESS);
	if (mGameWindow == NULL)
	{
		std::cout << "CANNOT CREATE WINDOW" << SDL_GetError() << std::endl;
		return;
	}

	GameRenderer = SDL_CreateRenderer(mGameWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (GameRenderer == NULL)
	{
		std::cout << "CANNOT CREATE RENDERER" << SDL_GetError() << std::endl;
		return;
	}
	
	SDL_SetWindowFullscreen(mGameWindow, SDL_WINDOW_FULLSCREEN);

	//Initialize SDL_mixer with our chosen audio settings. Without this function the SDL_Mixer will not work. 
	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
		printf("Unable to initialize audio: %s\n", Mix_GetError());
		exit(1); // exit(1): used to indicate exit failure. Both exit(0) and exit(1) are jump statements of C++ and are used to terminate the program. And both report the status of termination of the program to the operating system.
	}

	//Load our WAV file from disk
	Game_Music = Mix_LoadMUS("assets/mushroom_dance.wav");
	if (Game_Music == NULL) {
		printf("Unable to load WAV file: %s\n", Mix_GetError());
		exit(1);
	}

	//play game music 
	Mix_PlayMusic(Game_Music, -1);

	Apple_Sound = Mix_LoadWAV("assets/apple_bite.ogg");
	if (Apple_Sound == NULL) {
		printf("Unable to load ogg file: %s\n", Mix_GetError());
		exit(1);
	}

	HitByLog_Sound = Mix_LoadWAV("assets/hit20.mp3");
	if (HitByLog_Sound == NULL) {
		printf("Unable to load mp3 file: %s\n", Mix_GetError());
		exit(1);
	}

	FootStep_Sound = Mix_LoadWAV("assets/stepdirt_1wav");
	if (HitByLog_Sound == NULL) {
		printf("Unable to load WAV file: %s\n", Mix_GetError());
		exit(1);
	}

	m_isRunning = true;
	frog = new Player("assets/fruitfrogspritesheets.png", 0, Game::windowHeight - 250);

	srand(time(0));
	random = (rand() % Game::windowWidth) + 1;
	//apple item can be capture set to true
	apple = new Object("assets/apple.png", random, 10, true);

	random = (rand() % Game::windowWidth) + 1;
	banana = new Object("assets/banana.png", random, 20, true);
	
	random = (rand() % Game::windowWidth) + 1;
	strawberry = new Object("assets/strawberry.png", random, 20, true);

	random = (rand() % Game::windowWidth) + 1;
	grape1 = new Object("assets/grape.png", random, 35, true);

	random = (rand() % Game::windowWidth) + 1;
	grape2 = new Object("assets/grape.png", random, 40, true);

	random = (rand() % Game::windowWidth) + 1;
	//wood item can be capture set to false because player cannot capture the wood
	wood1 = new Object("assets/woodlog.png", random, 10, false);

	random = (rand() % Game::windowWidth) + 1;
	wood2 = new Object("assets/woodlog.png", random, 10, false);
	
	random = (rand() % Game::windowWidth) + 1;
	wood3 = new Object("assets/woodlog.png", random, 10, false);
	
	random = (rand() % Game::windowWidth) + 1;
	wood4 = new Object("assets/woodlog.png", random, 10, false);

	LevelMap = new Level ("assets/background.png");
	playerScore = new ScoreSystem();

	font = TTF_OpenFont("assets/MartianMono.ttf", 50);
	if (!font) {
		printf("\033[1;31mFAILED to initialized TTF_OpenFont: %s\n", TTF_GetError());
		printf("\033[0m");
	}
}

void Game::HandleEvents()
{
	SDL_Event event;
	int moveXaxis = 25; // Player speed

	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		m_isRunning = false;
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
			m_isRunning = false;
			break;
		case SDLK_LEFT:
			if (isGamePause)
			{ // do nothing if game is pause, stop movement
			}
			else
				frog->PlayerLeftMove(moveXaxis);
			break;
		case SDLK_RIGHT:
			if (isGamePause)
			{ // do nothing if game is pause, stop movement 
			}
			else
				frog->PlayerRightMove(moveXaxis);
			break;
			/*
			case SDLK_p:
			
			isGamePause = true;
			P_pressedCounter++; //how many time p is pressed (pause, unpause, pause, unpause,...)
			if (P_pressedCounter % 2 == 0) // if p is pressed 2nd time is is odd
			{   //odd number P_pressedCounter = pausing the game
				// even number P_pressedCounter = unpause the game
				isGamePause = false;
			}
			break;
			*/
		
		case SDLK_RETURN:
			isGamePause = false;
			break;
		}
	case SDL_KEYUP:
		switch (event.key.keysym.sym) {
		case SDLK_LEFT:
			if (isGamePause)
			{ // do nothing if game is pause, stop movement
			}
			else
				frog->PlayerIdleAnimation();
			break;
		case SDLK_RIGHT:
			if (isGamePause)
			{ // do nothing if game is pause, stop movement 
			}
			else
				frog->PlayerIdleAnimation();
			break;

		}
	default:
		break;
	}

}

void Game::StartGameMessage()
{
	int texW = 0;
	int texH = 0;
	SDL_Color textColor = { 255, 255, 255, 255 };
	Uint32 wrapLength = 1700;
	text = TTF_RenderText_Solid_Wrapped(font, "Are you ready to play the game? Presss Enter to play. Press Escape to Exit the game. Movement Right and Left Arrow. ",
		textColor, wrapLength);

	if (!text)
	{
		std::cout << "\x1b[1;31mFAILED to create TTF_RenderText_Solid(): " << TTF_GetError() << "\033[0m" << std::endl;
	}
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(GameRenderer, text);
	SDL_FreeSurface(text);
	SDL_QueryTexture(textTexture, NULL, NULL, &texW, &texH);
	if (!textTexture)
	{
		std::cout << "\x1b[1;31mFAILED to create SDL_CreateTextureFromSurface(): " << SDL_GetError() << "\033[0m" << std::endl;
	}
	SDL_Rect textRect = { 0, 400, texW, texH };
	SDL_RenderCopy(GameRenderer, textTexture, NULL, &textRect);
	SDL_DestroyTexture(textTexture);
}

void Game::WaveOf_FallingObject()
{
	// check if all objects have moved from screen.
	SDL_Rect tmpRect;
	int randomX, randomY; 
	tmpRect = wood1->ObjectLocation();
	srand(time(0));
	randomX = (rand() % Game::windowWidth) - 100;

	if (tmpRect.y > Game::windowHeight || wood1->isCollide())
	{
		std::cout << "Wood1 Out from the screen\n";
		delete wood1;
		wood1 = NULL;
		randomY = (rand() % 200) + 1;
		wood1 = new Object("assets/woodlog.png", randomX, randomY, false);
	}

	tmpRect = wood2->ObjectLocation();
	randomX = (rand() % Game::windowWidth) - 100;
	if (tmpRect.y > Game::windowHeight || wood2->isCollide())
	{
		std::cout << "Wood2 Out from the screen\n";
		delete wood2;
		wood2 = NULL;
		randomY = (rand() % 200) + 1;
		wood2 = new Object("assets/woodlog.png", randomX, randomY, false);
	}

	tmpRect = wood3->ObjectLocation();
	randomX = (rand() % Game::windowWidth) - 100;
	if (tmpRect.y > Game::windowHeight || wood3->isCollide())
	{
		std::cout << "Wood2 Out from the screen\n";
		delete wood3;
		wood3 = NULL;
		randomY = (rand() % 200) + 1;
		wood3 = new Object("assets/woodlog.png", randomX, randomY, false);
	}
	
	tmpRect = wood4->ObjectLocation();
	randomX = (rand() % Game::windowWidth) - 100;
	if (tmpRect.y > Game::windowHeight || wood4->isCollide())
	{
		std::cout << "Wood2 Out from the screen\n";
		delete wood4;
		wood4 = NULL;
		randomY = (rand() % 200) + 1;
		wood4 = new Object("assets/woodlog.png", randomX, randomY, false);
	}

	randomX = (rand() % Game::windowWidth) - 100;
	tmpRect = apple->ObjectLocation();
	if (tmpRect.y > Game::windowHeight || apple->isCollide())
	{
		std::cout << "Apple Out from the screen\n";
		delete apple;
		apple = NULL;
		randomY = (rand() % 200) + 1;
		apple = new Object("assets/apple.png", randomX, randomY, true);
	}

	randomX = (rand() % Game::windowWidth) - 100;
	tmpRect = banana->ObjectLocation();
	if (tmpRect.y > Game::windowHeight || banana->isCollide())
	{
		std::cout << "Banana Out from the screen\n";
		delete banana;
		banana = NULL;
		randomY = (rand() % 200) + 1;
		banana = new Object("assets/banana.png", randomX, randomY, true);
	}

	randomX = (rand() % Game::windowWidth) - 100;
	tmpRect = strawberry->ObjectLocation();
	if (tmpRect.y > Game::windowHeight || strawberry->isCollide())
	{
		std::cout << "Strawberry Out from the screen\n";
		delete strawberry;
		strawberry = NULL;
		randomY = (rand() % 200) + 1;
		strawberry = new Object("assets/strawberry.png", randomX, randomY, true);
	}

	randomX = (rand() % Game::windowWidth) - 100;
	tmpRect = grape1->ObjectLocation();
	if (tmpRect.y > Game::windowHeight || grape1->isCollide())
	{
		std::cout << "Grape1 Out from the screen\n";
		delete grape1;
		grape1 = NULL;
		randomY = (rand() % 200) + 1;
		grape1 = new Object("assets/grape.png", randomX, randomY, true);
	}

	randomX = (rand() % Game::windowWidth) - 100;
	tmpRect = grape2->ObjectLocation();
	if (tmpRect.y > Game::windowHeight || grape2->isCollide())
	{
		std::cout << "Grape2 Out from the screen\n";
		delete grape2;
		grape2 = NULL;
		randomY = (rand() % 200) + 1;
		grape2 = new Object("assets/grape.png", randomX, randomY, true);
	}
		
	/*
	if (LevelMap->getCurrentLevel() == 1)
	{
		TTF_Font* tempFont = TTF_OpenFont("assets/MartianMono.ttf", 50);
		SDL_Color tempColor = { 255, 0, 0 };
		SDL_Surface* tempSurface = TTF_RenderText_Solid(tempFont, "SPEED LEVEL UP 2", tempColor);
		SDL_Rect tempRect = { 150, 150, 800, 400 };
		SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(Game::GameRenderer, tempSurface);
		SDL_FreeSurface(tempSurface);
		SDL_RenderCopy(Game::GameRenderer, tempTexture, NULL, &tempRect);
		SDL_DestroyTexture(tempTexture);
		SDL_RenderPresent(Game::GameRenderer);
		SDL_Delay(3000);
		LevelMap->setLevel(2); // You have level UP!! 	
	}*/

	if (playerScore->getCurrentScore() > 10)
	{
		apple->setNewSpeed(5);
		banana->setNewSpeed(5);
		strawberry->setNewSpeed(5);
		grape1->setNewSpeed(5);
		grape2->setNewSpeed(5);

		wood1->setNewSpeed(5);
		wood2->setNewSpeed(5);
		wood3->setNewSpeed(5);
		wood4->setNewSpeed(5);
		
		LevelMap->setLevel(2);
	}	
	
	if (playerScore->getCurrentScore() > 20)
	{
		apple->setNewSpeed(8);
		banana->setNewSpeed(8);
		strawberry->setNewSpeed(8);
		grape1->setNewSpeed(8);
		grape2->setNewSpeed(8);

		wood1->setNewSpeed(8);
		wood2->setNewSpeed(8);
		wood3->setNewSpeed(8);
		wood4->setNewSpeed(8);

		LevelMap->setLevel(3);
	}

	if (playerScore->getCurrentScore() > 30)
	{
		apple->setNewSpeed(10);
		banana->setNewSpeed(10);
		strawberry->setNewSpeed(10);
		grape1->setNewSpeed(10);
		grape2->setNewSpeed(10);

		wood1->setNewSpeed(10);
		wood2->setNewSpeed(10);
		wood3->setNewSpeed(10);
		wood4->setNewSpeed(10);

		LevelMap->setLevel(4);
	}

	if (playerScore->getCurrentScore() > 40)
	{
		apple->setNewSpeed(15);
		banana->setNewSpeed(15);
		strawberry->setNewSpeed(15);
		grape1->setNewSpeed(15);
		grape2->setNewSpeed(15);

		wood1->setNewSpeed(15);
		wood2->setNewSpeed(15);
		wood3->setNewSpeed(15);
		wood4->setNewSpeed(15);

		LevelMap->setLevel(5);
	}
	
}

void Game::GameIsPauseMessage()
{
	TTF_Font* tempFont = TTF_OpenFont("assets/MartianMono.ttf", 50);
	SDL_Color tempColor = { 255, 255, 255 };
	SDL_Surface* tempSurface = TTF_RenderText_Solid(tempFont, "PAUSE", tempColor);
	SDL_Rect tempRect = { 50, 150, 300, 300 };
	SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(Game::GameRenderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	SDL_RenderCopy(Game::GameRenderer, tempTexture, NULL, &tempRect);
}

void Game::checkCollision()
{
	apple->CollisionTesting(apple->ObjectLocation(), frog->PlayerLocation());
	banana->CollisionTesting(banana->ObjectLocation(), frog->PlayerLocation());
	strawberry->CollisionTesting(strawberry->ObjectLocation(), frog->PlayerLocation());
	grape1->CollisionTesting(grape1->ObjectLocation(), frog->PlayerLocation());
	grape2->CollisionTesting(grape2->ObjectLocation(), frog->PlayerLocation());
	
	if (apple->isCollide() && !apple->isScoreAlreadyRecorded())
	{
		Mix_PlayChannel(-1, Apple_Sound, 0);
		tmpTotalScore = tmpTotalScore + apple->ObjectCaptured();
	}

	if (banana->isCollide() && !banana->isScoreAlreadyRecorded())
	{
		Mix_PlayChannel(-1, Apple_Sound, 0);
		tmpTotalScore = tmpTotalScore + banana->ObjectCaptured();
	}

	if (strawberry->isCollide() && !strawberry->isScoreAlreadyRecorded())
	{
		Mix_PlayChannel(-1, Apple_Sound, 0);
		tmpTotalScore = tmpTotalScore + strawberry->ObjectCaptured();
	}
	
	if (grape1->isCollide() && !grape1->isScoreAlreadyRecorded())
	{
		Mix_PlayChannel(-1, Apple_Sound, 0);
		tmpTotalScore = tmpTotalScore + grape1->ObjectCaptured();
	}
	
	if (grape2->isCollide() && !grape2->isScoreAlreadyRecorded())
	{
		Mix_PlayChannel(-1, Apple_Sound, 0);
		tmpTotalScore = tmpTotalScore + grape2->ObjectCaptured();
	}
	
	wood1->CollisionTesting(wood1->ObjectLocation(), frog->PlayerLocation());
	if (wood1->isCollide())
	{	
		Mix_PlayChannel(-1, HitByLog_Sound, 0);
		LevelMap->ChangeLevel("assets/gameover.png");
		LevelMap->DrawLevel();
		
		playerScore->UpdateScoreSystem();
		playerScore->DrawScoreBox();

		SDL_RenderPresent(GameRenderer);
		m_isRunning = false;
		SDL_Delay(2000);
	}

	wood2->CollisionTesting(wood2->ObjectLocation(), frog->PlayerLocation());
	if (wood2->isCollide())
	{
		Mix_PlayChannel(-1, HitByLog_Sound, 0);
		LevelMap->ChangeLevel("assets/gameover.png");
		LevelMap->DrawLevel();
		
		playerScore->UpdateScoreSystem();
		playerScore->DrawScoreBox();
				
		SDL_RenderPresent(GameRenderer);
		m_isRunning = false;
		SDL_Delay(2000);
	}

	wood3->CollisionTesting(wood3->ObjectLocation(), frog->PlayerLocation());
	if (wood3->isCollide())
	{
		Mix_PlayChannel(-1, HitByLog_Sound, 0);
		LevelMap->ChangeLevel("assets/gameover.png");
		LevelMap->DrawLevel();
		
		playerScore->UpdateScoreSystem();
		playerScore->DrawScoreBox();

		SDL_RenderPresent(GameRenderer);
		m_isRunning = false;
		SDL_Delay(2000);
	}

	wood4->CollisionTesting(wood4->ObjectLocation(), frog->PlayerLocation());
	if (wood4->isCollide())
	{	
		Mix_PlayChannel(-1, HitByLog_Sound, 0);
		LevelMap->ChangeLevel("assets/gameover.png");
		LevelMap->DrawLevel();
		
		playerScore->UpdateScoreSystem();
		playerScore->DrawScoreBox();
		
		SDL_RenderPresent(GameRenderer);
		m_isRunning = false;
		SDL_Delay(2000);
	}
}

void Game::ScoreKeeping() 
{	
	if (!playerScore->IsScoreRecorded())
	{
		playerScore->setTotalScore(tmpTotalScore);
		playerScore->UpdateScoreSystem();		
	}
}

// update object and player movement
void Game::update()
{
	if (isGamePause == true) // default value of isGamePause = false
	{
		//GameIsPauseMessage();	
	}
	else
	{
		checkCollision();
		frog->PlayerUpdate();
		apple->ObjectUpdate();
		banana->ObjectUpdate();
		strawberry->ObjectUpdate();
		grape1->ObjectUpdate();
		grape2->ObjectUpdate();

		wood1->ObjectUpdate();
		wood2->ObjectUpdate();
		wood3->ObjectUpdate();
		wood4->ObjectUpdate();

		WaveOf_FallingObject();
		ScoreKeeping();		
	}
}

// render object and player new position
void Game::render()
{	
	SDL_RenderClear(GameRenderer);

	LevelMap->DrawLevel();

	frog->PlayerDisplay();	
	apple->ObjectDisplay();
	banana->ObjectDisplay();
	strawberry->ObjectDisplay();
	grape1->ObjectDisplay();
	grape2->ObjectDisplay();

	wood1->ObjectDisplay();
	wood2->ObjectDisplay();
	wood3->ObjectDisplay();
	wood4->ObjectDisplay();

	playerScore->DrawScoreBox();
	
	if (isGamePause == true)
	{
		StartGameMessage();
		SDL_RenderPresent(GameRenderer);
	}
	else
	{
		SDL_RenderPresent(GameRenderer);
	}
}

void Game::clean()
{	
	SDL_DestroyWindow(mGameWindow);
	SDL_DestroyRenderer(GameRenderer);

	Mix_FreeMusic(Game_Music);      // Mix_Music *Game_Music = NULL;	
	Mix_FreeChunk(Apple_Sound);    //   Mix_Chunk *Apple_Sound = NULL;
	Mix_FreeChunk(HitByLog_Sound);
	Mix_FreeChunk(FootStep_Sound);
	
	mGameWindow = NULL;
	GameRenderer = NULL;

	TTF_CloseFont(font);
	TTF_Quit();

	IMG_Quit();
	SDL_Quit();	
}

