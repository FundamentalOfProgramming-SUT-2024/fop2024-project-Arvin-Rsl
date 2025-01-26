#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <ctype.h>
#include <ncurses.h>
#include <math.h>
#include "new_map.h"


// Arvin Rasulzadeh
// 403110422


typedef struct 
{
    position pos;
    int gold_count;
    int health;
    int hunger;
    int food_count;
    int food[4]; // 0 : regular
                 // 1 : ideal
                 // 2 : magical
                 // 3 : rotten
    int weapons[5]; // 0 : Mace
                    // 1 : Dagger
                    // 2 : Magic Wand
                    // 3 : Normal Arrow
                    // 4 : Sword
    int spell[3]; // ...
    int color; // ...
    char username[100];

} player;


#endif
