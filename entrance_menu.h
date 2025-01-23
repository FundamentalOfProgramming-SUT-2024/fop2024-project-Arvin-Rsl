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
#include <locale.h>
#include "new_user.h"
#include "log_in.h"
#include "pregame_menu.h"

void draw_title(const char*);
void draw_borders(int);
void entrance_menu();
void print_menu(int , char** , int , int , const char*);

// function to print the menu options
void print_menu(int highlight , char** choices, int n_choices , int which_color , const char* title){
    // three options
    clear();
    draw_title(title);
    for (int i = 1; i <= n_choices; ++i){
        if (highlight == i){
            attron(A_REVERSE); // highlight the selected option
            mvprintw(LINES / 2 + 2*(i-1), (COLS - strlen(choices[i-1])) / 2, "%s", choices[i-1]);
            attroff(A_REVERSE);
        }
        else{
            mvprintw(LINES / 2 + 2*(i-1), (COLS - strlen(choices[i-1])) / 2, "%s", choices[i-1]);
        }
    }
    draw_borders(which_color);
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
        // draw_title("Entrance Menu" , 20);
        print_menu(highlight , choices , 3 , 10 , "Entrance Menu");
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
        clear();
        draw_borders(12);
        mvprintw(LINES / 2, COLS / 2 - 11 , "You have entered as guest");
        mvprintw(LINES / 2 + 2, COLS / 2 - 11, "Press any key to proceed");
        refresh();
        getch();
        pregame_menu();
    }

    endwin(); 
}
//checked :)

// design!
void draw_borders(int which_color){
    start_color();
    init_pair(9 , COLOR_WHITE, COLOR_BLACK);
    init_pair(10 , COLOR_CYAN , COLOR_BLACK);
    init_pair(11 , COLOR_RED , COLOR_BLACK);
    init_pair(12 , COLOR_GREEN , COLOR_BLACK);
    
    attron(COLOR_PAIR(which_color));      
    for (int i = 1; i < COLS - 1; i++) { 
        mvprintw(0, i, "_");         // Top border
        mvprintw(LINES - 2, i, "_"); // Bottom border
    }
    
    for (int i = 1; i < LINES - 1; i++) {
        mvprintw(i, 1, "|");         // Left border
        mvprintw(i, COLS - 2, "|");  // Right border
    }
    attroff(COLOR_PAIR(which_color)); 
}

// title
void draw_title(const char* title){
    init_pair(120 , COLOR_WHITE , COLOR_BLUE);
    attron(COLOR_PAIR(120));
    int y = (COLS - strlen(title) - 16) / 2;
    mvprintw(3, y, " <<==== %s ====>> ", title);
    attroff(COLOR_PAIR(120));
}

#endif


