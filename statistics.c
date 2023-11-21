#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 700

// check number of lines in file
int checkNumberOfLines() {
    FILE* file = fopen("game_statistics.txt", "r");
    if (file == NULL) {  // Check if file exists
        printf("Error opening file!\n");
        return -1; // Return -1 to indicate an error
    }

    int lines = 0;
    char ch;
    while(!feof(file)) {
        ch = fgetc(file);
        if(ch == '\n') {
            lines++;
        }
    }

    fclose(file);
    return lines;
}

// calculate score
int calculateScore(int timeSurvived, int enemyShipsDestroyed) {
    // Convert time to seconds
    int seconds = timeSurvived / 1000;

    // Calculate score
    int score = (seconds * 10) + (enemyShipsDestroyed * 100) + (seconds * 25);

    return score;
}

// record game statistics
void recordGameStatistics(int timeSurvived, int enemyShipsDestroyed, int score) {
    // Get game number from file and plus 1 for the new statistics
    int gameNumber = checkNumberOfLines() + 1;

    // Convert time to seconds
    int seconds = timeSurvived / 1000;

    // Write game statistics to file
    FILE* file = fopen("game_statistics.txt", "a");
    fprintf(file, "%d. Time Survived: %d Sec, Enemy Ships Destroyed: %d, Score: %d\n", gameNumber, seconds, enemyShipsDestroyed, score);
    fclose(file);
}