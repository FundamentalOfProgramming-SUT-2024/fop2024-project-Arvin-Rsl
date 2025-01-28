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
#include <locale.h>
#include <pthread.h> // for pthread functions   !!!! bad
#include <unistd.h> // for usleep()
#include "new_map.h"


// my LINES is 45 and COLS is 184

// the upper three lines and lower three lines of map are dedicated to messages

void help();
void print_top_message();
void print_bottom_message();
// void* decrease_health();

// void* decrease_health(void* arg , int difficulty , player *hero){
//     while (1) {
//         double rate = 1.2 * difficulty; // decrease rate
//         int delay = 10000000; // delay in microseconds
//         usleep(delay);
//         hero->health--;
//         if (hero->health < 0) hero->health = 0; 
//     }
//     return NULL;
// }

// print message (top of the map)
void print_top_message(char * message){
    setlocale(LC_ALL, "");
    // HELP
    mvprintw(0 , COLS - 18 - 3 , "Press '/' for help" ); // 18 chars
    mvprintw(0 , 3 , "%s" , message); 
    // usleep(500000);
    // Sleep for 5 seconds without blocking
    // struct timespec req = {5, 0}; // 5 seconds
    // nanosleep(&req, NULL);
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
    attron(COLOR_PAIR(15));
    mvprintw(LINES - 1 , 10 + start_col + 14 , "Gold: "); // 6 chars
    attroff(COLOR_PAIR(15));
    mvprintw(LINES - 1 , 10 + start_col + 14 + 6 , "%d" , hero->gold_count); // 1 char


    // food count
    // init_pair(75 , COLOR_MAGENTA , COLOR_BLACK);
    attron(COLOR_PAIR(8));
    mvprintw(LINES - 1, 2*10 + start_col + 14 + 7, "Food: " ); // 6 chars
    attroff(COLOR_PAIR(8));
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
    for (int i = 0 ; i < 16 ; i++){ // maximum: 16 chars

        if (i < hero->health) {
            mvprintw(LINES - 1, 3*10 + start_col + 14 + 7 + 7 + 8 + i, "%c", '*');
        } else {
            mvprintw(LINES - 1, 3*10 + start_col + 14 + 7 + 7 + 8 + i, "%c", ' ');
        }
        // mvprintw(LINES - 1, 3*10 + start_col + 14 + 7 + 7 + 8 + i, "%c" , '*');
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