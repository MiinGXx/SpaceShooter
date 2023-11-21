#include <stdio.h>
#include <stdlib.h> // For rand()
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "rendering.h"
#include "gameplay.h"
#include "statistics.h"
#include "gui.h"

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 700
#define TICK_INTERVAL (1)

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

#define PROJECTILE_COOLDOWN 500  // 500 milliseconds between each projectile

// =====================================================
// GAMEPLAY FUNCTIONS
// assign playerProjectile coordinates
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

    // Audio Related
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Music *bgm = Mix_LoadMUS("sounds/Mountain Trials.mp3");
    Mix_Chunk *pewSFX = Mix_LoadWAV("sounds/pewSFX.wav");
    Mix_Chunk *explosionSFX = Mix_LoadWAV("sounds/boomSFX.wav");
    Mix_VolumeMusic(MIX_MAX_VOLUME / 10); // Set volume to 10%
    Mix_VolumeChunk(pewSFX, MIX_MAX_VOLUME / 15); // Set volume to 10%
    Mix_VolumeChunk(explosionSFX, MIX_MAX_VOLUME / 15); // Set volume to 10%

    // Window and Renderer
    SDL_Window * window = SDL_CreateWindow("Space Shooter v0.6", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
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

    // Initialize variables
    bool showDisclaimer = true;
    bool displayingMENU = false;
    bool displayingSCOREBOARD = false;
    bool ScoreboardTIME = true;
    bool ScoreboardTOP = false;
    bool confirmExit = false;
    bool escapePressed = false;
    bool gameStart = false;
    bool pauseGame = false;
    bool ingameMusic = false;
    bool gameOver = false;
    int mouseX, mouseY;
    float playerX = 275;
    float playerY = 600;

    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;

    bool collision = false;

    int lastProjectileTime = 0;  // Time of last projectile fired
    bool fireProjectile = false;

    float speed = 0.1;
    int frameTime = 5;

    int enemyShipDestroyed = 0;
    int playerLives = 3;
    int baseLives = 10;

    int time = 0;
    Uint32 startTime = 0;

    int currentPage = 1;
    int lineNumber;


    // Initialize enemy ships
    for (int i = 0; i < maxEnemyShips; ++i) {
        // Generate random x position for enemy ship
        enemyShips[i].enemyX = rand() % (SCREEN_WIDTH - 50);
        enemyShips[i].enemyY = i * -100;  // Spawn at different y position based on index
        enemyShips[i].enemySpeed = 0.025;  // Adjust speed as needed
    }
    // Initialize player projectiles
    for (int i = 0; i < maxPlayerProjectiles; ++i) {
        playerProjectiles[i].playerProjectileActive = false;
    }

// Main Loop 
    while (!quit)
    {
        int frameStartTime = SDL_GetTicks();
        float adjustedSpeed = speed * (frameTime / TICK_INTERVAL);

        // Event Polls
        if(SDL_PollEvent(&event) > 0){
            switch (event.type){
                case SDL_QUIT:
                    quit = true;
                    break;

                case SDL_KEYDOWN:
                    // if "esc" button is pressed, display exit confirmation screen
                    if (event.key.keysym.sym == SDLK_ESCAPE && displayingMENU) {
                        confirmExit = true;
                    }
                    if (event.key.keysym.sym == SDLK_SPACE && showDisclaimer) {
                        showDisclaimer = false;
                    }
                    if (event.key.keysym.sym == SDLK_ESCAPE && gameStart) {
                        pauseGame = true;
                    }
                    break;

                case SDL_MOUSEMOTION:
                    // Get mouse coordinates
                    SDL_GetMouseState(&mouseX, &mouseY);
                    break;
            }
        }

        bool spacePressedPrevFrame = false;
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
        if (state[SDL_SCANCODE_SPACE] && (time - lastProjectileTime > PROJECTILE_COOLDOWN) && gameStart) {
            // Fire projectile
            Mix_PlayChannel(-1, pewSFX, 0);
            shootPlayerProjectile(playerX, playerY);
            lastProjectileTime = time;
        } 
        // Update the flag for the next frame
        spacePressedPrevFrame = state[SDL_SCANCODE_SPACE];        

        // Set Background color
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black background
        SDL_RenderClear(renderer);

        // Render Disclaimer
        if (showDisclaimer) {
            renderDisclaimer(renderer, font, colorRED, colorWHITE);
            displayingMENU = true;
        }

        // Render Main Menu Screen
        if (!showDisclaimer && displayingMENU) {
            renderMenu(renderer, font, colorWHITE, colorRED, mouseX, mouseY, event, &gameStart, &displayingMENU, &displayingSCOREBOARD);
            startTime = SDL_GetTicks();
        }

        // Render Exit confirmation screen
        if (confirmExit) {
            renderExitConfirmation(renderer, font, colorWHITE, colorRED, mouseX, mouseY, event, &quit, &confirmExit);
        }

        // Render Scoreboard screen
        if (displayingSCOREBOARD) {
            int totalLines = checkNumberOfLines();
            int totalPages = totalLines / 10;

            if (ScoreboardTOP) {
                renderTopScoreboard(renderer, font, colorWHITE, currentPage, totalPages);
            } else if (ScoreboardTIME) {
                renderTimeScoreboard(renderer, font, colorWHITE, currentPage, totalPages);
            }
            
            // Handle Button Clicks
           handleButtonClicks(renderer, font, colorRED, colorWHITE, mouseX, mouseY, event, &currentPage, &displayingSCOREBOARD, &displayingMENU, &ScoreboardTIME, &ScoreboardTOP, &lineNumber);
        }

        if (gameStart) {
            // Play ingame bgm
            if (!ingameMusic) {
                startTime = SDL_GetTicks();
                // Mix_PlayMusic(bgm, -1);
                ingameMusic = true;
            }

            // display timer
            updateTime(time);
            renderTimer(renderer, font, colorWHITE, time);

            int frameStartTime = SDL_GetTicks();

            // display player ship lives
            renderPlayerLives(renderer, font, colorWHITE, playerLives);

            // display base lives
            renderBaseLives(renderer, font, colorWHITE, baseLives);

            // Keyboard movement for player ship
            handlePlayerMovement(left, right, up, down, &playerX, &playerY, adjustedSpeed);

            //display enemy ships
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

            // Update enemy ship positions
            for (int i = 0; i < maxEnemyShips; ++i) {
                enemyShips[i].enemyY += enemyShips[i].enemySpeed * (frameTime / TICK_INTERVAL);

                // Reset enemy ship position if it goes off screen
                if (enemyShips[i].enemyY > SCREEN_HEIGHT) {
                    // Play explosion sound effect
                    Mix_PlayChannel(-1, explosionSFX, 0);
                    // Reset enemy ship position
                    enemyShips[i].enemyX = rand() % (SCREEN_WIDTH - 50);  // Spawn at random x position
                    enemyShips[i].enemyY = -50;  // Spawn at top of screen
                    
                    // Decrease player lives
                    baseLives--;
                    printf("Base lives: %d HP\n", playerLives);

                    // Show game over screen when base lives reaches 0
                    if (baseLives <= 0) {
                        Mix_PlayChannel(-1, explosionSFX, 0);
                        printf("Game Over\n");
                        gameOver = true;  // Set game over to true (Display Game Over screen)
                        gameStart = false;  // Set game start to false (Stop rendering game screen)
                        // Record game statistics
                        recordGameStatistics(time, enemyShipDestroyed, calculateScore(time, enemyShipDestroyed));
                    }
                }

                // Check for collision with player ship
                SDL_Rect playerShipHitboxRect = {playerX + 5, playerY + 5, 40, 40};
                SDL_Rect enemyShipHitboxRect = {enemyShips[i].enemyX + 5, enemyShips[i].enemyY + 5, 40, 40};
                if (checkCollision(playerShipHitboxRect, enemyShipHitboxRect)) {
                    // Decrease player lives
                    playerLives--;
                    // Reset enemy ship position
                    enemyShips[i].enemyX = rand() % (SCREEN_WIDTH - 50);  // Spawn at random x position
                    enemyShips[i].enemyY = -50;  // Spawn at top of screen

                    printf("Player lives: %d\n", playerLives);
                    
                    // Show game over screen when player lives reaches 0
                    if (playerLives <= 0) {
                        Mix_PlayChannel(-1, explosionSFX, 0);
                        printf("Game Over\n");
                        gameOver = true;  // Set game over to true (Display Game Over screen)
                        gameStart = false;  // Set game start to false (Stop rendering game screen)
                        // Record game statistics
                        recordGameStatistics(time, enemyShipDestroyed, calculateScore(time, enemyShipDestroyed));
                    }
                }
            }
            
            // Update player projectiles
            for (int i = 0; i < maxPlayerProjectiles; ++i) {
                if (playerProjectiles[i].playerProjectileActive) {
                    playerProjectiles[i].playerProjectileY -= playerProjectiles[i].playerProjectileSpeed * (frameTime / TICK_INTERVAL);

                    // Deactivate player projectile if it goes off screen
                    if (playerProjectiles[i].playerProjectileY < 0) {
                        playerProjectiles[i].playerProjectileActive = false;
                    }

                    // Check for collision with enemy ships
                    SDL_Rect playerProjectileRect = {playerProjectiles[i].playerProjectileX, playerProjectiles[i].playerProjectileY, 5, 5};
                    for (int j = 0; j < maxEnemyShips; ++j) {
                        SDL_Rect enemyShipHitboxRect = {enemyShips[j].enemyX + 5, enemyShips[j].enemyY + 5, 40, 40};
                        if (checkCollision(playerProjectileRect, enemyShipHitboxRect)) {
                            Mix_PlayChannel(-1, explosionSFX, 0);
                            enemyShipDestroyed++; // Increment enemy ship destroyed counter
                            printf("Enemy ship destroyed: %d\n", enemyShipDestroyed);

                            // Reset enemy ship position
                            enemyShips[j].enemyX = rand() % (SCREEN_WIDTH - 50);  // Spawn at random x position
                            enemyShips[j].enemyY = -50;  // Spawn at top of screen
                            playerProjectiles[i].playerProjectileActive = false;
                        }
                    }
                }
            }

            // Calculate time elapsed
            time = SDL_GetTicks() - startTime;
        }

        // Render Game Over screen
        if (gameOver) {
            // Stop ingame bgm
            Mix_HaltMusic();

            // Render Game Over screen
            renderGameOverScreen(renderer, font, colorWHITE, colorRED, time, enemyShipDestroyed, calculateScore(time, enemyShipDestroyed));
            // Render Buttons
            // if mouse hover over 'RETRY', it will turn red, or else it will be white
            if (mouseX >= 275 && mouseX <= 375 && mouseY >= 450 && mouseY <= 500) {
                renderRetryBtn(renderer, font, colorRED, "RETRY", 450);
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    printf("Retry Button Pressed\n");
                    // =====================================================
                    // RESET EVERYTHING
                    // Reset variables
                    enemyShipDestroyed = 0;
                    playerLives = 3;
                    baseLives = 10;
                    gameStart = true;
                    gameOver = false;
                    // Reset enemy ships 
                    for (int i = 0; i < maxEnemyShips; ++i) {
                        // Generate random x position for enemy ship
                        enemyShips[i].enemyX = rand() % (SCREEN_WIDTH - 50);
                        enemyShips[i].enemyY = i * -100;  // Spawn at different y position based on index
                        enemyShips[i].enemySpeed = 0.025;  // Adjust speed as needed
                    }
                    //reset player ship
                    playerX = 275;
                    playerY = 600;
                    // Reset player projectiles
                    for (int i = 0; i < maxPlayerProjectiles; ++i) {
                        playerProjectiles[i].playerProjectileActive = false;
                    }
                    lastProjectileTime = 0;
                    // Reset timer
                    startTime = SDL_GetTicks();
                    // =====================================================
                }
            } else {
                renderRetryBtn(renderer, font, colorWHITE, "RETRY", 450);
            }
            // if mouse hover over 'EXIT', it will turn red, or else it will be white
            if (mouseX >= 275 && mouseX <= 375 && mouseY >= 500 && mouseY <= 550) {
                renderExitBtn(renderer, font, colorRED, "EXIT", 500);
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    printf("Exit Button Pressed\n");
                    // =====================================================
                    // RESET EVERYTHING
                    // Reset variables
                    enemyShipDestroyed = 0;
                    playerLives = 3;
                    baseLives = 10;
                    displayingMENU = true;
                    gameOver = false;
                    // Reset enemy ships
                    for (int i = 0; i < maxEnemyShips; ++i) {
                        // Generate random x position for enemy ship
                        enemyShips[i].enemyX = rand() % (SCREEN_WIDTH - 50);
                        enemyShips[i].enemyY = i * -100;  // Spawn at different y position based on index
                        enemyShips[i].enemySpeed = 0.025;  // Adjust speed as needed
                    }
                    //reset player ship
                    playerX = 275;
                    playerY = 600;
                    // Reset player projectiles
                    for (int i = 0; i < maxPlayerProjectiles; ++i) {
                        playerProjectiles[i].playerProjectileActive = false;
                    }
                    lastProjectileTime = 0;
                    // Reset timer
                    startTime = SDL_GetTicks();
                    // =====================================================
                }
            } else {
                renderExitBtn(renderer, font, colorWHITE, "EXIT", 500);
            }
        }

        SDL_RenderPresent(renderer);

        int frameTime = SDL_GetTicks() - frameStartTime;

        // Limit framerate to 60 FPS
        if (frameTime < TICK_INTERVAL) {
            SDL_Delay(TICK_INTERVAL - frameTime);
        }
    }


    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
	TTF_Quit();
    
    IMG_Quit();
    Mix_FreeMusic(bgm);
    Mix_FreeChunk(pewSFX);
    Mix_FreeChunk(explosionSFX);
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
 
    return 0;
}