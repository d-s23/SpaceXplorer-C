//
// Created by d2-sakaria on 05/05/2025.
//

#ifndef SAPCEXPLORER_GAMEFUNCTIONS_H
#define SAPCEXPLORER_GAMEFUNCTIONS_H


#include <stdbool.h>

//Structures
//Player stats structure
typedef struct{
    int x,y;            // player location
    int fuel;           // players inventory fuel stat
    int shipHealth;     // players ship health ()
    int spaceJunk;      // player inventory space junk stat
} player_stat;

// position structure
typedef struct{
    bool planet;        // true if this tile is a planet
    bool earth;         // true if this is Earth (win condition)
    bool beenVisited;   // true if player has visited this tile before
    int fuel;           // fuel available at this location
    int junk;           // junk available at this location
} position;

// Declared functions from main.c
// Declared functions from main.c
void introRules();
void difficultyLevel(int *difficulty, int *damage,int *encounterMultiplier);
void initialiseGame(player_stat *p, position map[20][20]);
void movePlayer(player_stat *p, position map[20][20], int *gameOver, int damage,int encounterMultiplier);
void repairShip(player_stat *p, position map[20][20]);
void displayStats(player_stat *p, position map[20][20]);
void leaderboard(const char*initials, int difficulty, int gameover);



#endif //SAPCEXPLORER_GAMEFUNCTIONS_H
