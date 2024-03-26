# The Legend of Zelda II: CSD Edition

Collaborative course project for CS454 2022-23 Class, University of Crete, Department of Computer Science.
Taught by professor [Anthony Savidis](https://www.researchgate.net/profile/Anthony-Savidis). 

## Introduction
The project is our own version of Zelda II game of Nintendo, where we implemented from scratch our own Game Engine using
Allegro Library. All TileMaps were designed by us using [Tiled](https://www.mapeditor.org/). Music was composed and recorded
by Theodoros Chalkidis (co-owner of this project).

## Development
We used Visual Studio 2022 to develop and run the projects. For older versions, make sure to configure your build tools
version. In theory, importing the project solution to Visual Studio should be enough to be able to build and run the game,
as all the necessary libraries are included on the repository. This should also apply for CLion, for which we
included a generated CMake file.

Although it shouldn't be heavy for the CPU, many bitmaps are pre-rendered on the GPU for better performance. 


### External Libraries
This project is based on [Allegro](https://liballeg.org/) library, which provides I/O managers and the necessary bitmaps, before blitting them on the screen.
It also uses [nlohman json](https://github.com/nlohmann/json) library to parse .json configuration files that will allow the user to configure the game properties
appropriately, without having to make any code changes or recompile the project.

### Game Engine Theory
Input, AI, Render, Physics, Usercode

## Game Information

### Configurations
As mentioned above, most of the game characteristics are configurable. One can easily change the player's stats (health,
mana points, attack damage, spawn lives, jump height, fall speed etc), as well as the NPC entities and items. Also, 
through Game Config one can change the locked frame rate and screen scaling (see comments), although we wouldn't recommend
going above 60 FPS as many animations and physics were built based on the clock, and the game won't look as good.

### Controls
#### Main Buttons
Press <kbd>Esc</kbd> to exit the game any time. <kbd>P</kbd> works as a Pause button.

On the Main Menu screen, you can move freely. Pressing <kbd>Enter</kbd> takes you to the main game course.

Every time you die, you respawn at the location you entered from at the specific map. Every time you change map,
all enemies and items respawn. Enemies have a configured drop chance for a configured list of possible drops.

Dying takes you to a prison cell. To exit the game, you need to use <kbd>Esc</kbd> nontheless.

Win the game by defeating Guma boss and pick the Sword!

#### Movement
Use <kbd>↑</kbd><kbd>↓</kbd><kbd>→</kbd><kbd>←</kbd> to Jump, Duck, Move Right and Left respectively.

Press <kbd>A</kbd> to attack. Note that Link does not take damage from attacks coming through his shield
when he ducks facing the attack direction.

#### Spells

<kbd>Q</kbd> Cast shield spell.

<kbd>W</kbd> Cast jump spell.

<kbd>E</kbd> Cast life spell.

<kbd>R</kbd> Cast fairy spell.

<kbd>T</kbd> Cast thunder spell.

#### Developer Keys

<kbd>F</kbd> Toggles the grid collision block for the player

Numbers teleport you to specific maps.

<kbd>1</kbd> Main Screen

<kbd>2</kbd> Palace

<kbd>3</kbd> Dungeon 1st floor

<kbd>4</kbd> Win Screen

<kbd>5</kbd> Dungeon 1st floor right

<kbd>6</kbd> Lose Screen


.
