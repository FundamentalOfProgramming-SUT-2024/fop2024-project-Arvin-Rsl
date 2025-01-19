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
#include <math.h>

void new_map();
void print_map();
void print_room();
void add_door_and_window();
void make_corridor();
int can_corridor_pass();
void print_corridors();


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
    int n_doors_min = 2;
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
// checked

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

// function to make corridor between two doors, and add their positions to an array
void make_corridor(position door1 , 
                   room room1 ,
                   position door2 , 
                   room room2 ,
                   position *** corridors_of_all_levels , // address of a (position**)malloc(3 * sizeof(position *))
                   int level_num , // 1 , 2 , or 3
                   int *current_n_of_corr_characters_on_this_level, // address to an int (current n of corridor characters on this floor level)
                   room* all_rooms_on_this_level,
                   int n_rooms_on_this_level
                  ){
// position*** => address to a position** which has 3 elements (three floor levels)
    // each level has a position* which contains all the positions of all corridors on that level 
    
    // first we must know each door is on which wall of the room
    // north 0 , south 1 , west 3 , east 2 (just like our movement arrays)
    int dir1 , dir2;
    if(door1.x == room1.corner.x) dir1 = 0;
    else if(door1.x == room1.corner.x + room1.length - 1) dir1 = 1;
    else if(door1.y == room1.corner.y) dir1 = 3;
    else dir1 = 2;
    if(door2.x == room2.corner.x) dir2 = 0;
    else if(door2.x == room2.corner.x + room2.length - 1) dir2 = 1;
    else if(door2.y == room2.corner.y) dir2 = 3;
    else dir2 = 2;

    int x_moves[8] = {-1 , +1 , 0 , 0 , -1 , -1 , +1 , +1}; // up , down , right , left , up-right , up-left , down-right , down-left
    int y_moves[8] = {0 , 0 , +1 , -1 , +1 , -1 , +1 , -1};

    position current;

    int corr_length = 0;
    //// 1
    current.x = door2.x + x_moves[dir2];
    current.y = door2.y + y_moves[dir2];
    corr_length++;
    position* temp1 = realloc((*corridors_of_all_levels)[level_num - 1], 
                                     (*current_n_of_corr_characters_on_this_level + corr_length) * sizeof(position));
    if (temp1 == NULL) {
        mvprintw(LINES/2 , COLS/2 , "Memory allocation FAILED!");
        return;
    }
    (*corridors_of_all_levels)[level_num - 1] = temp1;
    (*corridors_of_all_levels)[level_num - 1][*current_n_of_corr_characters_on_this_level + corr_length - 1] = current;
    //// 2
    current.x += x_moves[dir2];
    current.y += y_moves[dir2];
    corr_length++;
    position* temp2 = realloc((*corridors_of_all_levels)[level_num - 1], 
                                     (*current_n_of_corr_characters_on_this_level + corr_length) * sizeof(position));
    if (temp2 == NULL) {
        mvprintw(LINES/2 , COLS/2 , "Memory allocation FAILED!");
        return;
    }
    (*corridors_of_all_levels)[level_num - 1] = temp2;
    (*corridors_of_all_levels)[level_num - 1][*current_n_of_corr_characters_on_this_level + corr_length - 1] = current;
    position destination = current;
    //// 3
    current.x = door1.x + x_moves[dir1];
    current.y = door1.y + y_moves[dir1];
    corr_length++;
    position* temp3 = realloc((*corridors_of_all_levels)[level_num - 1], 
                                     (*current_n_of_corr_characters_on_this_level + corr_length) * sizeof(position));
    if (temp3 == NULL) {
        mvprintw(LINES/2 , COLS/2 , "Memory allocation FAILED!");
        return;
    }
    (*corridors_of_all_levels)[level_num - 1] = temp3;
    (*corridors_of_all_levels)[level_num - 1][*current_n_of_corr_characters_on_this_level + corr_length - 1] = current;
    //// 4
    current.x += x_moves[dir1];
    current.y += y_moves[dir1];
    corr_length++;
    position* temp4 = realloc((*corridors_of_all_levels)[level_num - 1], 
                                     (*current_n_of_corr_characters_on_this_level + corr_length) * sizeof(position));
    if (temp4 == NULL) {
        mvprintw(LINES/2 , COLS/2 , "Memory allocation FAILED!");
        return;
    }
    (*corridors_of_all_levels)[level_num - 1] = temp4;
    (*corridors_of_all_levels)[level_num - 1][*current_n_of_corr_characters_on_this_level + corr_length - 1] = current;
    


    while(!(abs(current.x - destination.x) <= 1 && abs(current.y - destination.y) <= 1)){
        int random_direction = rand() % 4; // up 0 , down 1 , right 2 , left 3 , up-right 4 , up-left 5 , down-right 6 , down-left 7
        int x_new = current.x + x_moves[random_direction];
        int y_new = current.y + y_moves[random_direction];

        double current_distance = sqrt( pow((destination.x - current.x) , 2) + pow((destination.y - current.y) , 2) );
        double new_distance = sqrt( pow((destination.x - x_new) , 2) + pow((destination.y - y_new) , 2) );

        if (new_distance <= current_distance && can_corridor_pass(x_new , y_new , all_rooms_on_this_level , n_rooms_on_this_level)){
            current.x = x_new;
            current.y = y_new;
            corr_length++;
            position* temp = realloc((*corridors_of_all_levels)[level_num - 1], 
                                     (*current_n_of_corr_characters_on_this_level + corr_length) * sizeof(position));
            if (temp == NULL) {
                mvprintw(LINES/2 , COLS/2 , "Memory allocation FAILED!");
                return;
            }

            (*corridors_of_all_levels)[level_num - 1] = temp;
            (*corridors_of_all_levels)[level_num - 1][*current_n_of_corr_characters_on_this_level + corr_length - 1] = current;
        }

    }
    *current_n_of_corr_characters_on_this_level += corr_length;
}
// checked (can be improved)

