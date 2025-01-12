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
void make_corridor();


// x (row) and y (col)
typedef struct {
    int x; // row
    int y; // col
} position;

// room
typedef struct {
    int floor_level; // the floor/level/ground where room is located (start floor: 1 , end floor: 4)
    int room_number; // room's number in that floor
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
    int doors_x[3];
    int doors_y[3];
    
    int windows_x[2];
    int windows_y[2];
    
} room;

// function to add the doors and windows to room 
void add_door_and_window(room* Room){
    srand(time(NULL));
    int n_doors_max = 3;
    int n_doors_min = 1;
    int n_doors = rand() % ((n_doors_max - n_doors_min)+1) + n_doors_min;
    Room->number_of_doors = n_doors;
    int n_windows_max = 2;
    int n_windows_min = 0;
    int n_windows = rand() % ((n_windows_max - n_windows_min)+1);
    Room->number_of_windows = n_windows;
    int x_north = Room->corner.x;
    int x_south = Room->corner.x + Room->length - 1;
    int y_west = Room->corner.y;
    int y_east = Room->corner.y + Room->width - 1;

    // adding (x,y) values for doors
    for (int i = 0 ; i < n_doors ; i++){
        int random_wall = rand() % 4;   // 0 : northern wall
                                        // 1 : southern wall
                                        // 2 : western wall
                                        // 3 : eastern wall
        if(random_wall == 0){
            int y_max = y_east - 1;
            int y_min = y_west + 1;
            int y = rand() % ((y_max - y_min)+1) + y_min;
            Room->doors_x[i] = x_north;
            Room->doors_y[i] = y;
        }
        else if (random_wall == 1){
            int y_max = y_east - 1;
            int y_min = y_west + 1;
            int y = rand() % ((y_max - y_min)+1) + y_min;
            Room->doors_x[i] = x_south;
            Room->doors_y[i] = y;
        }        
        else if (random_wall == 2){
            int x_max = x_south - 1;
            int x_min = x_north + 1;
            int x = rand() % ((x_max - x_min)+1) + x_min;
            Room->doors_x[i] = x;
            Room->doors_y[i] = y_west;
        }        
        else if (random_wall == 3){
            int x_max = x_south - 1;
            int x_min = x_north + 1;
            int x = rand() % ((x_max - x_min)+1) + x_min;
            Room->doors_x[i] = x;
            Room->doors_y[i] = y_east;
        }
    }
    // adding (x,y) values for windows
    for (int i = 0 ; i < n_windows ; i++){
        int random_wall = rand() % 4;   // 0 : northern wall
                                        // 1 : southern wall
                                        // 2 : western wall
                                        // 3 : eastern wall
        if(random_wall == 0){
            int y_max = y_east - 1;
            int y_min = y_west + 1;
            int y = rand() % ((y_max - y_min)+1) + y_min;
            Room->windows_x[i] = x_north;
            Room->windows_y[i] = y;
        }
        else if (random_wall == 1){
            int y_max = y_east - 1;
            int y_min = y_west + 1;
            int y = rand() % ((y_max - y_min)+1) + y_min;
            Room->windows_x[i] = x_south;
            Room->windows_y[i] = y;
        }        
        else if (random_wall == 2){
            int x_max = x_south - 1;
            int x_min = x_north + 1;
            int x = rand() % ((x_max - x_min)+1) + x_min;
            Room->windows_x[i] = x;
            Room->windows_y[i] = y_west;
        }        
        else if (random_wall == 3){
            int x_max = x_south - 1;
            int x_min = x_north + 1;
            int x = rand() % ((x_max - x_min)+1) + x_min;
            Room->windows_x[i] = x;
            Room->windows_y[i] = y_east;
        }
    }
}
// checkedd

// function to print room 
void print_room(room *Room){ // pay attention to the fact that walls are also taken into account for "length" and "width"
                             // we set the minimum of length and width to 6, so the room size is at least 4x4
    start_color();
    attron(COLOR_BLACK);
    position ul_corner = Room->corner;
    if (!Room->hide){ // visible

        // WALLS
        // northern wall
        for (int i = ul_corner.y + 1 ; i < ul_corner.y + Room->width - 1 ; i++){
            mvprintw(ul_corner.x , i , "_");
        }

        // southern wall
        for (int i = ul_corner.y + 1 ; i < ul_corner.y + Room->width - 1 ; i++){
            mvprintw(ul_corner.x + Room->length - 1 , i , "_");
        }

        // western wall
        for (int i = ul_corner.x + 1 ; i < ul_corner.x + Room->length ; i++){
            mvprintw(i , ul_corner.y , "|");
        }

        // eastern wall
        for (int i = ul_corner.x + 1 ; i < ul_corner.x + Room->length ; i++){
            mvprintw(i , ul_corner.y + Room->width - 1, "|");
        }

        // FLOOR
        // determine floor's char
        char floor;
        if (Room->type == 0 || Room->type == 1){
            floor = '.';
        }
        else if (Room->type == 2){
            floor = ',';
        }
        else if (Room->type == 3){
            floor = '-';
        }
        else if (Room->type == 4){
            floor = '~';
        }
        // printf floor
        start_color();
        init_pair(0 , COLOR_WHITE , COLOR_BLACK); 
        init_pair(1 , COLOR_RED , COLOR_BLACK); 
        init_pair(2 , COLOR_MAGENTA , COLOR_BLACK); 
        init_pair(3 , COLOR_YELLOW , COLOR_BLACK); 
        init_pair(4 , COLOR_BLUE , COLOR_BLACK); 
        attron(COLOR_PAIR(Room->type));
        for (int y = ul_corner.y + 1; y < ul_corner.y + Room->width - 1 ; y++){
            for (int x = ul_corner.x + 1 ; x < ul_corner.x + Room->length - 1 ; x++){
                mvprintw(x , y , "%c" , floor);
            }
        }
        attroff(COLOR_PAIR(Room->type));

        // Door(s)
        for (int i = 0 ; i < Room->number_of_doors ; i++){
            mvprintw(Room->doors_x[i],  Room->doors_y[i] , "+");
        }
        // Window(s)
        for (int i = 0 ; i < Room->number_of_windows ; i++){
            mvprintw(Room->windows_x[i],  Room->windows_y[i] , "=");
        }
    }
}
//checked

// function to make corridor between two doors using the dfs method
void make_corridor(position door1 , position door2){
}
// incomplete

// create new map
void new_map(int difficulty){
    srand(time(NULL));
    int n_rooms_max = difficulty * 8; 
    int n_rooms_min = 6;
    int n_rooms = rand() % ((n_rooms_max - n_rooms_min)+1) + n_rooms_min;
}
// incomplete

#endif