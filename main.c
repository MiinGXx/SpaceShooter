#include <stdio.h>
#include <stdlib.h> // For rand()
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#define SCREEN_WIDTH 650
#define SCREEN_HEIGHT 775
#define TICK_INTERVAL (1000 / 60)

int time = 0;

typedef struct {
    float enemyX;
    float enemyY;
    float enemySpeed;
} EnemyShip;

typedef struct {
    float playerProjectileX;
    float playerProjectileY;
    float playerProjectileSpeed;
    bool playerProjectileActive;  // True if projectile is active, false if not
} PlayerProjectile;

#define maxEnemyShips 5
EnemyShip enemyShips[maxEnemyShips];

#define maxPlayerProjectiles 15
PlayerProjectile playerProjectiles[maxPlayerProjectiles];

int lastProjectileTime = 0;  // Time of last projectile fired
#define PROJECTILE_COOLDOWN 750  // 750 milliseconds between each projectile

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

// render playerProjectile
void shootPlayerProjectile (int X, int Y) {
    for (int i = 0; i < maxPlayerProjectiles; ++i) {
        if (!playerProjectiles[i].playerProjectileActive) {
            playerProjectiles[i].playerProjectileActive = true;
            playerProjectiles[i].playerProjectileX = X + 22.5;
            playerProjectiles[i].playerProjectileY = Y;
            playerProjectiles[i].playerProjectileSpeed = 0.125;
            break;
        }
    }
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
    Mix_Chunk *pewSFX = Mix_LoadWAV("sounds/pewSFX.wav");
    Mix_Chunk *explosionSFX = Mix_LoadWAV("sounds/boomSFX.wav");
    Mix_VolumeMusic(MIX_MAX_VOLUME / 10); // Set volume to 10%
    Mix_VolumeChunk(hoverSFX, MIX_MAX_VOLUME / 10); // Set volume to 10%
    Mix_VolumeChunk(pewSFX, MIX_MAX_VOLUME / 15); // Set volume to 10%
    Mix_VolumeChunk(explosionSFX, MIX_MAX_VOLUME / 15); // Set volume to 10%

    // Window and Renderer
    SDL_Window * window = SDL_CreateWindow("Space Shooter v0.3", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    
    // Load All Sprite
    SDL_Surface * playerShip = IMG_Load("media/PlayerShipSprite.png");
    SDL_Surface * enemyShip = IMG_Load("media/AlienShipSprite.png");
    SDL_Surface * playerProjectile = IMG_Load("media/playerProjectile.png");

    // Loac Surface
    SDL_Texture * playerShipTexture = SDL_CreateTextureFromSurface(renderer, playerShip);
    SDL_Texture * enemyShipTexture = SDL_CreateTextureFromSurface(renderer, enemyShip);
    SDL_Texture * playerProjectileTexture = SDL_CreateTextureFromSurface(renderer, playerProjectile);

    // Clear Sprite
    SDL_FreeSurface(playerShip);
    SDL_FreeSurface(enemyShip);
    SDL_FreeSurface(playerProjectile);

    Mix_PlayMusic(bgm, -1);

    // Initialize variables
    // bool showDisclaimer = true;
    bool showDisclaimer = false;

    bool displayingMENU = false;
    bool confirmExit = false;
    bool escapePressed = false;
    // bool gameStart = false;
    bool gameStart = true;
    bool gameOver = false;
    int mouseX, mouseY;
    float playerX = 300;
    float playerY = 700;

    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;

    bool collision = false;

    bool fireProjectile = false;

    float speed = 0.1;

    // Initialize enemy ships
    for (int i = 0; i < maxEnemyShips; ++i) {
        // Generate random x position for enemy ship
        enemyShips[i].enemyX = rand() % (SCREEN_WIDTH - 50);
        enemyShips[i].enemyY = i * -100;  // Spawn at different y position based on index
        enemyShips[i].enemySpeed = 0.025;  // Adjust speed as needed

        // debug enemy ship position
        printf("Enemy Ship %d: X: %f, Y: %f\n", i, enemyShips[i].enemyX, enemyShips[i].enemyY);
    }

    // Initialize player projectiles
    for (int i = 0; i < maxPlayerProjectiles; ++i) {
        playerProjectiles[i].playerProjectileActive = false;
    }

// Main Loop 
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
                    if (event.key.keysym.sym == SDLK_SPACE && showDisclaimer) {
                        showDisclaimer = false;
                    }
                    break;

                case SDL_MOUSEMOTION:
                    // Get mouse coordinates
                    SDL_GetMouseState(&mouseX, &mouseY);
                    break;
            }
        }
        static bool spacePressedPrevFrame = false;

        // Keyboard input for player ship movement
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

        // Check if spacebar was pressed and the cooldown has passed
        if (state[SDL_SCANCODE_SPACE] && (time - lastProjectileTime > PROJECTILE_COOLDOWN)) {
            // Fire projectile
            Mix_PlayChannel(-1, pewSFX, 0);
            shootPlayerProjectile(playerX, playerY);
            lastProjectileTime = time;
        } else if (!state[SDL_SCANCODE_SPACE]) {
            // Reset the cooldown if spacebar is not pressed
            lastProjectileTime = 0;
        }

        // Update the flag for the next frame
        spacePressedPrevFrame = state[SDL_SCANCODE_SPACE];

        // Update enemy ship positions
        for (int i = 0; i < maxEnemyShips; ++i) {
            enemyShips[i].enemyY += enemyShips[i].enemySpeed;

            // Reset enemy ship position if it goes off screen
            if (enemyShips[i].enemyY > SCREEN_HEIGHT) {
                enemyShips[i].enemyX = rand() % (SCREEN_WIDTH - 50);  // Spawn at random x position
                enemyShips[i].enemyY = 0;  // Spawn at top of screen
            }

            // Check for collision with player ship
            SDL_Rect playerShipRect = {playerX, playerY, 50, 50};
            SDL_Rect enemyShipRect = {enemyShips[i].enemyX, enemyShips[i].enemyY, 50, 50};
            if (checkCollision(playerShipRect, enemyShipRect)) {
                printf("Collision detected!\n");
                gameOver = true;  // Set game over to true (Display Game Over screen)
            }
        }
        
        // Update player projectiles
        for (int i = 0; i < maxPlayerProjectiles; ++i) {
            if (playerProjectiles[i].playerProjectileActive) {
                playerProjectiles[i].playerProjectileY -= playerProjectiles[i].playerProjectileSpeed;

                // Reset player projectile position if it goes off screen
                if (playerProjectiles[i].playerProjectileY < 0) {
                    playerProjectiles[i].playerProjectileActive = false;
                }

                // Check for collision with enemy ships
                SDL_Rect playerProjectileRect = {playerProjectiles[i].playerProjectileX, playerProjectiles[i].playerProjectileY, 5, 5};
                for (int j = 0; j < maxEnemyShips; ++j) {
                    SDL_Rect enemyShipRect = {enemyShips[j].enemyX, enemyShips[j].enemyY, 50, 50};
                    if (checkCollision(playerProjectileRect, enemyShipRect)) {
                        Mix_PlayChannel(-1, explosionSFX, 0);
                        printf("Enemy ship %d destroyed!\n", j);
                        enemyShips[j].enemyX = rand() % (SCREEN_WIDTH - 50);  // Spawn at random x position
                        enemyShips[j].enemyY = 0;  // Spawn at top of screen
                        playerProjectiles[i].playerProjectileActive = false;
                    }
                }
            }
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

            //display and move enemy ships
            for (int i = 0; i < maxEnemyShips; ++i) {
                SDL_Rect enemyShipRect;
                enemyShipRect.x = enemyShips[i].enemyX;
                enemyShipRect.y = enemyShips[i].enemyY;
                enemyShipRect.w = 50;
                enemyShipRect.h = 50;
                SDL_RenderCopy(renderer, enemyShipTexture, NULL, &enemyShipRect);
            }

            //display player ship
            SDL_Rect playerShipRect;
            playerShipRect.x = playerX;
            playerShipRect.y = playerY;
            playerShipRect.w = 50;
            playerShipRect.h = 50;
            SDL_RenderCopy(renderer, playerShipTexture, NULL, &playerShipRect);
            
            // Render active player projectiles
            for (int i = 0; i < maxPlayerProjectiles; ++i) {
                if (playerProjectiles[i].playerProjectileActive) {
                    SDL_Rect playerProjectileRect = {playerProjectiles[i].playerProjectileX, playerProjectiles[i].playerProjectileY, 5, 5};
                    SDL_RenderCopy(renderer, playerProjectileTexture, NULL, &playerProjectileRect);
                }
            }
            
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
    Mix_FreeChunk(pewSFX);
    Mix_FreeChunk(explosionSFX);
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
 
    return 0;
}