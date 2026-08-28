#include <stdio.h>
#include "gameFunctions.h"
#include <stdlib.h>
#include <time.h>

#define MAP_WIDTH 20
#define MAP_HEIGHT 20

int main() {
    srand(time(NULL)); // random seed
    player_stat player;
    position map [MAP_WIDTH][MAP_HEIGHT];

    int difficulty = 4;
    int gameover = 0;
    int damage, encounterMultiplier;

    introRules(); // Present game into and rules


    difficultyLevel(&difficulty, &damage, &encounterMultiplier);
    //Selects difficulty


    initialiseGame(&player, map); // initialise player and map
    printf("You are starting at location (%d, %d)\n", player.x, player.y);


    //Main game loop
    while (gameover == 0){
        // game logic
        int gamemenu;

        printf("\nWhat would you like to do?\n");
        printf("1. Move\n");
        printf("2. Repair ship\n");
        printf("3. Check stats\n");
        printf("4. Quit game\n");
        printf("Enter choice: ");
        scanf("%d", &gamemenu);

        switch (gamemenu) {
            case 1:
                movePlayer(&player, map, &gameover, damage, encounterMultiplier);  // movement + fuel check + random events
                break;
            case 2:
                repairShip(&player, map);
                break;
            case 3:
                displayStats(&player, map);
                break;
            case 4:
                printf("You quit the game.\n");
                gameover = 1;
                break;
            default:
                printf("Invalid option. Try again.\n");
        }

    }
    if (gameover == 1){
        printf("\nYou lost\n");
    }

    else if (gameover == 2){
        printf("\nYou won congrats\n");
    }

    char initials[4];
    printf("Enter your 3 initials: \n");
    scanf("%3s", initials);

    leaderboard(initials, difficulty, gameover);

    return 0;
}

