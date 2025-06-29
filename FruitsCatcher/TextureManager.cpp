#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture)
{
    SDL_Surface* tempSurface = IMG_Load(texture); 
    
    if (!tempSurface)
    {
        std::cout << "ERROR creating surface" << SDL_GetError() << std::endl;
    }

    SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(Game::GameRenderer, tempSurface); 

    if (!tempTexture)
    {
        std::cout << "ERROR creating texture" << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(tempSurface);

    return tempTexture;
}
