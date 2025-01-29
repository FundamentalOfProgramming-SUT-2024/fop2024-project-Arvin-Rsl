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
    int weapons[5]; // 0 : Mace (m)
                    // 1 : Dagger (d)
                    // 2 : Magic Wand (w)
                    // 3 : Normal Arrow (a)
                    // 4 : Sword (s)
    int current_weapon; // 0 : Mace (m)
                        // 1 : Dagger (d)
                        // 2 : Magic Wand (w)
                        // 3 : Normal Arrow (a)
                        // 4 : Sword (s)
    int spells[3]; // 0 : Health → H
                  // 1 : Speed   → $
                  // 2 : Damage  → !
    int current_spell;
    int pick; // 1 if player has enabled picking up "spells" and "weapons" , 0 otherwise
    int color; // ...
    char username[100];

} player;

#endif
