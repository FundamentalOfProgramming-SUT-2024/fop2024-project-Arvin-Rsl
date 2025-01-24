#ifndef PREGAME_MENU_H
#define PREGAME_MENU_H
////  library : Pregame Menu   ////

// Arvin Rasulzadeh
// 403110422

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <ctype.h>
#include <ncurses.h>
#include "entrance_menu.h" // needed for print_menu() function  &  going back to entrance menu
// #include "map.h" // for new_map() function (which is not ready yet)
#include "score_table.h" // for show_score_table() function (which is not ready yet)
#include "song.h"

void pregame_menu();
void settings();
void choose_song();
void choose_color();
void choose_difficulty();
void show_saved_games();
void new_game();
void print_menu(int , char** , int , int , const char*);
void entrance_menu();
void draw_borders(int);
void draw_title(const char*);
void show_score_table(char* , int );


// show the options in pregame menu (Settings , Score Table , New Game , Continue Saved Game , Back)
void pregame_menu(){
    setlocale(LC_ALL, "");
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    bkgd(COLOR_PAIR(1));
    keypad(stdscr, TRUE); // enable keyboard input for the window
    curs_set(0); // hide cursor
    int highlight = 1;
    int choice = 0;
    int c;
    char *choices[] = {"Settings", "Score Table", "New Game" , "Continue Saved Game" , "Back to Entrance Menu"}; 
    setlocale(LC_ALL, "");

    while (1){
        clear();
        // draw_title("Pregame Menu");
        print_menu(highlight , choices , 5 , 10 , "Pregame Menu");
        c = getch();
        switch(c){
            case KEY_UP:
                if (highlight == 1){
                    highlight = 5;
                    break;
                }
                else{
                    highlight--;
                    break;
                }
            case KEY_DOWN:
                if (highlight == 5){
                    highlight = 1;
                    break;
                }
                else{
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
        settings();
    }
    else if (choice == 2){
        char my_username[] = "arvin";
        int start_page = 1;
        // setlocale(LC_ALL, "");
        // Show the score table starting from the first page
        show_score_table(my_username, start_page);
    }
    else if (choice == 3){
        // new_game();
    }
    else if (choice == 4){
        // show_saved_games();
    }
    else if (choice == 5){
        entrance_menu();
    }
    endwin(); 
}

// show the options in Settings (Level Of Difficulty , Songs , Hero's Color)
void settings(){
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    bkgd(COLOR_PAIR(1));
    keypad(stdscr, TRUE); // enable keyboard input for the window
    curs_set(0); // hide cursor
    int highlight = 1;
    int choice = 0;
    int c;
    char *choices[] = {"Level Of Difficulty", "Songs", "Hero's Color" , "Back to Pregame Menu"}; 

    while (1){
        // draw_title("Settings");
        print_menu(highlight , choices , 4 , 10 , "Settings");
        c = getch();
        switch(c){
            case KEY_UP:
                if (highlight == 1){
                    highlight = 4;
                    break;
                }
                else{
                    highlight--;
                    break;
                }
            case KEY_DOWN:
                if (highlight == 4){
                    highlight = 1;
                    break;
                }
                else{
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
        int level = 0; // 1 = easy ; 2 = medium ; 3 = hard
        choose_difficulty(level);
    }
    else if (choice == 2){
        int song;
        choose_song(&song);
    }
    else if (choice == 3){
        int color;
        choose_color(color);
    }
    else if (choice == 4){
        pregame_menu();
    }
    endwin(); 
}

// choose level of difficulty:  
                                //     1 for Easy   
                                //     2 for Medium   
                                //     3 for Hard   
void choose_difficulty(int level){
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    bkgd(COLOR_PAIR(1));
    keypad(stdscr, TRUE); // enable keyboard input for the window
    curs_set(0); // hide cursor
    int highlight = 1;
    int choice = 0;
    int c;
    char *choices[] = {"Easy (default)", "Medium", "Hard" , "Back"}; 
    while (1){
        // draw_title("Difficulty");
        print_menu(highlight , choices , 4 , 11 , "Difficulty");
        c = getch();
        switch(c){
            case KEY_UP:
                if (highlight == 1){
                    highlight = 4;
                    break;
                }
                else{
                    highlight--;
                    break;
                }
            case KEY_DOWN:
                if (highlight == 4){
                    highlight = 1;
                    break;
                }
                else{
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

    if (choice == 4){
        // level = 1;
        settings();
    }
    else{
        level = choice;
    }
    endwin(); 
}

// choose Hero's color:   
                                //     RED      1 
                                //     GREEN	2  
                                //     BLUE	    3  
                                //     MAGENTA  4   
                                //     CYAN	    5  
void choose_color(int color){
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    bkgd(COLOR_PAIR(1));
    keypad(stdscr, TRUE); // enable keyboard input for the window
    curs_set(0); // hide cursor
    int highlight = 1;
    int choice = 0;
    int c;
    char *choices[] = {"Red", "Green", "Blue" , "Magenta" , "Cyan" , "Back"}; 
    while (1){
        // draw_title("Hero's Color");
        print_menu(highlight , choices , 6 , 9 , "Player's Color");
        c = getch();
        switch(c){
            case KEY_UP:
                if (highlight == 1){
                    highlight = 6;
                    break;
                }
                else{
                    highlight--;
                    break;
                }
            case KEY_DOWN:
                if (highlight == 6){
                    highlight = 1;
                    break;
                }
                else{
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
    if (choice == 6){
        settings();
    }
    else{
        color = choice;
    }
    endwin(); 
}


// choose theme songs (for regular room type) 
                                //     1 for song1   
                                //     2 for song2   
                                //     3 for song3
void choose_song(int* song){

    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    bkgd(COLOR_PAIR(1));
    keypad(stdscr, TRUE); // enable keyboard input for the window
    curs_set(0); // hide cursor
    int highlight = 1;
    int choice = 0;
    int c;
    char *choices[] = {"Song 1 (default)", "Song 2" , "Song 3" , "None" ,"Back"}; 
    init_audio();
    while (1){
        // draw_title(/);
        print_menu(highlight , choices , 5 , 12 , "Theme Song");
        if(1 == highlight || 2 == highlight || 3 == highlight){
            choose_soundtrack(highlight);
        }
        else if (4 == highlight || 5 == highlight){
            stop_soundtrack();
        }

        c = getch();
        switch(c){
            case KEY_UP:
                if (highlight == 1){
                    highlight = 5;
                    break;
                }
                else{
                    highlight--;
                    break;
                }
            case KEY_DOWN:
                if (highlight == 5){
                    highlight = 1;
                    break;
                }
                else{
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

    if (choice == 5){
        stop_soundtrack();
        settings();
    }
    else{
        if (choice == 4){
            choice = 0;
        }
        // choose_soundtrack(choice);
        *song = choice;
    }
    
    endwin(); 
}


#endif