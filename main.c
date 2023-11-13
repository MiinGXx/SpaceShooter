#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#define SCREEN_WIDTH 750
#define SCREEN_HEIGHT 900

// =====================================================
// render text
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
// =====================================================

// main program 
int main(int argc, char ** argv) {
    bool quit = false;
    SDL_Event event;

    // SDL Init
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    Mix_Init(MIX_INIT_MP3);
    TTF_Init();

    // Text Related

	TTF_Font *font = TTF_OpenFont("VISITOR.ttf", 25);
	SDL_Color colorRED = {255, 0, 0};
    SDL_Color colorGREEN = {0, 255, 0};
    SDL_Color colorBLUE = {0, 0, 255};
    SDL_Color colorWHITE = {255, 255, 255};
 
    // Window and Renderer
    SDL_Window * window = SDL_CreateWindow("Space Shooter v0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    
 
    
    while (!quit)
    {
        // Event Polls
        if(SDL_PollEvent(&event) > 0){
            switch (event.type){
                case SDL_QUIT:
                    quit = true;
                    break;
			}
       }

        // Set Background color
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render Disclaimer
        renderDisclaimerTitle(renderer, font, colorRED, "Disclaimer:", 250);
        renderDisclaimerContent(renderer, font, colorWHITE, "This game serves as a project", 350);
        renderDisclaimerContent(renderer, font, colorWHITE, "for educational purposes.", 380);

        renderDisclaimerContent(renderer, font, colorWHITE, "All assets used in this game", 450);
        renderDisclaimerContent(renderer, font, colorWHITE, "are not owned by the developer.", 480);

        renderDisclaimerContent(renderer, font, colorWHITE, "Press SPACEBAR to continue", 600);


        SDL_RenderPresent(renderer);
    }


    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
	TTF_Quit();
    
    IMG_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
 
    return 0;
}