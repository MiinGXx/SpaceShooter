#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 700

// Disclaimer Title
void renderDisclaimerTitle(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y) {
    SDL_Surface * surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_Rect rect;
    int centerX = (SCREEN_WIDTH - 300) / 2;
    rect.x = centerX;
    rect.y = y;
    rect.w = 300;
    rect.h = 50;
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}

// Disclaimer Content
void renderDisclaimerContent(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y) {
    SDL_Surface * surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_Rect rect;
    int centerX = (SCREEN_WIDTH - 400) / 2;
    rect.x = centerX;
    rect.y = y;
    rect.w = 400;
    rect.h = 30;
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}

// Main menu title 
void renderMainMenuTitle(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y) {
    SDL_Surface * surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_Rect rect;
    int centerX = (SCREEN_WIDTH - 400) / 2;
    rect.x = centerX;
    rect.y = y;
    rect.w = 400;
    rect.h = 100;
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}

// Main menu start button
void renderStartBtn(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y) {
    SDL_Surface * surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_Rect rect;
    int centerX = (SCREEN_WIDTH - 100) / 2;
    rect.x = centerX;
    rect.y = y;
    rect.w = 100;
    rect.h = 50;
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}

// Main menu scoreboard button
void renderScoreboardBtn(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y) {
    SDL_Surface * surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect;
    int centerX = (SCREEN_WIDTH - 225) / 2;
    rect.x = centerX;
    rect.y = y;
    rect.w = 225;
    rect.h = 50;
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}

// Confirm Exit Title
void renderConfirmExitTitle(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y) {
    SDL_Surface * surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_Rect rect;
    int centerX = (SCREEN_WIDTH - 400) / 2;
    rect.x = centerX;
    rect.y = y;
    rect.w = 400;
    rect.h = 50;
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}

// Confirm Exit Content
void renderConfirmExit(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y) {
    SDL_Surface * surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_Rect rect;
    int centerX = (SCREEN_WIDTH - 400) / 2;
    rect.x = centerX;
    rect.y = y;
    rect.w = 400;
    rect.h = 30;
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}

// Confirm Exit Button
// confirmExitbtn
void renderConfirmExitBtn(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y) {
    SDL_Surface * surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_Rect rect;
    int centerX = (SCREEN_WIDTH - 100) / 2;
    rect.x = centerX;
    rect.y = y;
    rect.w = 100;
    rect.h = 50;
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}

// declineExitBtn
void renderDeclineExitBtn(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y) {
    SDL_Surface * surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_Rect rect;
    int centerX = (SCREEN_WIDTH - 100) / 2;
    rect.x = centerX;
    rect.y = y;
    rect.w = 100;
    rect.h = 50;
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}

// Game Over Title
void renderGameOverTitle(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y) {
    SDL_Surface * surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect;
    int centerX = (SCREEN_WIDTH - 400) / 2;
    rect.x = centerX;
    rect.y = y;
    rect.w = 400;
    rect.h = 50;
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}

// Game Over Content
void renderGameOverContent(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y, int w) {
    SDL_Surface * surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect;
    int centerX = (SCREEN_WIDTH - w) / 2;
    rect.x = centerX;
    rect.y = y;
    rect.w = w;
    rect.h = 30;
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}

// Time survived
void renderTimeSurvived(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, int time, int y) {
    // Convert time to seconds
    int seconds = time / 1000;

    // Format the time as a string
    char timeString[10];
    sprintf(timeString, "%d sec", seconds);

    // Render the time string
    SDL_Surface * surface = TTF_RenderText_Solid(font, timeString, color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_Rect rect;
    int centerX = (SCREEN_WIDTH - 100) / 2;
    rect.x = centerX;
    rect.y = y;
    rect.w = 100;
    rect.h = 30;
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}

// Enemy ship destroy count
void renderEnemyShipDestroyed(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, int enemyShipDestroyed, int y) {
    // Format the enemy ship destroyed as a string
    char enemyShipDestroyedString[10];
    sprintf(enemyShipDestroyedString, "a total of %d", enemyShipDestroyed);

    // Render the enemy ship destroyed string
    SDL_Surface * surface = TTF_RenderText_Solid(font, enemyShipDestroyedString, color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_Rect rect;
    int centerX = (SCREEN_WIDTH - 300) / 2;
    rect.x = centerX;
    rect.y = y;
    rect.w = 300;
    rect.h = 30;
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}

// Score
void renderScore(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, int score, int y) {
    // Format the score as a string
    char scoreString[10];
    sprintf(scoreString, "Score: %d", score);

    // Render the score string
    SDL_Surface * surface = TTF_RenderText_Solid(font, scoreString, color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_Rect rect;
    int centerX = (SCREEN_WIDTH - 200) / 2;
    rect.x = centerX;
    rect.y = y;
    rect.w = 200;
    rect.h = 50;
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}

// Retry button
void renderRetryBtn(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y) {
    SDL_Surface * surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect;
    int centerX = (SCREEN_WIDTH - 100) / 2;
    rect.x = centerX;
    rect.y = y;
    rect.w = 100;
    rect.h = 50;
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}

// Exit button
void renderExitBtn(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y) {
    SDL_Surface * surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect;
    int centerX = (SCREEN_WIDTH - 100) / 2;
    rect.x = centerX;
    rect.y = y;
    rect.w = 100;
    rect.h = 50;
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}

// Scoreboard Title
void renderScoreboardTitle(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y) {
    SDL_Surface * surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect;
    int centerX = (SCREEN_WIDTH - 300) / 2;
    rect.x = centerX;
    rect.y = y;
    rect.w = 300;
    rect.h = 50;
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}

// Scoreboard Content
void renderScoreboardContent(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y, int w) {
    SDL_Surface * surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect;
    int centerX = (SCREEN_WIDTH - w) / 2;
    rect.x = centerX;
    rect.y = y;
    rect.w = w;
    rect.h = 20;
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}

// Back button
void renderBackBtn(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y) {
    SDL_Surface * surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect;
    int centerX = (SCREEN_WIDTH - 150) / 2;
    rect.x = centerX;
    rect.y = y;
    rect.w = 150;
    rect.h = 50;
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}

// Left Button
void renderLeftBtn(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, int y) {
    SDL_Surface * surface = TTF_RenderText_Solid(font, "<", color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect;
    rect.x = 10;
    rect.y = y;
    rect.w = 50;
    rect.h = 50;
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}

// Right Button
void renderRightBtn(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, int y) {
    SDL_Surface * surface = TTF_RenderText_Solid(font, ">", color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect;
    rect.x = SCREEN_WIDTH - 60;
    rect.y = y;
    rect.w = 50;
    rect.h = 50;
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}

// History Button
void renderHistoryBtn(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, int y) {
    SDL_Surface * surface = TTF_RenderText_Solid(font, "Time", color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect;
    rect.x = 475;
    rect.y = y;
    rect.w = 60;
    rect.h = 20;
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}

// Top Score Button
void renderTopBtn(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, int y) {
    SDL_Surface * surface = TTF_RenderText_Solid(font, "Top", color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect;
    rect.x = 475;
    rect.y = y;
    rect.w = 60;
    rect.h = 20;
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}

