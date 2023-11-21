#ifndef GUI_H
#define GUI_H

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

typedef struct {
    int gameNumber;
    int timeSurvived;
    int enemyShipsDestroyed;
    int score;
} ScoreEntry;

void renderDisclaimer(SDL_Renderer * renderer, TTF_Font * font, SDL_Color colorRED, SDL_Color colorWHITE);
void renderMenu(SDL_Renderer* renderer, TTF_Font* font, SDL_Color colorWHITE, SDL_Color colorRED, int mouseX, int mouseY, SDL_Event event, bool* gameStart, bool* displayingMENU, bool* displayingSCOREBOARD);
void renderTopScoreboard(SDL_Renderer* renderer, TTF_Font* font, SDL_Color colorWHITE, int currentPage, int totalPages);
void renderTimeScoreboard(SDL_Renderer* renderer, TTF_Font* font, SDL_Color colorWHITE, int currentPage, int totalPages);
void handleButtonClicks(SDL_Renderer* renderer, TTF_Font* font, SDL_Color colorRED, SDL_Color colorWHITE, int mouseX, int mouseY, SDL_Event event, int* currentPage, bool* displayingSCOREBOARD, bool* displayingMENU, bool* ScoreboardTIME, bool* ScoreboardTOP, int* lineNumber);
void renderExitConfirmation(SDL_Renderer* renderer, TTF_Font* font, SDL_Color colorWHITE, SDL_Color colorRED, int mouseX, int mouseY, SDL_Event event, bool* quit, bool* confirmExit);
void renderGameOverScreen(SDL_Renderer* renderer, TTF_Font* font, SDL_Color colorWHITE, SDL_Color colorRED, int time, int enemyShipDestroyed, int score);

#endif