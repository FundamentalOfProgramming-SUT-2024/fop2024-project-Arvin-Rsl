#ifndef MOVE_H
#define MOVE_H
////  library : Move  ////

// Arvin Rasulzadeh
// 403110422
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <ctype.h>
#include <ncurses.h>
#include <math.h>
// #include "map2.h"
#include "new_map.h"
#include "player.h"
// typedef struct player player;
// typedef struct position position;

int x_moves[] = {-1 , +1 , +0 , +0 , -1 , -1 , +1 , +1}; // up , down , right , left , up-right , up-left , down-right , down-left
int y_moves[] = {+0 , +0 , +1 , -1 , +1 , -1 , +1 , -1};
int valid_move();
void Move();

int valid_move(int x , int y ){   
    char there = mvinch(x , y) & A_CHARTEXT;
    if (there == '.'  || there == ',' || there == '-' || there == '~' || there == '#' || there == '+'){
        return 1;
    }
    return 0;
}
// checked

// technically just a switch/case that changes the players position (if valid) .  
void movement(int ch , player* hero){ // later in while(1) of the print_map() function: 
                                      // char ch = getchar();
                                      // attron
                                      // mvprintw(hero.pos.x , hero.pos.y , "A");
                                      // attroff

    keypad(stdscr, TRUE);
    position current;
    current.x = hero->pos.x;
    current.y = hero->pos.y;
    int x_new ;
    int y_new ;
    switch (ch) {
        case '8': // Up
        case KEY_UP:
        case 'J':
        case 'j':
            x_new = current.x + x_moves[0];
            y_new = current.y + y_moves[0];
            if (valid_move(x_new , y_new)){
                hero->pos.x = x_new;
                hero->pos.y = y_new;
            } 
            break;

        case '2': // Down
        case KEY_DOWN:
        case 'K':
        case 'k':       
            x_new = current.x + x_moves[1];
            y_new = current.y + y_moves[1];
            if (valid_move(x_new , y_new)){
                hero->pos.x = x_new;
                hero->pos.y = y_new;
            } 
            break;

        case '6': // Right
        case KEY_RIGHT:
        case 'L':
        case 'l':
            x_new = current.x + x_moves[2];
            y_new = current.y + y_moves[2];
            if (valid_move(x_new , y_new)){
                hero->pos.x = x_new;
                hero->pos.y = y_new;
            } 
            break;

        case '4': // Left
        case KEY_LEFT:
        case 'H':
        case 'h':
            x_new = current.x + x_moves[3];
            y_new = current.y + y_moves[3];
            if (valid_move(x_new , y_new)){
                hero->pos.x = x_new;
                hero->pos.y = y_new;
            } 
            break;

        case '9': // Upper right
        case 'U':
        case 'u':
            x_new = current.x + x_moves[4];
            y_new = current.y + y_moves[4];
            if (valid_move(x_new , y_new)){
                hero->pos.x = x_new;
                hero->pos.y = y_new;
            } 
            break;

        case '7': // Upper left
        case 'Y':
        case 'y':
            x_new = current.x + x_moves[5];
            y_new = current.y + y_moves[5];
            if (valid_move(x_new , y_new)){
                hero->pos.x = x_new;
                hero->pos.y = y_new;
            } 
            break;

        case '1': // Down left
        case 'B':
        case 'b':
            x_new = current.x + x_moves[7];
            y_new = current.y + y_moves[7];
            if (valid_move(x_new , y_new)){
                hero->pos.x = x_new;
                hero->pos.y = y_new;
            } 
            break;

        case '3': // Down right
        case 'N':
        case 'n':
            x_new = current.x + x_moves[6];
            y_new = current.y + y_moves[6];
            if (valid_move(x_new , y_new)){
                hero->pos.x = x_new;
                hero->pos.y = y_new;
            } 
            break;
    } 
}

/*
example of movement():
        attron(COLOR_PAIR(me.color));
        mvprintw(me.pos.x , me.pos.y , "%c" , 'A');
        int ch = getch();
        if (ch == 'q') {
            break;  
        }
        movement(ch , &me);
        mvprintw(me.pos.x , me.pos.y , "%c" , 'A');
        attroff(COLOR_PAIR(me.color));
        refresh();
*/
#endif