// function to check if there is a room (corridor cannot pass) or not
int can_corridor_pass(int x , int y , room* all_rooms_on_this_level , int n_rooms_on_this_level){
    if (x <= 0 || y <= 0 || x >= LINES - 1 || y >= COLS - 1){
        return 0;
    }

    for(int i = 0 ; i < n_rooms_on_this_level ; i++){
        room Room = all_rooms_on_this_level[i];
        if (x >= Room.corner.x  && 
                x < Room.corner.x + Room.length &&
                y >= Room.corner.y && 
                y < Room.corner.y + Room.width ){
            return 0;
        }
    }

    
    // char there = mvinch(x , y) & A_CHARTEXT;
    // if (there != '_' && there != '|' && there != '=' && there != '.' && there != ',' && there != '-' && there != '~' && there != 'O'){
    //     return 1;
    // }
    // else{
    //     return 0;
    // }

    return 1;

}
// checked 


// function to print corridors 
void print_corridors(position* corridors_of_this_level , int n_of_corr_characters_on_this_level){
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    for (int i = 0; i < n_of_corr_characters_on_this_level; i++){
        mvprintw(corridors_of_this_level[i].x, corridors_of_this_level[i].y, "#");
    }
    attroff(COLOR_PAIR(1));
}
// checked

// create new map
void new_map(int difficulty){
    // srand(time(NULL));
    // int n_rooms_max = difficulty * 8; 
    // int n_rooms_min = 6;
    // int n_rooms = rand() % ((n_rooms_max - n_rooms_min)+1) + n_rooms_min;
    

    // position** corridors_of_all_levels = (position**) malloc(3 * sizeof(position*));
    // make_corridor(door1 , door2, &corridors_of_all_levels , level_num);
}
// incomplete!!

#endif