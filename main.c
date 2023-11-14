#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#define SCREEN_WIDTH 650
#define SCREEN_HEIGHT 775
#define TICK_INTERVAL (1000 / 60)

int time = 0;

// =====================================================
// RENDERING FUNCTIONS
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
// Main Menu Content
// Main Menu Title
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
// Main Menu Buttons
void renderMainMenuBtn(SDL_Renderer * renderer, TTF_Font * font, SDL_Color color, char * text, int y) {
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

// confirmExit 
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

// Gameplay Screen
// Timer function
void updateTime() {
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

    // Audio Related
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Music *bgm = Mix_LoadMUS("sounds/Mountain Trials.mp3");
    Mix_Chunk *hoverSFX = Mix_LoadWAV("sounds/hover.wav");
    Mix_VolumeMusic(MIX_MAX_VOLUME / 10); // Set volume to 10%

    // Window and Renderer
    SDL_Window * window = SDL_CreateWindow("Space Shooter v0.2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    
    // Load All Sprite
    SDL_Surface * playerShip = IMG_Load("media/PlayerShipSprite.png");
    SDL_Surface * enemyShip = IMG_Load("media/EnemyShipSprite.png");

    // Loac Surface
    SDL_Texture * playerShipTexture = SDL_CreateTextureFromSurface(renderer, playerShip);
    SDL_Texture * enemyShipTexture = SDL_CreateTextureFromSurface(renderer, enemyShip);

    // Clear Sprite
    SDL_FreeSurface(playerShip);
    SDL_FreeSurface(enemyShip);

    // Mix_PlayMusic(bgm, -1);

    // Initialize variables
    // bool showDisclaimer = true;
    bool showDisclaimer = false;

    bool displayingMENU = false;
    bool confirmExit = false;
    bool escapePressed = false;
    // bool gameStart = false;
    bool gameStart = true;
    int mouseX, mouseY;
    float playerX = 300;
    float playerY = 700;

    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;

    float speed = 0.1;


    while (!quit)
    {
        // Event Polls
        if(SDL_PollEvent(&event) > 0){
            switch (event.type){
                case SDL_QUIT:
                    quit = true;
                    break;

                case SDL_KEYDOWN:
                    // if "esc" button is pressed, display exit confirmation screen
                    if ((event.key.keysym.sym == SDLK_ESCAPE) && displayingMENU) {
                        confirmExit = true;
                    }
                    if (event.key.keysym.sym == SDLK_SPACE) {
                        showDisclaimer = false;
                    }

                case SDL_MOUSEMOTION:
                    // Get mouse coordinates
                    SDL_GetMouseState(&mouseX, &mouseY);
                    printf("Mouse coordinates: (%d, %d)\n", mouseX, mouseY);
                    break;
            }
        }

        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_LEFT] && gameStart) {
            left = true;
        } else {
            left = false;
        }
        if (state[SDL_SCANCODE_RIGHT] && gameStart) {
            right = true;
        } else {
            right = false;
        }
        if (state[SDL_SCANCODE_UP] && gameStart) {
            up = true;
        } else {
            up = false;
        }
        if (state[SDL_SCANCODE_DOWN] && gameStart) {
            down = true;
        } else {
            down = false;
        }


        // Set Background color
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black background
        SDL_RenderClear(renderer);

        // Render Disclaimer
        // if (showDisclaimer) {
        //     renderDisclaimerTitle(renderer, font, colorRED, "Disclaimer:", 200);
        //     renderDisclaimerContent(renderer, font, colorWHITE, "This game serves as a project", 300);
        //     renderDisclaimerContent(renderer, font, colorWHITE, "for educational purposes.", 330);

        //     renderDisclaimerContent(renderer, font, colorWHITE, "All assets used in this game", 400);
        //     renderDisclaimerContent(renderer, font, colorWHITE, "are not owned by the developer.", 430);

        //     renderDisclaimerContent(renderer, font, colorWHITE, "Press SPACEBAR to continue", 500);

        //     displayingMENU = true;
        // }

        // Render Main Menu Screen
        // if (!showDisclaimer && displayingMENU) {
            // Menu title
        //     renderMainMenuTitle(renderer, font, colorWHITE, "SPACE", 175);
        //     renderMainMenuTitle(renderer, font, colorWHITE, "SHOOTER", 250);

        //     // Menu buttons
        //     // if mouse hover over 'START', it will turn red, or else it will be white
        //     if (mouseX >= 275 && mouseX <= 375 && mouseY >= 400 && mouseY <= 450) {
        //         renderMainMenuBtn(renderer, font, colorRED, "START", 400);
        //         if (event.type == SDL_MOUSEBUTTONDOWN) {
        //             printf("Start Button Pressed\n");
        //             gameStart = true;
        //             displayingMENU = false;
        //         }
        //     } else { 
        //         renderMainMenuBtn(renderer, font, colorWHITE, "START", 400);
        //     }
        // }

        // Render Exit confirmation screen
        // if (confirmExit) {
        //     SDL_RenderClear(renderer);
        //     renderConfirmExit(renderer, font, colorWHITE, "Are you sure you want to exit?", 350);
        //     // if mouse hover over 'YES', it will turn red, or else it will be white
        //     if (mouseX >= 275 && mouseX <= 375 && mouseY >= 400 && mouseY <= 450) {
        //         renderConfirmExitBtn(renderer, font, colorRED, "YES", 400);
        //         if (event.type == SDL_MOUSEBUTTONDOWN) {
        //             quit = true;
        //         }
        //     } else {
        //         renderConfirmExitBtn(renderer, font, colorWHITE, "YES", 400);
        //     }
        //     // if mouse hover over 'NO', it will turn red, or else it will be white
        //     if (mouseX >= 275 && mouseX <= 375 && mouseY >= 450 && mouseY <= 500) {
        //         renderDeclineExitBtn(renderer, font, colorRED, "NO", 450);
        //         if (event.type == SDL_MOUSEBUTTONDOWN) {
        //             confirmExit = false;
        //         }
        //     } else {
        //         renderDeclineExitBtn(renderer, font, colorWHITE, "NO", 450);
        //     }
        // }

        if (gameStart) {
            //display timer
            updateTime();
            renderTimer(renderer, font, colorWHITE, time);

            // Keyboard movement for player ship
            if (left) {
                playerX -= speed;
            }
            if (right) {
                playerX += speed;
            }
            if (up) {
                playerY -= speed;
            }
            if (down) {
                playerY += speed;
            }
            // Restrict player ship movement within windows
            if (playerX < 0) {
                playerX = 0;
            }
            if (playerX > SCREEN_WIDTH - 50) {
                playerX = SCREEN_WIDTH - 50;
            }
            if (playerY < 0) {
                playerY = 0;
            }
            if (playerY > SCREEN_HEIGHT - 50) {
                playerY = SCREEN_HEIGHT - 50;
            }

            //display player ship
            SDL_Rect playerShipRect;
            playerShipRect.x = playerX;
            playerShipRect.y = playerY;
            playerShipRect.w = 50;
            playerShipRect.h = 50;
            SDL_RenderCopy(renderer, playerShipTexture, NULL, &playerShipRect);
        }

        SDL_RenderPresent(renderer);
    }


    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
	TTF_Quit();
    
    IMG_Quit();
    Mix_FreeMusic(bgm);
    Mix_FreeChunk(hoverSFX);
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
 
    return 0;
}