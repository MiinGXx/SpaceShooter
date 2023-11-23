#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "gui.h"
#include "rendering.h"
#include "statistics.h"

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 700

// display disclaimer gui
void renderDisclaimer(SDL_Renderer * renderer, TTF_Font * font, SDL_Color colorRED, SDL_Color colorWHITE) {
    renderDisclaimerTitle(renderer, font, colorRED, "Disclaimer:", 200);
    renderDisclaimerContent(renderer, font, colorWHITE, "This game serves as a project", 300);
    renderDisclaimerContent(renderer, font, colorWHITE, "for educational purposes.", 330);
    renderDisclaimerContent(renderer, font, colorWHITE, "All assets used in this game", 400);
    renderDisclaimerContent(renderer, font, colorWHITE, "are not owned by the developer.", 430);
    renderDisclaimerContent(renderer, font, colorWHITE, "Press SPACEBAR to continue", 500);
}

// display main menu gui
void renderMenu(SDL_Renderer* renderer, TTF_Font* font, SDL_Color colorWHITE, SDL_Color colorRED, int mouseX, int mouseY, SDL_Event event, bool* gameStart, bool* displayingMENU, bool* displayingSCOREBOARD) {
    // render Menu title
    renderMainMenuTitle(renderer, font, colorWHITE, "SPACE", 175);
    renderMainMenuTitle(renderer, font, colorWHITE, "SHOOTER", 250);

    // Menu buttons
    // if mouse hover over 'START', it will turn red, or else it will be white
    if (mouseX >= 275 && mouseX <= 375 && mouseY >= 400 && mouseY <= 450) {
        renderStartBtn(renderer, font, colorRED, "START", 400);
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            printf("Start Button Pressed\n");
            *displayingMENU = false;
            *gameStart = true;
        }
    } else { 
        renderStartBtn(renderer, font, colorWHITE, "START", 400);
    }
    // if mouse hover over 'SCOREBOARD', it will turn red, or else it will be white
    if (mouseX >= 180 && mouseX <= 410 && mouseY >= 460 && mouseY <= 510) {
        renderScoreboardBtn(renderer, font, colorRED, "SCOREBOARD", 460);
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            printf("Scoreboard Button Pressed\n");
            *displayingMENU = false;
            *displayingSCOREBOARD = true;
        }
    } else {
        renderScoreboardBtn(renderer, font, colorWHITE, "SCOREBOARD", 460);
    }
}

// Comparison function for qsort
int compareScores(const void* a, const void* b) {
    ScoreEntry* scoreA = (ScoreEntry*)a;
    ScoreEntry* scoreB = (ScoreEntry*)b;

    return scoreB->score - scoreA->score;

}

// display full scoreboard gui (top score filter)
void renderTopScoreboard(SDL_Renderer* renderer, TTF_Font* font, SDL_Color colorWHITE, int currentPage, int totalPages) {
    FILE* file = fopen("game_statistics.txt", "r");
    if (file == NULL) {  // Check if file exists
        printf("Error opening file!\n");
        return;
    }

    char buffer[256];
    int lineNumber = 0;
    int linesPerPage = 20;
    int startY = 100;


    ScoreEntry scores[checkNumberOfLines()]; // Create array of scores with size equal to number of lines in file

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // Remove newline character
        buffer[strcspn(buffer, "\n")] = '\0';

        // Extract information from each line
        int gameNumber, timeSurvived, enemyShipsDestroyed, score;
        sscanf(buffer, "%d. Time Survived: %d Sec, Enemy Ships Destroyed: %d, Score: %d", &scores[lineNumber].gameNumber, &scores[lineNumber].timeSurvived, &scores[lineNumber].enemyShipsDestroyed, &scores[lineNumber].score);
        lineNumber++;
    }
    fclose(file); // Close file

    // Sort Scores in descending order
    qsort(scores, lineNumber, sizeof(ScoreEntry), compareScores);

    // Render scoreboard title
    renderScoreboardTitle(renderer, font, colorWHITE, "SCOREBOARD", 25);

    // Render scoreboard content
    for (int i = 0; i < lineNumber; ++i) {
        if (i >= (currentPage - 1) * linesPerPage && i < currentPage * linesPerPage) {
            char buffer[256];
            sprintf(buffer, "%d. Time Survived: %d Sec, Enemy Ships Destroyed: %d, Score: %d", scores[i].gameNumber, scores[i].timeSurvived, scores[i].enemyShipsDestroyed, scores[i].score);
            renderScoreboardContent(renderer, font, colorWHITE, buffer, startY, 550);
            startY += 25;
        }
    }
}

// display full scoreboard gui (time filter)
void renderTimeScoreboard(SDL_Renderer* renderer, TTF_Font* font, SDL_Color colorWHITE, int currentPage, int totalPages) {
    FILE* file = fopen("game_statistics.txt", "r");
    if (file == NULL) {  // Check if file exists
        printf("Error opening file!\n");
        return;
    }

    int linesPerPage = 20;
    int startY = 100;

    // Render scoreboard title
    renderScoreboardTitle(renderer, font, colorWHITE, "SCOREBOARD", 25);

    // Render scoreboard content
    char buffer[256];
    int lineNumber = 0;

    // Read file line by line and render each lines
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (lineNumber >= (currentPage - 1) * linesPerPage && lineNumber < currentPage * linesPerPage) {
            // Remove newline character
            buffer[strcspn(buffer, "\n")] = '\0';
            renderScoreboardContent(renderer, font, colorWHITE, buffer, startY, 550);
            startY += 25;
        }
        lineNumber++;
    }
    fclose(file); // Close file
}    

