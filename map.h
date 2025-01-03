#ifndef MAP_H
#define MAP_H
////  library : Creating Map   ////

// Arvin Rasulzadeh
// 403110422

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <ctype.h>
#include <ncurses.h>

void new_map();
void print_map();
void print_room();
void add_door_and_window();

// x (row) and y (col)
typedef struct {
    int x; // row
    int y; // col
} position;

// room
typedef struct {
    // length and width include the wall characters
    int length; // |
                // |
                // |
                // |
    int width;  // ____
    int hide;   // if 0, the Room is visible
    int number_of_doors;
    int number_of_windows;
    position corner; // corner = upper left corner of the room
    int type; // 0 => Regular Room
              // 1 => Battle Room (trap)
              // 2 => Enchant Room
              // 3 => Treasure Room ( Third is the charm :D )
              // 4 => Nightmare Room
/*  Type of Room:    Pillar Char:       Floor Char      Floor & Pillar Color      int type  
    Regular Room          O                 .                   White                 0
    Battle Room        No Pillar            .                   Red                   1
    Enchant Room          O                 ,                   Magenta               2
    Treasure Room      No Pillar            -                   Yellow                3
    Nightmare Room        O                 ~                   Blue                  4

*/
} room;

// function to print room
void print_room(room Room){
    start_color();
    attron(COLOR_BLACK);
    position ul_corner = Room.corner;
    if (!Room.hide){ // visible

        // WALLS
        // northern wall
        for (int i = ul_corner.y + 1 ; i < ul_corner.y + Room.width - 1 ; i++){
            mvprintw(ul_corner.x , i , "_");
        }

        // southern wall
        for (int i = ul_corner.y + 1 ; i < ul_corner.y + Room.width - 1 ; i++){
            mvprintw(ul_corner.x + Room.length - 1 , i , "_");
        }

        // western wall
        for (int i = ul_corner.x + 1 ; i < ul_corner.x + Room.length ; i++){
            mvprintw(i , ul_corner.y , "|");
        }

        // eastern wall
        for (int i = ul_corner.x + 1 ; i < ul_corner.x + Room.length ; i++){
            mvprintw(i , ul_corner.y + Room.width - 1, "|");
        }

        // FLOOR
        // determine floor's char
        char floor;
        if (Room.type == 0 || Room.type == 1){
            floor = '.';
        }
        else if (Room.type == 2){
            floor = ',';
        }
        else if (Room.type == 3){
            floor = '-';
        }
        else if (Room.type == 4){
            floor = '~';
        }
        // printf floor
        start_color();
        init_pair(0 , COLOR_WHITE , COLOR_BLACK); 
        init_pair(1 , COLOR_RED , COLOR_BLACK); 
        init_pair(2 , COLOR_MAGENTA , COLOR_BLACK); 
        init_pair(3 , COLOR_YELLOW , COLOR_BLACK); 
        init_pair(4 , COLOR_BLUE , COLOR_BLACK); 
        attron(COLOR_PAIR(Room.type));
        for (int y = ul_corner.y + 1; y < ul_corner.y + Room.width - 1 ; y++){
            for (int x = ul_corner.x + 1 ; x < ul_corner.x + Room.length - 1 ; x++){
                mvprintw(x , y , "%c" , floor);
            }
        }
        attroff(COLOR_PAIR(Room.type));
    }
}

// function to add the doors and windows to room
void add_door_and_window(){}

// create new map
void new_map(int difficulty){
    // srand(time(NULL));
    // int n_rooms_max = difficulty * 8; 
    // int n_rooms_min = 6;
    // int n_rooms = rand() % ((n_rooms_max - n_rooms_min)+1) + n_rooms_min;

}
#endif