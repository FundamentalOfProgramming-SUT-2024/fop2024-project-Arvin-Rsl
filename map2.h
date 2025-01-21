#ifndef MAP2_H
#define MAP2_H
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

// x (row) and y (col)
typedef struct {
    int x; // row
    int y; // col
} position;

// room
typedef struct {
    int floor_level; // the floor/level/ground where room is located (start floor: 1 , end floor: 4)
    int room_number; // room's number in that floor , starting from 1
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

void new_map();
void print_map();
void print_room();
void print_corridors();
void add_door_and_window();
void make_corridor();
int can_corridor_pass();
int number_of_rooms();
int room_valid();
position closest_door();
room closest_room_except_previous();
int find_min_y();
void sort_rooms();

// function to add the doors and windows to room 
void add_door_and_window(room* Room , int n_rooms){
    srand(time(NULL));
    // int n_doors_max = 3;
    // int n_doors_min = 2;
    // int n_doors = rand() % ((n_doors_max - n_doors_min)+1) + n_doors_min;
    int n_doors = 2;
    if (Room->room_number == 1 || Room->room_number == n_rooms){ n_doors = 1;}
    Room->number_of_doors = n_doors;
    int n_windows = rand() % 3;
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
    // stepping away from the wall
    int dir1 , dir2;
    if(door1.x == room1.corner.x) dir1 = 0;
    else if(door1.x == room1.corner.x + room1.length - 1) dir1 = 1;
    else if(door1.y == room1.corner.y) dir1 = 3;
    else if(door1.y == room1.corner.y + room1.width - 1) dir1 = 2;
    if(door2.x == room2.corner.x) dir2 = 0;
    else if(door2.x == room2.corner.x + room2.length - 1) dir2 = 1;
    else if(door2.y == room2.corner.y) dir2 = 3;
    else if(door2.y == room2.corner.y + room2.width - 1) dir2 = 2;

    int x_moves[8] = {-1 , +1 , 0 , 0 , -1 , -1 , +1 , +1}; // up , down , right , left , up-right , up-left , down-right , down-left
    int y_moves[8] = {0 , 0 , +1 , -1 , +1 , -1 , +1 , -1};

    position current = {0,0};

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
    // current.x += x_moves[dir2];
    // current.y += y_moves[dir2];
    // corr_length++;
    // position* temp2 = realloc((*corridors_of_all_levels)[level_num - 1], 
    //                                  (*current_n_of_corr_characters_on_this_level + corr_length) * sizeof(position));
    // if (temp2 == NULL) {
    //     mvprintw(LINES/2 , COLS/2 , "Memory allocation FAILED!");
    //     return;
    // }
    // (*corridors_of_all_levels)[level_num - 1] = temp2;
    // (*corridors_of_all_levels)[level_num - 1][*current_n_of_corr_characters_on_this_level + corr_length - 1] = current;
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
    // //// 4
    // current.x += x_moves[dir1];
    // current.y += y_moves[dir1];
    // corr_length++;
    // position* temp4 = realloc((*corridors_of_all_levels)[level_num - 1], 
    //                                  (*current_n_of_corr_characters_on_this_level + corr_length) * sizeof(position));
    // if (temp4 == NULL) {
    //     mvprintw(LINES/2 , COLS/2 , "Memory allocation FAILED!");
    //     return;
    // }
    // (*corridors_of_all_levels)[level_num - 1] = temp4;
    // (*corridors_of_all_levels)[level_num - 1][*current_n_of_corr_characters_on_this_level + corr_length - 1] = current;
    


    while( !(abs(current.x - destination.x) <= 1 && abs(current.y - destination.y) <= 1) ){

        int not_valid_dirs = 0;
        int can_pass_valid_dir = 0;
        int random_direction;

        for (int d = 0 ; d < 4 ; d++){
            int x_new = current.x + x_moves[d];
            int y_new = current.y + y_moves[d];
            double current_distance = sqrt( pow((destination.x - current.x) , 2) + pow((destination.y - current.y) , 2) );
            double new_distance = sqrt( pow((destination.x - x_new) , 2) + pow((destination.y - y_new) , 2) );
        
            if( (new_distance > current_distance) && !(can_corridor_pass(x_new , y_new , all_rooms_on_this_level , n_rooms_on_this_level))){
                not_valid_dirs++;
            }
            if(can_corridor_pass(x_new , y_new , all_rooms_on_this_level , n_rooms_on_this_level)){
                can_pass_valid_dir = d;
            }
        }

        if(not_valid_dirs == 4){
            // none of the four directions satisfies the two conditions of (getting closer to destination) and (not entering a room) at the same time
            random_direction = can_pass_valid_dir;

            // so we just go for a position that doesn't enter a room (even if we get far)
            current.x += x_moves[random_direction];
            current.y += y_moves[random_direction];
            corr_length++;
            position* temp = realloc((*corridors_of_all_levels)[level_num - 1], 
                                        (*current_n_of_corr_characters_on_this_level + corr_length) * sizeof(position));
            if (temp == NULL) {
                mvprintw(LINES/2 , COLS/2 , "Memory allocation FAILED!");
                break;;
            }

            (*corridors_of_all_levels)[level_num - 1] = temp;
            (*corridors_of_all_levels)[level_num - 1][*current_n_of_corr_characters_on_this_level + corr_length - 1] = current;
        }

        else{
            random_direction = rand() % 4;
            // again (including the checking of new_distance <= current_distance)
            int x_new = current.x + x_moves[random_direction];
            int y_new = current.y + y_moves[random_direction];

            double current_distance = sqrt( pow((destination.x - current.x) , 2) + pow((destination.y - current.y) , 2) );
            double new_distance = sqrt( pow((destination.x - x_new) , 2) + pow((destination.y - y_new) , 2) );

            if ( (new_distance <= current_distance) && can_corridor_pass(x_new , y_new , all_rooms_on_this_level , n_rooms_on_this_level) ){
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
    }
    
    *current_n_of_corr_characters_on_this_level += corr_length;
}
// checked (can be improved)

// function to check if there is a room (corridor cannot pass) or not
int can_corridor_pass(int x , int y , room* all_rooms_on_this_level , int n_rooms_on_this_level){
    if (x <= 0 || y <= 0 || x >= LINES  || y >= COLS ){
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

// random number of rooms
int number_of_rooms(int difficulty){
    int n_rooms_max = pow(1.3 , difficulty )* 6; 
    int n_rooms_min = 6;
    int n_rooms = rand() % ((n_rooms_max - n_rooms_min)+1) + n_rooms_min;
    return n_rooms;
}
// checked

// create new map
void new_map(int difficulty ,
             int n_rooms , 
             position *** address_corridors_of_all_levels , 
             int level_num,
             room*** address_rooms_of_all_levels
             ){
    int room_types[10] = {0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 2 , 4};

    int max_length , max_width;
    switch (difficulty)
    {
    case 1:
        max_length = 17;
        max_width = 26;
        break;
    case 2:
        max_length = 15;
        max_width = 22;
        break;
    case 3:
        max_length = 13;
        max_width = 20;
        break;
    }

    int max_y_for_corner = COLS - (3+max_width),
        min_y_for_corner = 3, 
        max_x_for_corner = LINES - (3+max_length), 
        min_x_for_corner = 3;

    int done_rooms = 0;
    do {
        room ROOM;
        ROOM.floor_level = level_num;
        ROOM.type = room_types[rand() % 10];
        ROOM.length = rand() % (max_length - 6) + 6;
        ROOM.width = rand() % (max_width - 6) + 6;
        ROOM.corner.x = rand() % (max_x_for_corner - min_x_for_corner) + min_x_for_corner;
        ROOM.corner.y = rand() % (max_y_for_corner - min_y_for_corner) + min_y_for_corner;
        if (room_valid(ROOM , address_rooms_of_all_levels , level_num , done_rooms)){
            done_rooms++;
            ROOM.room_number = done_rooms;

            room* temp = realloc((*address_rooms_of_all_levels)[level_num - 1], done_rooms * sizeof(room));
            if (temp == NULL) {
                mvprintw(LINES/2 , COLS/2 , "Memory allocation FAILED!");
                return;
            }

            (*address_rooms_of_all_levels)[level_num - 1] = temp;
            (*address_rooms_of_all_levels)[level_num - 1][done_rooms - 1] = ROOM;
        }

    } while(done_rooms < n_rooms);

    sort_rooms(*(address_rooms_of_all_levels)[level_num - 1] , n_rooms);
    
}
// incomplete


// position closest_door(position start_door , room*** address_rooms_of_all_levels , int level_num, int room_number , int number_of_rooms, room * closest_room){
//     double distance = LINES; // s.th. large for initializing
//     position closest;
//     for (int i = 0 ; i < number_of_rooms ; i++){
//         if(i != room_number - 1){ // other rooms!
//             room roooom = (*address_rooms_of_all_levels)[level_num - 1][i];
//             for (int k = 0 ; k < roooom.number_of_doors ; k++){
//                 int x = roooom.doors_x[k];
//                 int y = roooom.doors_y[k];
//                 double temp_distance = sqrt( pow((start_door.x - x) , 2) + pow((start_door.y - y) , 2) );
//                 if (temp_distance < distance){
//                     distance = temp_distance;
//                     closest.x = roooom.doors_x[k];
//                     closest.y = roooom.doors_y[k];
//                     *closest_room = roooom;
//                 }
//             }
//         }
//     }

//     return closest;

// }


// check if new room has overlap with previous ones
int room_valid(room ROOM , room*** address_rooms_of_all_levels , int level_num , int i){
    int x_min = ROOM.corner.x , x_max = ROOM.corner.x + ROOM.length;
    int y_min = ROOM.corner.y , y_max = ROOM.corner.y + ROOM.width;

    for (int j = 0 ; j < i ; j++){
        room checking = (*address_rooms_of_all_levels)[level_num - 1][j];
        int check_x_min = checking.corner.x - 3, check_x_max = checking.corner.x + checking.length + 3;
        int check_y_min = checking.corner.y - 3, check_y_max = checking.corner.y + checking.width + 3;

        if(( (x_max >= check_x_min && x_max <= check_x_max) || (x_min >= check_x_min && x_min <= check_x_max) )
             && ( (y_max >= check_y_min && y_max <= check_y_max) || (y_min >= check_y_min && y_min <= check_y_max) )){
            return 0;
        }
    }
    return 1;
}
// checked

// function that returns the index of the room with the least corner.x
int find_min_y(room* my_rooms, int n_rooms) {
    int min_index = 0;
    for (int i = 1; i < n_rooms; i++) {
        if (my_rooms[i].corner.y < my_rooms[min_index].corner.y) {
            min_index = i;
        }
    }
    return min_index;
}
// 

// function to sort rooms (based on how close they are to each other)
void sort_rooms(room* my_rooms, int n_rooms) {
    // find the first room with the smallest corner.y value
    int start_index = find_min_y(my_rooms, n_rooms);
    
    // swap it to the first position
    room temp = my_rooms[0];
    my_rooms[0] = my_rooms[start_index];
    my_rooms[start_index] = temp;
    

    // select the closest room 
    for (int i = 1; i < n_rooms; i++) {
        int nearest_index = i;
        double min_distance = sqrt(pow(my_rooms[i - 1].corner.x - my_rooms[i].corner.x, 2) + pow(my_rooms[i - 1].corner.y - my_rooms[i].corner.y, 2));
       
        for (int j = i + 1; j < n_rooms; j++) {
            double d = sqrt(pow(my_rooms[i - 1].corner.x - my_rooms[j].corner.x, 2) + pow(my_rooms[i - 1].corner.y - my_rooms[j].corner.y, 2));
            if (d < min_distance) {
                min_distance = d;
                nearest_index = j;
            }
        }

        // swap the nearest room with the current
        temp = my_rooms[i];
        my_rooms[i] = my_rooms[nearest_index];
        my_rooms[nearest_index] = temp;
    }

    for (int k = 0 ; k < n_rooms ; k++){
        my_rooms[k].room_number = k + 1;
    }
}

#endif