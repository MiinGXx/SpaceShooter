#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdbool.h>

void updateTime(int time);
void renderTimer(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, int time);
bool checkCollision(SDL_Rect a, SDL_Rect b);
void renderPlayerLives(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, int lives);
void renderBaseLives(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, int lives);

#endif 