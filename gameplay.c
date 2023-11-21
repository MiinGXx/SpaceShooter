#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 700
#define TICK_INTERVAL (1)

// Timer function
void updateTime(int time) {
    time = SDL_GetTicks(); 
}

// Render timer
void renderTimer(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, int time) {
    // Convert time to seconds
    int seconds = time / 1000;

    // Format the time as a string
    char timeString[10];
    sprintf(timeString, "%d sec", seconds);

    // Render the time string
    SDL_Surface * surface = TTF_RenderText_Solid(font, timeString, color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_Rect rect = {10, 10, surface->w, surface->h};
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}

// Check collision between two rectangles (for enenmy ship and player ship)
bool checkCollision(SDL_Rect a, SDL_Rect b) {
    // The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    // Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    // Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    // If any of the sides from A are outside of B
    if (bottomA <= topB) {
        return false;
    }
    if (topA >= bottomB) {
        return false;
    }
    if (rightA <= leftB) {
        return false;
    }
    if (leftA >= rightB) {
        return false;
    }
    // If none of the sides from A are outside B
    return true;
}

// render player lives
void renderPlayerLives(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, int lives) {
    // Format the lives as a string
    char livesString[10];
    sprintf(livesString, "Lives: %d", lives);

    // Render the lives string
    SDL_Surface * surface = TTF_RenderText_Solid(font, livesString, color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_Rect rect = {10, 50, surface->w, surface->h};
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}

// render base lives
void renderBaseLives(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, int lives) {
    // Format the lives as a string
    char livesString[10];
    sprintf(livesString, "Base: %d HP", lives);

    // Render the lives string
    SDL_Surface * surface = TTF_RenderText_Solid(font, livesString, color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_Rect rect = {10, 75, surface->w, surface->h};
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}

