#ifndef ENTRANCE_MENU_H
#define ENTRANCE_MENU_H
////  library : Entrance Menu   ////

// Arvin Rasulzadeh
// 403110422

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <ctype.h>
#include <ncurses.h>
#include "new_user.h"
#include "log_in.h"

void entrance_menu();
void print_menu();

// function to print the menu options
void print_menu(int highlight , char** choices, int n_choices){
    // three options
    clear();
    for (int i = 1; i <= n_choices; ++i){
        if (highlight == i){
            attron(A_REVERSE); // highlight the selected option
            mvprintw(LINES / 2 + i-1, (COLS - strlen(choices[i-1])) / 2, "%s", choices[i-1]);
            attroff(A_REVERSE);
        }
        else{
            mvprintw(LINES / 2 + i-1, (COLS - strlen(choices[i-1])) / 2, "%s", choices[i-1]);
        }
    }
    refresh();
}
// checked :) ==> It can be used later (e.g. in pregame menu) as well 

// function for entrance menu
void entrance_menu(){
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    bkgd(COLOR_PAIR(1));
    keypad(stdscr, TRUE); // enable keyboard input for the window
    curs_set(0); // hide cursor
    int highlight = 1;
    int choice = 0;
    int c;
    char *choices[] = {"Log In", "Create New User", "Enter As Guest"}; 

    while (1){
        print_menu(highlight , choices , 3);
        c = getch();
        switch(c){
            case KEY_UP:
                if (highlight == 1){
                    highlight = 3;
                    break;
                }
                else if(highlight == 2){
                    highlight--;
                    break;
                }
                else if(highlight == 3){
                    highlight--;
                    break;
                }
            case KEY_DOWN:
                if (highlight == 3){
                    highlight = 1;
                    break;
                }
                else if(highlight == 2){
                    highlight++;
                    break;
                }
                else if(highlight == 1){
                    highlight++;
                    break;
                }
            case 10: // ENTER key
                choice = highlight;
                break;
            default:
                break;
        }

        if (choice != 0){
            break;
        }

    }

    // call the appropriate function based on the choice
    if (choice == 1){
        log_in();
    }
    else if (choice == 2){
        create_user();
    }
    else if (choice == 3){
        // pregame_menu();
    }

    endwin(); 
}
//checked :)

#endif


