#include "header.h"
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
using namespace std;

Card Cards[72];
Picture Pictures[36];
File Data;
const int SCREEN_WIDTH = 1180;
const int SCREEN_HEIGHT = 720;
int COUNT_CARDS = 6;
int paddingX;
int paddingY;
int areaX;
int areaY;
int areaWidth;
int areaHeight;
Mix_Chunk* Sound = NULL;
Mix_Chunk* fon = NULL;

void loadMusic() {
    fon = Mix_LoadWAV("fon.wav");
    Mix_PlayChannel(-1, fon, -1);
}
void loadClickSound()
{
    Sound = Mix_LoadWAV("click.wav");
    Mix_PlayChannel(-1, Sound, 0);
}
void clickCardSound()
{
    Sound = Mix_LoadWAV("clickCard.wav");
    Mix_PlayChannel(-1, Sound, 0);
}
void notFoundPairSound()
{
    Sound = Mix_LoadWAV("notFoundPair.wav");
    Mix_PlayChannel(-1, Sound, 0);
}
void foundPairSound()
{
    Sound = Mix_LoadWAV("foundPair.wav");
    Mix_PlayChannel(-1, Sound, 0);
}
void loadWinSound()
{
    Sound = Mix_LoadWAV("win.wav");
    Mix_PlayChannel(-1, Sound, 0);
}
void clearFile(string name)
{
    ofstream file(name, ios_base::in | ios_base::out);
    file << "AA";
    file.seekp(ios::beg);
    file << "1";
    file.close();
}
void readDataFile(string name)
{
    ifstream file(name);
    if(file.is_open())
    {
        string line;
        getline(file, line);
        atoi(line.c_str()) == 1? Data.music = true: Data.music = false;
        for(int i=0; i < 6; i++)
        {
            getline(file, line);
            Data.bestTime[i] = line;
        }
    }
    file.close();
}
void writeInFile(string name)
{
    ofstream file(name);
    if(Data.music == true)
    {
        file << 1 << endl;
    }
    else
    {
        file << 0 << endl;
    }
    for(int i=0; i < 6; i++)
    {
        file << Data.bestTime[i] << endl;
    }
    file.close();
}
bool Hitting(int x, int y, SDL_Rect rect)
{
    return x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h;
}
SDL_Texture* getTextTexture(SDL_Renderer* &renderer, char*text, TTF_Font *font, SDL_Color fore, SDL_Color back)
{
    SDL_Surface* textSurface = NULL;
    textSurface = TTF_RenderText_Shaded(font, text, fore, back);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    return texture;
}
void drawText(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect rect)
{
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}
void fillPictureCards(SDL_Renderer *renderer)
{
    SDL_Surface *tempImage = SDL_LoadBMP("1.bmp");
    SDL_Texture *tempTexture = SDL_CreateTextureFromSurface(renderer, tempImage);
    SDL_FreeSurface(tempImage);Pictures[0].picture = tempTexture;Pictures[0].id = 1;
    tempImage = SDL_LoadBMP("2.bmp");
    tempTexture = SDL_CreateTextureFromSurface(renderer, tempImage);
    SDL_FreeSurface(tempImage);Pictures[1].picture = tempTexture;Pictures[1].id = 2;
    tempImage = SDL_LoadBMP("3.bmp");
    tempTexture = SDL_CreateTextureFromSurface(renderer, tempImage);
    SDL_FreeSurface(tempImage);Pictures[2].picture = tempTexture;Pictures[2].id = 3;
    tempImage = SDL_LoadBMP("4.bmp");
    tempTexture = SDL_CreateTextureFromSurface(renderer, tempImage);
    SDL_FreeSurface(tempImage);Pictures[3].picture = tempTexture;Pictures[3].id = 4;
    tempImage = SDL_LoadBMP("5.bmp");
    tempTexture = SDL_CreateTextureFromSurface(renderer, tempImage);
    SDL_FreeSurface(tempImage);Pictures[4].picture = tempTexture;Pictures[4].id = 5;
    tempImage = SDL_LoadBMP("6.bmp");
    tempTexture = SDL_CreateTextureFromSurface(renderer, tempImage);
    SDL_FreeSurface(tempImage);Pictures[5].picture = tempTexture;Pictures[5].id = 6;
    tempImage = SDL_LoadBMP("7.bmp");
    tempTexture = SDL_CreateTextureFromSurface(renderer, tempImage);
    SDL_FreeSurface(tempImage);Pictures[6].picture = tempTexture;Pictures[6].id = 7;
    tempImage = SDL_LoadBMP("8.bmp");
    tempTexture = SDL_CreateTextureFromSurface(renderer, tempImage);
    SDL_FreeSurface(tempImage);Pictures[7].picture = tempTexture;Pictures[7].id = 8;
    tempImage = SDL_LoadBMP("9.bmp");
    tempTexture = SDL_CreateTextureFromSurface(renderer, tempImage);
    SDL_FreeSurface(tempImage);Pictures[8].picture = tempTexture;Pictures[8].id = 9;
    tempImage = SDL_LoadBMP("10.bmp");
    tempTexture = SDL_CreateTextureFromSurface(renderer, tempImage);
    SDL_FreeSurface(tempImage);Pictures[9].picture = tempTexture;Pictures[9].id = 10;
    tempImage = SDL_LoadBMP("11.bmp");
    tempTexture = SDL_CreateTextureFromSurface(renderer, tempImage);
    SDL_FreeSurface(tempImage);Pictures[10].picture = tempTexture;Pictures[10].id = 11;
    tempImage = SDL_LoadBMP("12.bmp");
    tempTexture = SDL_CreateTextureFromSurface(renderer, tempImage);
    SDL_FreeSurface(tempImage);Pictures[11].picture = tempTexture;Pictures[11].id = 12;
    tempImage = SDL_LoadBMP("13.bmp");
    tempTexture = SDL_CreateTextureFromSurface(renderer, tempImage);
    SDL_FreeSurface(tempImage);Pictures[12].picture = tempTexture;Pictures[12].id = 13;
    tempImage = SDL_LoadBMP("14.bmp");
    tempTexture = SDL_CreateTextureFromSurface(renderer, tempImage);
    SDL_FreeSurface(tempImage);Pictures[13].picture = tempTexture;Pictures[13].id = 14;
    tempImage = SDL_LoadBMP("15.bmp");
    tempTexture = SDL_CreateTextureFromSurface(renderer, tempImage);
    SDL_FreeSurface(tempImage);Pictures[14].picture = tempTexture;Pictures[14].id = 15;
    tempImage = SDL_LoadBMP("16.bmp");
    tempTexture = SDL_CreateTextureFromSurface(renderer, tempImage);
    SDL_FreeSurface(tempImage);Pictures[15].picture = tempTexture;Pictures[15].id = 16;
    tempImage = SDL_LoadBMP("17.bmp");
    tempTexture = SDL_CreateTextureFromSurface(renderer, tempImage);
    SDL_FreeSurface(tempImage);Pictures[16].picture = tempTexture;Pictures[16].id = 17;
    tempImage = SDL_LoadBMP("18.bmp");
    tempTexture = SDL_CreateTextureFromSurface(renderer, tempImage);
    SDL_FreeSurface(tempImage);Pictures[17].picture = tempTexture;Pictures[17].id = 18;
    tempImage = SDL_LoadBMP("19.bmp");
    tempTexture = SDL_CreateTextureFromSurface(renderer, tempImage);
    SDL_FreeSurface(tempImage);Pictures[18].picture = tempTexture;Pictures[18].id = 19;
    tempImage = SDL_LoadBMP("20.bmp");
    tempTexture = SDL_CreateTextureFromSurface(renderer, tempImage);
    SDL_FreeSurface(tempImage);Pictures[19].picture = tempTexture;Pictures[19].id = 20;
    tempImage = SDL_LoadBMP("21.bmp");
    tempTexture = SDL_CreateTextureFromSurface(renderer, tempImage);
    SDL_FreeSurface(tempImage);Pictures[20].picture = tempTexture;Pictures[20].id = 21;
    tempImage = SDL_LoadBMP("22.bmp");
    tempTexture = SDL_CreateTextureFromSurface(renderer, tempImage);
    SDL_FreeSurface(tempImage);Pictures[21].picture = tempTexture;Pictures[21].id = 22;
    tempImage = SDL_LoadBMP("23.bmp");
    tempTexture = SDL_CreateTextureFromSurface(renderer, tempImage);
    SDL_FreeSurface(tempImage);Pictures[22].picture = tempTexture;Pictures[22].id = 23;
    tempImage = SDL_LoadBMP("24.bmp");
    tempTexture = SDL_CreateTextureFromSurface(renderer, tempImage);
    SDL_FreeSurface(tempImage);Pictures[23].picture = tempTexture;Pictures[23].id = 24;
    tempImage = SDL_LoadBMP("25.bmp");
    tempTexture = SDL_CreateTextureFromSurface(renderer, tempImage);
    SDL_FreeSurface(tempImage);Pictures[24].picture = tempTexture;Pictures[24].id = 25;
    tempImage = SDL_LoadBMP("26.bmp");
    tempTexture = SDL_CreateTextureFromSurface(renderer, tempImage);
    SDL_FreeSurface(tempImage);Pictures[25].picture = tempTexture;Pictures[25].id = 26;
    tempImage = SDL_LoadBMP("27.bmp");
    tempTexture = SDL_CreateTextureFromSurface(renderer, tempImage);
    SDL_FreeSurface(tempImage);Pictures[26].picture = tempTexture;Pictures[26].id = 27;
    tempImage = SDL_LoadBMP("28.bmp");
    tempTexture = SDL_CreateTextureFromSurface(renderer, tempImage);
    SDL_FreeSurface(tempImage);Pictures[27].picture = tempTexture;Pictures[27].id = 28;
    tempImage = SDL_LoadBMP("29.bmp");
    tempTexture = SDL_CreateTextureFromSurface(renderer, tempImage);
    SDL_FreeSurface(tempImage);Pictures[28].picture = tempTexture;Pictures[28].id = 29;
    tempImage = SDL_LoadBMP("30.bmp");
    tempTexture = SDL_CreateTextureFromSurface(renderer, tempImage);
    SDL_FreeSurface(tempImage);Pictures[29].picture = tempTexture;Pictures[29].id = 30;
    tempImage = SDL_LoadBMP("31.bmp");
    tempTexture = SDL_CreateTextureFromSurface(renderer, tempImage);
    SDL_FreeSurface(tempImage);Pictures[30].picture = tempTexture;Pictures[30].id = 31;
    tempImage = SDL_LoadBMP("32.bmp");
    tempTexture = SDL_CreateTextureFromSurface(renderer, tempImage);
    SDL_FreeSurface(tempImage);Pictures[31].picture = tempTexture;Pictures[31].id = 32;
    tempImage = SDL_LoadBMP("33.bmp");
    tempTexture = SDL_CreateTextureFromSurface(renderer, tempImage);
    SDL_FreeSurface(tempImage);Pictures[32].picture = tempTexture;Pictures[32].id = 33;
    tempImage = SDL_LoadBMP("34.bmp");
    tempTexture = SDL_CreateTextureFromSurface(renderer, tempImage);
    SDL_FreeSurface(tempImage);Pictures[33].picture = tempTexture;Pictures[33].id = 34;
    tempImage = SDL_LoadBMP("35.bmp");
    tempTexture = SDL_CreateTextureFromSurface(renderer, tempImage);
    SDL_FreeSurface(tempImage);Pictures[34].picture = tempTexture;Pictures[34].id = 35;
    tempImage = SDL_LoadBMP("36.bmp");
    tempTexture = SDL_CreateTextureFromSurface(renderer, tempImage);
    SDL_FreeSurface(tempImage);Pictures[35].picture = tempTexture;Pictures[35].id = 36;
}
void startWindow(SDL_Renderer *renderer, TTF_Font* font)
{
    readDataFile("data.txt");
    char text[5] = "Play"; 
    SDL_Color fore = { 255,215,0 };
    SDL_Color back = { 255,250,205 };
    SDL_Rect sound = {400, 500, 100, 100};
    SDL_Rect noSound = {700, 500, 100, 100};
    SDL_Texture *textTexture = getTextTexture(renderer, text, font, fore, back);
    SDL_Rect tempRect = {450, 280, 300, 140};
    drawText(renderer, textTexture, tempRect);
    SDL_DestroyTexture(textTexture);

    SDL_Surface *tempImage = SDL_LoadBMP("sound.bmp");
    SDL_Texture *soundTexture = SDL_CreateTextureFromSurface(renderer, tempImage);
    SDL_FreeSurface(tempImage);
    
    tempImage = SDL_LoadBMP("noSound.bmp");
    SDL_Texture *noSoundTexture = SDL_CreateTextureFromSurface(renderer, tempImage);
    SDL_FreeSurface(tempImage);
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderFillRect(renderer, &sound);
    SDL_RenderCopy(renderer, soundTexture, NULL, &sound);
    SDL_RenderCopy(renderer, noSoundTexture, NULL, &noSound);

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
    SDL_Rect temp;
    if(Data.music)
    {
        temp = {sound.x, sound.y, sound.w, sound.h};
    }
    else
    {
        temp = {noSound.x, noSound.y, noSound.w, noSound.h};
    }
    SDL_RenderDrawRect(renderer, &temp);
    SDL_RenderPresent(renderer);

    bool quit = false;
    SDL_Event event;
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
                SDL_Quit();
            }
            if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
            {
                if(Hitting(event.button.x, event.button.y, tempRect))
                {
                    if(Data.music == true)
                    {
                        loadClickSound();
                        SDL_Delay(400);
                    }
                    quit = true;
                }
                if(Hitting(event.button.x, event.button.y, sound))
                {
                    Data.music = true;
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
                    SDL_RenderFillRect(renderer, &sound);
                    SDL_RenderFillRect(renderer, &noSound);
                    SDL_RenderCopy(renderer, soundTexture, NULL, &sound);
                    SDL_RenderCopy(renderer, noSoundTexture, NULL, &noSound);
                    temp = {sound.x, sound.y, sound.w, sound.h};
                    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
                    SDL_RenderDrawRect(renderer, &temp);
                    SDL_RenderPresent(renderer);
                }
                if(Hitting(event.button.x, event.button.y, noSound))
                {
                    Data.music = false;
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
                    SDL_RenderFillRect(renderer, &sound);
                    SDL_RenderFillRect(renderer, &noSound);
                    SDL_RenderCopy(renderer, soundTexture, NULL, &sound);
                    SDL_RenderCopy(renderer, noSoundTexture, NULL, &noSound);
                    temp = {noSound.x, noSound.y, noSound.w, noSound.h};
                    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
                    SDL_RenderDrawRect(renderer, &temp);
                    SDL_RenderPresent(renderer);
                }
            }
        }
    }
    SDL_DestroyTexture(soundTexture);
    SDL_DestroyTexture(noSoundTexture);
    writeInFile("data.txt");
}
void drawChooseButtons(SDL_Renderer *renderer, TTF_Font* font, Button buttons[], int buttonCount)
{
    SDL_Color fore = { 255, 215, 0 };
    SDL_Color back = { 255, 250, 205 };
    
    // Label
    char label[15] = { 'C', 'h', 'o', 'o', 's', 'e', ' ', 'm', 'o', 'd', 'e', ':' };
    SDL_Texture *labelTexture = getTextTexture(renderer, label, font, fore, back);
    SDL_Rect labelRect = { 420, 30, 400, 60 };
    drawText(renderer, labelTexture, labelRect);
    SDL_DestroyTexture(labelTexture);
    
    for (int i = 0; i < buttonCount; i++) {
        SDL_Texture *textTexture = getTextTexture(renderer, buttons[i].text, font, fore, back);
        drawText(renderer, textTexture, buttons[i].rect);
        SDL_DestroyTexture(textTexture);
    }
    
    SDL_RenderPresent(renderer);
}
int chooseGameMode(SDL_Renderer *renderer, TTF_Font* font, SDL_Texture *fonTexture)
{
    // Определяем кнопки
    Button buttons[6] = {
        {{240, 120, 300, 150}, {'3', 'x', '2'}},
        {{660, 120, 300, 150}, {'4', 'x', '3'}},
        {{240, 320, 300, 150}, {'5', 'x', '4'}},
        {{660, 320, 300, 150}, {'6', 'x', '5'}},
        {{240, 520, 300, 150}, {'8', 'x', '7'}},
        {{660, 520, 300, 150}, {'9', 'x', '8'}}
    };

    SDL_RenderCopy(renderer, fonTexture, NULL, NULL);
    drawChooseButtons(renderer, font, buttons, 6);
    
    bool quit = false;
    SDL_Event event;
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) {
                quit = true;
                SDL_Quit();
            }
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
            {
                for (int i = 0; i < 6; i++)
                {
                    if (Hitting(event.button.x, event.button.y, buttons[i].rect))
                    {
                        if(Data.music == true)
                        {
                            loadClickSound();
                            SDL_Delay(500);
                        }
                        return i + 1;
                    }
                }
            }
        }
    }
}
void clearCards()
{
    for(int i = 0; i < 72; i++)
    {
        Cards[i].click = false;
        Cards[i].found = false;
        Cards[i].question = true;
        Cards[i].num = -1;
        if(Cards[i].picture != NULL)
        {
            SDL_DestroyTexture(Cards[i].picture);
            Cards[i].picture = NULL;
        }
        Cards[i].x = 0; Cards[i].y = 0; Cards[i].w = 0; Cards[i].h = 0;
    }
}
void clearPictures()
{
    for (int i = 0; i < 36; i++) {
        if (Pictures[i].picture != NULL) {
            SDL_DestroyTexture(Pictures[i].picture);
            Pictures[i].picture = NULL;
        }
        Pictures[i].flag = false;
    }
}
void drawCardsBack(SDL_Renderer *renderer, SDL_Texture *fonTexture, int gameMode)
{
    int rows, cols;
    switch(gameMode)
    {
    case 1:
        rows = 3; cols = 2;
        paddingX = 110;
        paddingY = 30;
        areaX = 250;
        areaY = 100;
        areaWidth = 700;
        areaHeight = 520;
        COUNT_CARDS = 6;
        break;
    case 2:
        rows = 4; cols = 3;
        paddingX = 70;
        paddingY = 10;
        areaX = 50;
        areaY = 70;
        areaWidth = 1080;
        areaHeight = 630;
        COUNT_CARDS = 12;
        break;
    case 3:
        rows = 5; cols = 4;
        paddingX = 50;
        paddingY = 10;
        areaX = 50;
        areaY = 70;
        areaWidth = 1080;
        areaHeight = 630;
        COUNT_CARDS = 20;
        break;
    case 4:
        rows = 6; cols = 5;
        paddingX = 20;
        paddingY = 10;
        areaX = 50;
        areaY = 70;
        areaWidth = 1080;
        areaHeight = 630;
        COUNT_CARDS = 30;
        break;
    case 5:
        rows = 8; cols = 7;
        paddingX = 20;
        paddingY = 10;
        areaX = 50;
        areaY = 70;
        areaWidth = 1080;
        areaHeight = 630;
        COUNT_CARDS = 56;
        break;
    case 6:
        rows = 9; cols = 8;
        paddingX = 15;
        paddingY = 5;
        areaX = 50;
        areaY = 70;
        areaWidth = 1080;
        areaHeight = 650;
        COUNT_CARDS = 72;
        break;
    }

    int cardWidth = (areaWidth - paddingX * (cols - 1)) / cols;
    int cardHeight = (areaHeight - paddingY * (rows - 1)) / rows;

    
    SDL_Surface *backCard = SDL_LoadBMP("backCard.bmp");
    SDL_Texture *backCardTexture = SDL_CreateTextureFromSurface(renderer, backCard);
    SDL_FreeSurface(backCard);
    SDL_Surface *question = SDL_LoadBMP("question.bmp");
    SDL_Texture *questionTexture = SDL_CreateTextureFromSurface(renderer, question);
    SDL_FreeSurface(question);
    
    int temp = 0;
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            SDL_Rect cardRect;
            cardRect.x = areaX + j * (cardWidth + paddingX);
            cardRect.y = areaY + i * (cardHeight + paddingY);
            cardRect.w = cardWidth;
            cardRect.h = cardHeight;
            Cards[temp].x = cardRect.x;Cards[temp].y = cardRect.y;Cards[temp].w = cardRect.w;Cards[temp].h = cardRect.h;
            if(Cards[temp].click == false)SDL_RenderCopy(renderer, backCardTexture, NULL, &cardRect);
            if(Cards[temp].question == true)SDL_RenderCopy(renderer, questionTexture, NULL, &cardRect);
            temp++;
        }
    }
    SDL_DestroyTexture(backCardTexture);
}
void drawCard(SDL_Renderer *renderer, int cardIndex, int gameMode)
{
    SDL_Rect temp = {Cards[cardIndex].x, Cards[cardIndex].y, Cards[cardIndex].w, Cards[cardIndex].h};
    SDL_RenderCopy(renderer, Cards[cardIndex].picture, NULL, &temp);
    SDL_RenderPresent(renderer);
}
void fillCardsWithImages(SDL_Renderer *renderer, int gameMode)
{
    vector<int> imageIndices;

    for (int i = 0; i < 36; ++i)
    {
        imageIndices.push_back(i);
    }
    random_shuffle(imageIndices.begin(), imageIndices.end());

    int pairsNeeded;
    switch(gameMode)
    {
    case 1:
        pairsNeeded = 3;
        break;
    case 2:
        pairsNeeded = 6;
        break;
    case 3:
        pairsNeeded = 10;
        break;
    case 4:
        pairsNeeded = 15;
        break;
    case 5:
        pairsNeeded = 28;
        break;
    case 6:
        pairsNeeded = 36;
        break;
    }
    for (int i = 0; i < pairsNeeded; ++i)
    {
        int imageIndex = imageIndices[i];
        
        Cards[i * 2].picture = Pictures[imageIndex].picture;
        Cards[i * 2 + 1].picture = Pictures[imageIndex].picture;
        
        Cards[i * 2].num = i;
        Cards[i * 2 + 1].num = i;
    }

    random_shuffle(Cards, Cards + pairsNeeded * 2);
}
void gamePlay(SDL_Renderer *renderer, TTF_Font* font, SDL_Texture *fonTexture, int choose)
{
    int startTime = time(NULL);
    SDL_RenderCopy(renderer, fonTexture, NULL, NULL);
    drawCardsBack(renderer, fonTexture, choose);
    SDL_RenderPresent(renderer);
    char recordTime[20] = "Best time:";
    char bestTime[20];
    _itoa_s(atoi(Data.bestTime[choose-1].c_str()),bestTime, 10);
    int count = 0, first = -1, second = -1;
    int foundPairs = 0;
    bool quit = false;
    SDL_Event event;
    SDL_Color fore = { 255, 215, 0 };
    SDL_Color back = { 255, 250, 205};
    SDL_Rect bestTtime = {200, 0, 50, 70};
    SDL_Texture *bestTimeTexture = getTextTexture(renderer, bestTime, font, fore, back);
    drawText(renderer, bestTimeTexture, bestTtime);
    SDL_DestroyTexture(bestTimeTexture);
    SDL_Texture *bestTimeTextTexture = getTextTexture(renderer, recordTime, font, fore, back);
    SDL_Rect bestTimeTextRect = {0,0,200,70};
    drawText(renderer, bestTimeTextTexture, bestTimeTextRect);
    SDL_DestroyTexture(bestTimeTextTexture);
    while (!quit)
    {
        char text[6];
        int timeNow = time(NULL);
        int yourTime = timeNow - startTime;
        _itoa_s(yourTime, text, 10);
        SDL_Texture *timeTexture = getTextTexture(renderer, text, font, fore, back);
        SDL_Rect nowTimeRect = {1130, 0, 50, 50};
        drawText(renderer, timeTexture, nowTimeRect);
        SDL_DestroyTexture(timeTexture);
        SDL_RenderPresent(renderer); 
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
                SDL_Quit();
            }
            if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
            {
                int x = event.button.x;
                int y = event.button.y;
                
                for (int i = 0; i < COUNT_CARDS; ++i)
                {
                    if (Hitting(x, y, {Cards[i].x, Cards[i].y, Cards[i].w, Cards[i].h}) && !Cards[i].click)
                    {
                        if(Data.music == true)
                        {
                            clickCardSound();
                        }
                        Cards[i].click = true;
                        Cards[i].question = false;
                        drawCard(renderer, i, choose);
                        SDL_RenderPresent(renderer);
                        
                        if (count == 0)
                        {
                            first = i;
                            count++;
                        }
                        else if (count == 1)
                        {
                            second = i;
                            count = 0;

                            if (Cards[first].num == Cards[second].num)
                            {
                                if(!(foundPairs+1 == COUNT_CARDS / 2))
                                {
                                    if(Data.music == true)
                                    {
                                        foundPairSound();
                                    }
                                }
                                foundPairs++;
                                if (foundPairs == COUNT_CARDS / 2)
                                {
                                    if(Data.music == true)
                                    {
                                        loadWinSound();
                                    }
                                    if(yourTime < atoi(Data.bestTime[choose-1].c_str()))
                                    {
                                        char temp[20];
                                        _itoa_s(yourTime, temp, 10);
                                        Data.bestTime[choose-1] = temp;
                                        clearFile("data.txt");
                                        writeInFile("data.txt");
                                    }
                                    SDL_Delay(1500);
                                    return;
                                }
                            }
                            else
                            {
                                if(Data.music == true)
                                {
                                    notFoundPairSound();
                                }
                                SDL_Delay(700);
                                Cards[first].click = false;
                                Cards[first].question = false;
                                Cards[second].click = false;
                                Cards[second].question = false;
                            }
                            drawCardsBack(renderer, fonTexture, choose);
                            SDL_RenderPresent(renderer);
                        }
                    }
                }
            }
        }
    }
    
    SDL_Delay(500);
}