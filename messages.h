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
void food_list();
void weapon_list();
void spell_list();
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


// display food list

// the food list window
void food_list(player hero){
    int height = 23;
    int width = 52;
    int start_x = (LINES - height) / 2;
    int start_y = (COLS - width) / 2;

    // create a new window for the food screen
    WINDOW *help_win = newwin(height, width, start_x, start_y);

    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    // draw borders around the window
    wattron(help_win, COLOR_PAIR(5));
    box(help_win, 0, 0);
    wattron(help_win, COLOR_PAIR(5));


    int title_y = (width - 9) / 2; // length of "FOOD MENU" = 9

    // Print FOOD MENU centered
    wattron(help_win, COLOR_PAIR(8) | A_BOLD);
    mvwprintw(help_win, 1, title_y, "FOOD MENU");
    wattroff(help_win, COLOR_PAIR(8) |A_BOLD);

    // print instructions inside the window
    mvwprintw(help_win, 3, 1, " Regular Food: %d" , hero.food_count);
    mvwprintw(help_win, 5, 1, " Ideal Food: %d" , 0);
    mvwprintw(help_win, 7, 1, " Magical Food: %d" , 0);
    mvwprintw(help_win, 9, 1, " Rotten Food: %d" , 0);
    mvwprintw(help_win, 14, 1, " To consume food, exit this menu and enter 'C'");

    
    wrefresh(help_win);

    // wait for user input to close the help screen
    wgetch(help_win);

    // delete the window
    delwin(help_win);
    clear();

}


// the weapon list window
void weapon_list(player* ptr_to_hero){
    int height = 23;
    int width = 55;
    int start_x = (LINES - height) / 2;
    int start_y = (COLS - width) / 2;

    // create a new window for the help screen
    WINDOW *help_win = newwin(height, width, start_x, start_y);

    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    // draw borders around the window
    wattron(help_win, COLOR_PAIR(6));
    box(help_win, 0, 0);
    wattron(help_win, COLOR_PAIR(6));


    int title_y = (width - 11) / 2; // length of "WEAPON MENU" = 11

    // Print WEAPON MENU centered
    wattron(help_win, COLOR_PAIR(1) | A_BOLD);
    mvwprintw(help_win, 1, title_y, "WEAPON MENU");
    wattroff(help_win, COLOR_PAIR(1) | A_BOLD);

    char CH = 'm';
    // CH = wgetch(help_win);
    while (CH == 'm' || CH == 'd'|| CH == 'w'|| CH == 'a' || CH == 's' || CH == 'M' || CH == 'D'|| CH == 'W'|| CH == 'A' || CH == 'S'){
        mvwprintw(help_win, 16, 1, " The current weapon is bold.");
        mvwprintw(help_win, 18, 1, " To select weapon, enter the weapon's character.");
        mvwprintw(help_win, 20, 1, " Default weapon is Mace.");
    
        // print instructions inside the window
        if(ptr_to_hero->current_weapon == 0) wattron(help_win , A_BOLD);
        mvwprintw(help_win, 3, 1, " Mace (m): %d" , ptr_to_hero->weapons[0]);
        if(ptr_to_hero->current_weapon == 0) wattroff(help_win , A_BOLD);

        if(ptr_to_hero->current_weapon == 1) wattron(help_win , A_BOLD);
        mvwprintw(help_win, 5, 1, " Dagger (d): %d" , ptr_to_hero->weapons[1]);
        if(ptr_to_hero->current_weapon == 1) wattroff(help_win , A_BOLD);

        if(ptr_to_hero->current_weapon == 2) wattron(help_win , A_BOLD);
        mvwprintw(help_win, 7, 1, " Magic Wand (w): %d" , ptr_to_hero->weapons[2]);
        if(ptr_to_hero->current_weapon == 2) wattroff(help_win , A_BOLD);

        if(ptr_to_hero->current_weapon == 3) wattron(help_win , A_BOLD);
        mvwprintw(help_win, 9, 1, " Normal Arrow (a): %d" , ptr_to_hero->weapons[3]);
        if(ptr_to_hero->current_weapon == 3) wattroff(help_win , A_BOLD);

        if(ptr_to_hero->current_weapon == 4) wattron( help_win , A_BOLD);
        mvwprintw(help_win, 11, 1, " Sword (s): %d" , ptr_to_hero->weapons[4]);
        if(ptr_to_hero->current_weapon == 4) wattroff( help_win , A_BOLD);
        CH = wgetch(help_win);

        // int whichWeapon = 0;
        // ptr_to_hero->current_weapon = whichWeapon;
        switch (CH)
        {
        case 'm':
        case 'M':
            ptr_to_hero->current_weapon = 0;
            break;
        case 'd':
        case 'D':
            ptr_to_hero->current_weapon = 1;
            break;
        case 'w':
        case 'W':
            ptr_to_hero->current_weapon = 2;
            break;
        case 'a':
        case 'A':
            ptr_to_hero->current_weapon = 3;
            break;
        case 's':
        case 'S':
            ptr_to_hero->current_weapon = 4;
            break;
        
        default:
            break;
        }

        wrefresh(help_win);
    }



    // int CH;
    // CH = wgetch(help_win);
    // while (CH == 'm' || CH == 'd'|| CH == 'w'|| CH == 'a' || CH == 's' || CH == 'M' || CH == 'D'|| CH == 'W'|| CH == 'A' || CH == 'S'){
    //     int whichWeapon = 0;
    //     hero.current_weapon = whichWeapon;
    //     CH = wgetch(help_win);
    // }
    // do {
    //     CH = wgetch(help_win);
    // } while (CH == 'm' || CH == 'd'|| CH == 'w'|| CH == 'a' || CH == 's' || CH == 'M' || CH == 'D'|| CH == 'W'|| CH == 'A' || CH == 'S');

    // delete the window
    delwin(help_win);
    clear();

}


