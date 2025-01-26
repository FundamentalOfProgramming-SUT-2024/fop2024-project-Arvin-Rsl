#ifndef MESSAGES_H
#define MESSAGES_H
////  library : Games Messages   ////

// Arvin Rasulzadeh
// 403110422

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <ctype.h>
#include <ncurses.h>
#include "player.h"

// my LINES is 45 and COLS is 184

// the upper three lines and lower three lines of map are dedicated to messages

void help();
void print_top_message();
void print_bottom_message();

// // x (row) and y (col)
// typedef struct {
//     int x; // row
//     int y; // col
// } position;

// // room
// typedef struct {
//     int floor_level; // the floor/level/ground where room is located (start floor: 1 , end floor: 4)
//     int room_number; // room's number in that floor , starting from 1
//     // length and width include the wall characters
//     int length; // |
//                 // |
//                 // |
//                 // |
//     int width;  // ____
//     int hide;   // if 0, the Room is visible
//     int number_of_doors;
//     int number_of_windows;
//     int number_of_pillars;
//     position corner; // corner = upper left corner of the room
//     int type; // 0 => Regular Room
//               // 1 => Battle Room (trap)
//               // 2 => Enchant Room
//               // 3 => Treasure Room ( Third is the charm :D )
//               // 4 => Nightmare Room
// /*  Type of Room:    Pillar Char:       Floor Char      Floor & Pillar Color      int type  
//     Regular Room          O                 .                   White                 0
//     Battle Room        No Pillar            .                   Red                   1
//     Enchant Room          O                 ,                   Magenta               2
//     Treasure Room      No Pillar            -                   Yellow                3
//     Nightmare Room        O                 ~                   Blue                  4

// */
//     int doors_x[3];
//     int doors_y[3];
    
//     int windows_and_pillars_x[2]; // the first two for windows and the rest for pillars
//     int windows_and_pillars_y[2]; // the first two for windows and the rest for pillars

//     // int pillars_x[2];
//     // int pillars_y[2];
    
// } room;

// print message (top of the map)
void print_top_message(char * message){
    // HELP
    mvprintw(0 , COLS - 18 - 3 , "Press '/' for help" ); // 18 chars
    mvprintw(0 , 3 , "%s" , message); 
}


void print_bottom_message(player* hero , int level_num){

    // int start_col = 0;
    int start_col = (COLS - (14 + 7 + 7 + 8 + 16  +  3*10) )/ 2;

    // level number
    init_pair(73 , COLOR_CYAN , COLOR_BLACK);
    attron(COLOR_PAIR(73));
    mvprintw(LINES - 1 , start_col , "Floor Level: "); // 13 chars
    attroff(COLOR_PAIR(73));
    mvprintw(LINES - 1 , start_col + 13, "%d" , level_num); // 1 char


    // gold count
    init_pair(74 , COLOR_YELLOW , COLOR_BLACK);
    attron(COLOR_PAIR(74));
    mvprintw(LINES - 1 , 10 + start_col + 14 , "Gold: "); // 6 chars
    attroff(COLOR_PAIR(74));
    mvprintw(LINES - 1 , 10 + start_col + 14 + 6 , "%d" , hero->gold_count); // 1 char


    // food count
    init_pair(75 , COLOR_MAGENTA , COLOR_BLACK);
    attron(COLOR_PAIR(75));
    mvprintw(LINES - 1, 2*10 + start_col + 14 + 7, "Food: " ); // 6 chars
    attroff(COLOR_PAIR(75));
    mvprintw(LINES - 1, 2*10 + start_col + 14 + 7 + 6, "%d" , hero->food_count); // 1 chars


    // health bar (full = 16 , medium = 9 , low = 5)
    if (hero->health > 9){
        init_pair(3 , COLOR_GREEN , COLOR_BLACK);
    }
    else if (5 < hero->health && hero->health <= 9)
    {
        init_pair(3 , COLOR_YELLOW , COLOR_BLACK);
    }
    else if (hero->health <= 5){
        init_pair(3 , COLOR_RED , COLOR_BLACK);
    }
    attron(COLOR_CYAN);
    mvprintw(LINES - 1, 3*10 + start_col + 14 + 7 + 7 , "Health: "); // 8 chars
    attroff(COLOR_CYAN);
    attron(COLOR_PAIR(3));
    for (int i = 0 ; i < hero->health ; i++){ // maximum: 16 chars
        mvprintw(LINES - 1, 3*10 + start_col + 14 + 7 + 7 + 8 + i, "*");
    }
    attroff(COLOR_PAIR(3));
}


// the help screen
void help() {
    int height = 24;
    int width = 40;
    int start_x = (LINES - height) / 2;
    int start_y = (COLS - width) / 2;

    // create a new window for the help screen
    WINDOW *help_win = newwin(height, width, start_x, start_y);

    init_pair(6, COLOR_GREEN, COLOR_BLACK);
    // draw borders around the window
    wattron(help_win, COLOR_PAIR(6));
    box(help_win, 0, 0);
    wattron(help_win, COLOR_PAIR(6));

    init_pair(5, COLOR_CYAN, COLOR_BLACK);

    int title_y = (width - 9) / 2; // length of "HELP MENU" = 9

    // Print HELP MENU in cyan color and centered
    wattron(help_win, COLOR_PAIR(5));
    mvwprintw(help_win, 1, title_y, "HELP MENU");
    wattroff(help_win, COLOR_PAIR(5));

    // print instructions inside the window
    mvwprintw(help_win, 3, 1, " Viewing Foods: F");
    mvwprintw(help_win, 4, 1, " Viewing Weapons: I");

    int movement_start_x = (height - 16) / 2 + 2; // Vertically center the movement instructions
    int movement_start_y = (width - 15) / 2;     // Horizontally center the movement instructions

    // Print movement instructions inside the window
    mvwprintw(help_win, movement_start_x, 1, " Movement:");
    mvwprintw(help_win, movement_start_x + 1, movement_start_y, "+---+---+---+");
    mvwprintw(help_win, movement_start_x + 2, movement_start_y, "| 7 | 8 | 9 |");
    mvwprintw(help_win, movement_start_x + 3, movement_start_y, "+---+---+---+");
    mvwprintw(help_win, movement_start_x + 4, movement_start_y, "| 4 |   | 6 |");
    mvwprintw(help_win, movement_start_x + 5, movement_start_y, "+---+---+---+");
    mvwprintw(help_win, movement_start_x + 6, movement_start_y, "| 1 | 2 | 3 |");
    mvwprintw(help_win, movement_start_x + 7, movement_start_y, "+---+---+---+");

    // Print alternative movement keys inside the window, centered
    mvwprintw(help_win, movement_start_x + 9, 1, " Alternative Movement:");
    mvwprintw(help_win, movement_start_x + 10, movement_start_y, "+---+---+---+");
    mvwprintw(help_win, movement_start_x + 11, movement_start_y, "| Y | J | U |");
    mvwprintw(help_win, movement_start_x + 12, movement_start_y, "+---+---+---+");
    mvwprintw(help_win, movement_start_x + 13, movement_start_y, "| H |   | L |");
    mvwprintw(help_win, movement_start_x + 14, movement_start_y, "+---+---+---+");
    mvwprintw(help_win, movement_start_x + 15, movement_start_y, "| B | K | N |");
    mvwprintw(help_win, movement_start_x + 16, movement_start_y, "+---+---+---+");

    wrefresh(help_win);

    // wait for user input to close the help screen
    wgetch(help_win);

    // delete the window
    delwin(help_win);
    clear();

}

#endif