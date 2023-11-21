#ifndef RENDERING_H
#define RENDERING_H

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

void renderDisclaimerTitle(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y);
void renderDisclaimerContent(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y);

void renderMainMenuTitle(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y);
void renderStartBtn(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y);
void renderScoreboardBtn(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y);

void renderConfirmExitTitle(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y);
void renderConfirmExit(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y);
void renderConfirmExitBtn(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y);
void renderDeclineExitBtn(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y);

void renderGameOverTitle(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y);
void renderGameOverContent(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y, int w);
void renderTimeSurvived(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, int time, int y);
void renderEnemyShipDestroyed(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, int enemyShipDestroyed, int y);
void renderScore(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, int score, int y);
void renderRetryBtn(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y);
void renderExitBtn(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y);

void renderScoreboardTitle(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y);
void renderScoreboardContent(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y, int w);
void renderBackBtn(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y);
void renderLeftBtn(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, int y);
void renderRightBtn(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, int y);
void renderHistoryBtn(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, int y);
void renderTopBtn(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, int y);

#endif