// the weapon list window
void spell_list(player* ptr_to_hero){
    int height = 23;
    int width = 55;
    int start_x = (LINES - height) / 2;
    int start_y = (COLS - width) / 2;

    // create a new window for the help screen
    WINDOW *help_win = newwin(height, width, start_x, start_y);

    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    // draw borders around the window
    wattron(help_win, COLOR_PAIR(4));
    box(help_win, 0, 0);
    wattron(help_win, COLOR_PAIR(4));


    int title_y = (width - 10) / 2; // length of "SPELL MENU" = 10

    // Print SPELL MENU centered
    wattron(help_win, COLOR_PAIR(2) | A_BOLD);
    mvwprintw(help_win, 1, title_y, "SPELL MENU");
    wattroff(help_win, COLOR_PAIR(2) | A_BOLD);

    char CH = 'h';
    while (CH == 'h' || CH == 'd'|| CH == 's' || CH == 'H' || CH == 'D' || CH == 'S'){
        mvwprintw(help_win, 13, 1, " To use spell, exit this menu and enter 'Z'");
        mvwprintw(help_win, 16, 1, " The current spell is bold.");
        mvwprintw(help_win, 18, 1, " To select spell, enter the spell's character.");
        mvwprintw(help_win, 20, 1, " Default selected spell is Health.");
    
        // print instructions inside the window
        if(ptr_to_hero->current_spell == 0) wattron(help_win , A_BOLD);
        mvwprintw(help_win, 4, 1, " Health (h): %d" , ptr_to_hero->spells[0]);
        if(ptr_to_hero->current_spell == 0) wattroff(help_win , A_BOLD);

        if(ptr_to_hero->current_spell == 1) wattron(help_win , A_BOLD);
        mvwprintw(help_win, 6, 1, " Speed (s): %d" , ptr_to_hero->spells[1]);
        if(ptr_to_hero->current_spell == 1) wattroff(help_win , A_BOLD);

        if(ptr_to_hero->current_spell == 2) wattron(help_win , A_BOLD);
        mvwprintw(help_win, 8, 1, " Damage (d): %d" , ptr_to_hero->spells[2]);
        if(ptr_to_hero->current_spell == 2) wattroff(help_win , A_BOLD);
        CH = wgetch(help_win);

        // int whichWeapon = 0;
        // ptr_to_hero->current_weapon = whichWeapon;
        switch (CH)
        {
        case 'h':
        case 'H':
            ptr_to_hero->current_spell = 0;
            break;
        case 'd':
        case 'D':
            ptr_to_hero->current_spell = 2;
            break;
        case 's':
        case 'S':
            ptr_to_hero->current_spell = 1;
            break;
        default:
            break;
        }

        wrefresh(help_win);
    }

    delwin(help_win);
    clear();

}



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
    int height = 26;
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
    wattron(help_win, COLOR_PAIR(5) | A_BOLD);
    mvwprintw(help_win, 1, title_y, "HELP MENU");
    wattroff(help_win, COLOR_PAIR(5) | A_BOLD);

    wattron(help_win, A_BOLD);

    // print instructions inside the window
    mvwprintw(help_win, 3, 1, " Viewing Foods: F");
    mvwprintw(help_win, 4, 1, " Viewing Weapons: I");
    mvwprintw(help_win, 5, 1, " Viewing Spells: X");

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

    wattroff(help_win, A_BOLD);

    wrefresh(help_win);

    // wait for user input to close the help screen
    wgetch(help_win);

    // delete the window
    delwin(help_win);
    clear();

}

#endif