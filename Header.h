#pragma once
#include <algorithm>
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <ctime>
#include <vector>
#include <fstream>
#include <string>

struct Button {
    SDL_Rect rect;
    char text[5];
};

struct Card {
    int x, y, w, h, num;
    bool click = false;
    bool question = true;
    bool found = false;
    SDL_Texture* picture;
};

struct Picture {
    int id;
    SDL_Texture* picture;
    bool flag = false;
};

struct File {
    bool music;
    std::string bestTime[6];
};

extern Card Cards[72];
extern Picture Pictures[36];
extern File Data;
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern int COUNT_CARDS;
extern int paddingX;
extern int paddingY;
extern int areaX;
extern int areaY;
extern int areaWidth;
extern int areaHeight;
extern Mix_Chunk* Sound;
extern Mix_Chunk* fon;

void loadMusic();
void loadClickSound();
void clickCardSound();
void notFoundPairSound();
void foundPairSound();
void loadWinSound();
void clearFile(std::string name);
void readDataFile(std::string name);
void writeInFile(std::string name);
bool Hitting(int x, int y, SDL_Rect rect);
SDL_Texture* getTextTexture(SDL_Renderer*& renderer, char* text, TTF_Font* font, SDL_Color fore, SDL_Color back);
void drawText(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect rect);
void fillPictureCards(SDL_Renderer* renderer);
void startWindow(SDL_Renderer* renderer, TTF_Font* font);
void drawChooseButtons(SDL_Renderer* renderer, TTF_Font* font, Button buttons[], int buttonCount);
int chooseGameMode(SDL_Renderer* renderer, TTF_Font* font, SDL_Texture* fonTexture);
void clearCards();
void clearPictures();
void drawCardsBack(SDL_Renderer* renderer, SDL_Texture* fonTexture, int gameMode);
void drawCard(SDL_Renderer* renderer, int cardIndex, int gameMode);
void fillCardsWithImages(SDL_Renderer* renderer, int gameMode);
void gamePlay(SDL_Renderer* renderer, TTF_Font* font, SDL_Texture* fonTexture, int choose);