// display full exit confirmation gui
void renderExitConfirmation(SDL_Renderer* renderer, TTF_Font* font, SDL_Color colorWHITE, SDL_Color colorRED, int mouseX, int mouseY, SDL_Event event, bool* quit, bool* confirmExit) {
    SDL_RenderClear(renderer);
    renderConfirmExit(renderer, font, colorWHITE, "Are you sure you want to exit?", 200);
    // if mouse hover over 'YES', it will turn red, or else it will be white
    if (mouseX >= 275 && mouseX <= 375 && mouseY >= 300 && mouseY <= 350) {
        renderConfirmExitBtn(renderer, font, colorRED, "YES", 300);
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            *quit = true;
        }
    } else {
        renderConfirmExitBtn(renderer, font, colorWHITE, "YES", 300);
    }
    // if mouse hover over 'NO', it will turn red, or else it will be white
    if (mouseX >= 275 && mouseX <= 375 && mouseY >= 360 && mouseY <= 410) {
        renderDeclineExitBtn(renderer, font, colorRED, "NO", 360);
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            *confirmExit = false;
        }
    } else {
        renderDeclineExitBtn(renderer, font, colorWHITE, "NO", 360);
    }
}

// display full game over gui
void renderGameOverScreen(SDL_Renderer* renderer, TTF_Font* font, SDL_Color colorWHITE, SDL_Color colorRED, int time, int enemyShipDestroyed, int score) {
    // Render Game Over title
    renderGameOverTitle(renderer, font, colorRED, "GAME OVER", 180);
    // Render Game Over content
    renderScore(renderer, font, colorWHITE, score, 225);
    renderGameOverContent(renderer, font, colorWHITE, "You have survived for", 280, 350);
    renderTimeSurvived(renderer, font, colorWHITE, time, 300);
    renderGameOverContent(renderer, font, colorWHITE, "You have destroyed", 350, 330);
    renderEnemyShipDestroyed(renderer, font, colorWHITE, enemyShipDestroyed, 370);
    renderGameOverContent(renderer, font, colorWHITE, "enemy ships", 390, 250);
}

// button handler for scoreboard
void handleButtonClicks(SDL_Renderer* renderer, TTF_Font* font, SDL_Color colorRED, SDL_Color colorWHITE, int mouseX, int mouseY, SDL_Event event, int* currentPage, bool* displayingSCOREBOARD, bool* displayingMENU, bool* ScoreboardTIME, bool* ScoreboardTOP, int* lineNumber) {
    // Back Button
    if (mouseX >= 225 && mouseX <= 375 && mouseY >= 625 && mouseY <= 675) {
        renderBackBtn(renderer, font, colorRED, "BACK", 625);
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            printf("Back Button Pressed\n");
            *displayingSCOREBOARD = false;
            *displayingMENU = true;
        }
    } else {
        renderBackBtn(renderer, font, colorWHITE, "BACK", 625);
    }

    // Left Button
    if (*currentPage > 1 && mouseX >= 10 && mouseX <= 60 && mouseY >= 625 && mouseY <= 675) {
        renderLeftBtn(renderer, font, colorRED, 625);
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            printf("Left Button Pressed\n");
            (*currentPage)--;
        }
    } else if (*currentPage > 1) {
        renderLeftBtn(renderer, font, colorWHITE, 625);
    }

    // Right Button
    if (*lineNumber > *currentPage * 20 && mouseX >= 530 && mouseX <= 580 && mouseY >= 625 && mouseY <= 675) {
        renderRightBtn(renderer, font, colorRED, 625);
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            printf("Right Button Pressed\n");
            (*currentPage)++;
        }
    } else if (*lineNumber > *currentPage * 20) {
        renderRightBtn(renderer, font, colorWHITE, 625);
    }

    // Filter Scoreboard based on history
    if (mouseX >= 475 && mouseX <= 550 && mouseY >= 25 && mouseY <= 45) {
        renderHistoryBtn(renderer, font, colorRED, 25);
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            printf("History Button Pressed\n");
            *ScoreboardTIME = true;
            *ScoreboardTOP = false;
        }
    } else {
        renderHistoryBtn(renderer, font, colorWHITE, 25);
    }

    // Filter Scoreboard based on top score
    if (mouseX >= 475 && mouseX <= 550 && mouseY >= 50 && mouseY <= 70) {
        renderTopBtn(renderer, font, colorRED, 50);
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            printf("Top Button Pressed\n");
            *ScoreboardTIME = false;
            *ScoreboardTOP = true;
        }
    } else {
        renderTopBtn(renderer, font, colorWHITE, 50);
    }
}
