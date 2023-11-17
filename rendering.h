#ifndef RENDERING_H
#define RENDERING_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

void renderDisclaimerTitle(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y);
void renderDisclaimerContent(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y);

void renderMainMenuTitle(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y);
void renderMainMenuBtn(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y);

void renderConfirmExitTitle(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y);
void renderConfirmExit(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y);
void renderConfirmExitBtn(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y);
void renderDeclineExitBtn(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y);

void renderGameOverTitle(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y);
void renderGameOverContent(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y, int w);
void renderTimeSurvived(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, int time, int y);
void renderEnemyShipDestroyed(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, int enemyShipDestroyed, int y);
void renderRetryBtn(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y);
void renderExitBtn(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y);

#endif