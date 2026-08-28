# SpaceXplorer - C-Based Space Exploration Game

A console-based space exploration game developed in **C**, featuring exploration, resource management, randomised events and multiple difficulty levels.

The objective is to navigate a randomly generated 2D galaxy, manage fuel and spaceship health, and successfully locate Earth while surviving the hazards of space.

## Features

* **2D 20×20 galaxy** with directional movement and boundary checking
* **Randomised galaxy generation** with planets, fuel and space junk
* **Fuel and spaceship health management** throughout exploration
* **Multiple difficulty levels** affecting gameplay and encounter difficulty
* **Random events and hazards** including alien encounters and asteroid collisions
* **Space junk system** used as a resource for spaceship repairs
* **Player statistics** displaying location, fuel, health and collected space junk
* **Win and loss conditions** based on reaching Earth and maintaining the spaceship
* **Leaderboard system** recording the player's initials, difficulty and result
* **External rules file** used to provide the game's introduction and instructions

## Technologies & Concepts

* **C**
* Modular programming using `.c` and `.h` files
* Structures and pointers
* 2D arrays
* Random number generation
* File input and output
* Conditional logic and loops
* Input validation and boundary checking
* State management

## How to Play ##

Select a difficulty level, then use the main menu to:

Move using W, A, S and D
Repair the ship when on a planet
Check your statistics to monitor location, fuel, health and space junk
Quit the game at any time

## Controls ##
Input		Action
1		Move
2		Repair Ship
3		Check Stats
4		Quit Game


Input		Direction

W		Up
S		Down
A		Left
D		Right


## Difficulty ##

The game offers three difficulty levels, which affect encounter frequency and the damage received from hazards.

Difficulty	Encounter Multiplier	Damage
Easy		    12			              10
Medium		  10			              20
Hard		    8			                30

(Invalid difficulty selections default to Medium.)


## Resources & Progression ##

The galaxy is randomly generated at the start of each game, with planets appearing at random locations and providing randomly generated fuel and space junk.

Fuel is consumed when moving, whilst planets can provide additional fuel. Space junk can be collected during exploration and used when repairing the spaceship.

The game is completed when the player successfully locates Earth. Running out of fuel or losing all spaceship health results in a loss.


## Development & Testing ##

The project was developed iteratively, with testing covering movement and boundaries, random starting locations, resource generation, fuel management, spaceship health, repairs, difficulty levels, win/loss conditions and leaderboard functionality.

## Author: ##
 Dev S
