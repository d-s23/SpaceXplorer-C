//
// Created by d2-sakaria on 05/05/2025.
//
#include "gameFunctions.h"
#include <stdio.h>
#include <stdlib.h>


void introRules() {
    FILE *fptr;

    // Open a file in read mode
    fptr = fopen("rules.txt", "r");

    // Store the content of the file
    char myString[100];

    // Read and print the content line by line
    while (fgets(myString, sizeof(myString), fptr)) {
        printf("%s", myString);  // Print each line
    }

    // Close the file
    fclose(fptr);

}


void difficultyLevel(int *difficulty, int *damageAmount, int *encounterMultiplier) {
    printf("Select your difficulty level:\n 1. Easy\n 2. Medium\n 3. Hard\n");
    scanf("%d", difficulty);

    switch (*difficulty) {
        case 1: // Easy
            printf("You selected easy mode!\n");
            *encounterMultiplier = 12;
            *damageAmount = -10;
            break;

        case 2: // Medium
            printf("You selected Medium mode!\n");
            *encounterMultiplier = 10;
            *damageAmount = -20;
            break;

        case 3: // Hard
            printf("You selected Hard mode!\n");
            *encounterMultiplier = 8;
            *damageAmount = -30;
            break;

        default:
            printf("Invalid difficulty. Defaulting to Medium\n");
            *difficulty = 2;
            *encounterMultiplier = 10;
            *damageAmount = -20;
    }
}


void initialiseGame(player_stat *p, position map[20][20]) {
    // Set initial player stats
    p->fuel = 100;
    p->shipHealth = 100;
    p->spaceJunk = 0;

    // Random starting position
    p->x = rand() % 20;
    p->y = rand() % 20;

    // Initialize map
    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 20; x++) {
            map[y][x].planet = (rand() % 3 == 0); // ~33.3% chance it's a planet
            map[y][x].beenVisited = false;
            map[y][x].fuel = map[y][x].planet ? (rand() % 15 + 10) : 0; //Generates a number between (0 to 15) +10 == 10 to 25
            map[y][x].junk = rand() % 5 + 1; //Generates a number between (0 to 5) +1 == 1 to 6
            map[y][x].earth = false; // Temporarily
        }
    }

    // Pick a random Earth position not too close to player
    int earthX, earthY;
    do { // randomly select a location for earth
        earthX = rand() % 20;
        earthY = rand() % 20;
    } while (abs(earthX - p->x) + abs(earthY - p->y) < 5); // At least 5 tiles away, using manhattan distance

    map[earthY][earthX].earth = true;
}


