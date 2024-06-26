#include <algorithm>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <ctime>
#include <vector>
#include<fstream>
#include <string>
#include "Header.h"
using namespace std;

int main(int argc, char* argv[])
{
    setlocale(0, "");
    srand(time(NULL));

    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_Window* window = SDL_CreateWindow("Memo",
        100, 100,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Surface *FonImage = SDL_LoadBMP("fon.bmp");
    SDL_Texture *FonTexture = SDL_CreateTextureFromSurface(renderer, FonImage);
    SDL_FreeSurface(FonImage);

    TTF_Font* my_font = TTF_OpenFont("font.ttf", 50);
    Mix_Init(0);
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, FonTexture, NULL, NULL);
    SDL_RenderPresent(renderer);
    
    startWindow(renderer, my_font);
    if(Data.music == true)
    {
        loadMusic();
    }
    bool exit = false;
    do
    {
        clearCards();
        clearPictures();
        int choose = chooseGameMode(renderer, my_font, FonTexture);
        fillPictureCards(renderer);
        fillCardsWithImages(renderer, choose);
        gamePlay(renderer, my_font,FonTexture,choose);
    }while(!exit);
    clearFile("data.txt");
    Mix_FreeChunk(fon);
    Mix_FreeChunk(Sound);
    Mix_CloseAudio();
    SDL_DestroyTexture(FonTexture);
    TTF_CloseFont(my_font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}