void movePlayer(player_stat *p, position map[20][20], int *gameOver, int damage,int encounterMultiplier) {
    char direction;
    int damageAmount = damage;

    printf("\nChoose direction to move:\n");
    printf("What direction would you like to move in?\n");
    printf("Use w(Up), s(down), a(left), d(right)\n");
    scanf(" %c", &direction);

    int newX = p->x;
    int newY = p->y;

    switch(direction) {
        case 'w': newY--; break; // up
        case 's': newY++; break; // down
        case 'd': newX++; break; // left
        case 'a': newX--; break; // right
        default:
            printf("Invalid direction\n");
            return;
    }


    // Check boundaries
    if (newX < 0 || newX >= 20 || newY < 0 || newY >= 20) {
        printf("You have reached the end of the universe\n");
        return;
    }


    // Check if visited
    if (map[newY][newX].beenVisited) {
        printf("You have jumped at lightspeed to (%d, %d)\n", newX, newY);
        printf("You have already been here, no more resources.\n");

    }

    else {
        // Get resources if any
        if (map[newY][newX].planet) { // Landed on a planet
            printf("You have jumped at lightspeed to (%d, %d)\n", newX, newY);
            printf("You landed on a planet!\n");
            printf("You collected %d fuel and %d space junk.\n", map[newY][newX].fuel, map[newY][newX].junk);

            p->spaceJunk += map[newY][newX].junk; // Junk found on planet added to inventory
            p->shipHealth -= 10; // Landing damage to ship!


            p->fuel += map[newY][newX].fuel;
            if (p->fuel >100){
                p->fuel = 100; //Checks if fuel stat is over 100%, if it is sets it back to 100
            }

            map[newY][newX].junk = 0;
            map[newY][newX].fuel = 0;



        } else { //Landed in space
            printf("You have jumped at lightspeed to (%d, %d)\n", newX, newY);
            printf("You are floating through empty space... you picked up %d scrap\n", map[newY][newX].junk);
            p->spaceJunk += map[newY][newX].junk;
            map[newY][newX].junk = 0;
        }
        map[newY][newX].beenVisited = 1;
    }

    // Move player
    p->x = newX;
    p->y = newY;

    // Fuel consumption
    p->fuel -= 10;
    if (p->fuel <= 0) {
        printf("You are out of fuel!\n");
        *gameOver = 1;
    }
    else if (p->fuel <= 10) {
        printf("WARNING: Fuel is Critically Low\n");
    }

    // Ship damaged
    if (p->shipHealth <= 0) {
        printf("Your ship has taken damage beyond repair!\n");
        *gameOver = 1;
    }
    else if (p->shipHealth <= 10) {
        printf("WARNING: Ship Health is Critically Low\n");
    }

    //Alien or Meteor encounter
    if (rand() % encounterMultiplier == 0){
        if (rand() % 2 == 0) {
            printf("An Alien ship appeared out of nowhere! You managed to shake them off but you ended up taking %d damage to your ship!\n", damageAmount);
            p->shipHealth += damageAmount;
        }
        else{
            printf("An Meteor hit your ship out of nowhere! You took %d damage to your ship!\n", damageAmount);
            p->shipHealth += damageAmount;
        }

    }

    // Check for win
    if (map[newY][newX].earth) {
        printf("You made it back home! You found Earth!\n");
        *gameOver = 2;
        return;
    }
}

void repairShip(player_stat *p, position map[20][20]){
    // Check if player is currently on a planet
    if (map[p->y][p->x].planet){
        if (p->shipHealth >= 100) {
            printf("Your ship is already fully repaired.\n");
            return;
        }

        else if (p->spaceJunk < 10){
            printf("Not enough space junk to repair your ship!\n");
        }

        else{
            while ((p->spaceJunk >= 10) && ( p-> shipHealth < 100)){
                p->spaceJunk -= 10;
                p->shipHealth += 20;
                if (p->shipHealth > 100){
                    p->shipHealth = 100;
                }

            }
            printf("Your Ship Health has been restored to:%d %\n", p->shipHealth);
        }

    }

    else{
        printf("You must land on a planet to repair your ship.\n");
    }
}

void displayStats(player_stat *p, position map[20][20]){
    int compass;
    printf("\n*--- Player Stats ---*\n");
    printf("Location: (%d, %d)\n", p->x, p->y);
    printf("Fuel: %d\n", p->fuel);
    printf("Ship Health: %d\n", p->shipHealth);
    printf("Space Junk: %d\n", p->spaceJunk);
    printf("------------------------\n");
}

void leaderboard(const char*initials, int difficulty, int gameover){
    const char* result;

    if (gameover == 2){
        result = "Win";
    }
    else{
        result = "Lost";
    }

    FILE* file = fopen("leaderboard.txt", "a");

    // Write to file
    fprintf(file, "%s %d %s\n", initials, difficulty, result);
    fclose(file);

    // Reopen to display all leaderboard entries
    file = fopen("leaderboard.txt", "r");
    if (!file) {
        printf("Error reading leaderboard file.\n");
        return;
    }

    char readInitials[4];
    int readDifficulty;
    char readResult[10];

    printf("\n--- Leaderboard ---\n");
    printf("INI  | DIFFICULTY | RESULT\n");
    printf("----------------------------\n");

    while (fscanf(file, "%3s %d %9s", readInitials, &readDifficulty, readResult) == 3) {
        printf("%-4s | %-10d | %-5s\n", readInitials, readDifficulty, readResult);
    }

    printf("----------------------------\n");
    fclose(file);
}

