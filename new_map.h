#ifndef NEW_MAP_H
#define NEW_MAP_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <ctype.h>
#include <ncurses.h>
#include <math.h>
#include <unistd.h> // for sleep() function (randomizing existance of windows between rooms)
#define MAX_CORR (184 * 45) 

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
    int number_of_pillars;
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
    int doors_x[2];
    int doors_y[2];
    
    // int windows_y[2]; // the first two for windows and the rest for pillars
    // int windows_x[2]; // the first two for windows and the rest for pillars
    // int n_pillars; /// always 3 pillars
    int pillars_x[3];
    int pillars_y[3];
    
    int n_foods;
    int picked_foods[3]; // 1 if food is picked (don't print it anymore); 0 otherwise
    int foods_x[3];
    int foods_y[3];

    int n_golds;
    int picked_golds[3]; // 1 if food is picked (don't print it anymore); 0 otherwise
    int golds_x[3];
    int golds_y[3];
    
} room;

int valid_4_corr(int , int);
void print_black_rooms(int , room** , int);
void build_corr(int , position*** , room ** , int , int*);

void new_map();
void print_map();
void print_room();
void print_corridors();
void add_door_and_window();
void add_pillars();
void add_food();
void add_gold();
int number_of_rooms();
int room_valid();
int find_min_y();
void sort_rooms();
int can_corridor_pass(int  , int , room*  , int );

// function to add golds (U+2666) to room 
void add_gold(room** address_rooms_this_level , int n_rooms){ // first food, then gold
    srand(time(NULL));
    for (int i = 0 ; i < n_rooms ; i++){
    
        room r1 = (*address_rooms_this_level)[i];
        int x_north1 = r1.corner.x;
        int x_south1 = r1.corner.x + r1.length - 1;
        int y_west1 = r1.corner.y;
        int y_east1 = r1.corner.y + r1.width - 1;
        int k = 0;

        while (k < r1.n_golds ){
            int x = rand() % (x_south1 - x_north1 - 3) + x_north1 + 2;
            int y = rand() % (y_east1 - y_west1 - 3) + y_west1 + 2;

            int overlap = 0;
            for (int P = 0 ; P < 3 ; P++){
                if(x == r1.pillars_x[P] && y == r1.pillars_y[P]){
                    // the random location overlaps with a pillar
                    overlap = 1;
                }
            }
            for (int F = 0 ; F < r1.n_foods ; F++){
                if(x == r1.foods_x[F] && y == r1.foods_y[F]){
                    // the random location overlaps with a food
                    overlap = 1;
                }
            }
            

            if(!overlap){
                (*address_rooms_this_level)[i].golds_x[k] = x;
                (*address_rooms_this_level)[i].golds_y[k] = y;

                k++;
            }

        }
        
    }

}

// function to add the regular foods ( 'f' ) to room 
void add_food(room** address_rooms_this_level , int n_rooms){ // first food, then gold
    srand(time(NULL));
    for (int i = 0 ; i < n_rooms ; i++){
    
        room r1 = (*address_rooms_this_level)[i];
        int x_north1 = r1.corner.x;
        int x_south1 = r1.corner.x + r1.length - 1;
        int y_west1 = r1.corner.y;
        int y_east1 = r1.corner.y + r1.width - 1;
        int k = 0;

        while (k < r1.n_foods ){
            int x = rand() % (x_south1 - x_north1 - 3) + x_north1 + 2;
            int y = rand() % (y_east1 - y_west1 - 3) + y_west1 + 2;

            int overlap = 0;
            for (int P = 0 ; P < 3 ; P++){
                if(x == r1.pillars_x[P] && y == r1.pillars_y[P]){
                    // the random location overlaps with a pillar
                    overlap = 1;
                }
            }

            if(!overlap){
                (*address_rooms_this_level)[i].foods_x[k] = x;
                (*address_rooms_this_level)[i].foods_y[k] = y;

                k++;
            }

        }
    
    }

}

// function to add the pillars ( 'O' ) to room 
void add_pillars(room** address_rooms_this_level , int n_rooms){
    srand(time(NULL));
    for (int i = 0 ; i < n_rooms ; i++){
    
        room r1 = (*address_rooms_this_level)[i];

        for (int k = 0 ; k < 3 ; k++){ // always 3 pillars
            int x_north1 = r1.corner.x;
            int x_south1 = r1.corner.x + r1.length - 1;
            int y_west1 = r1.corner.y;
            int y_east1 = r1.corner.y + r1.width - 1;

            int x = rand() % (x_south1 - x_north1 - 3) + x_north1 + 2;
            int y = rand() % (y_east1 - y_west1 - 3) + y_west1 + 2;
            
            (*address_rooms_this_level)[i].pillars_x[k] = x;
            (*address_rooms_this_level)[i].pillars_y[k] = y;
        }
    }

}

// function to build the corridors of 1 floor level
void build_corr(int n_rooms_level, position*** address_corridors_of_all_levels, room ** rooms_of_all_levels, int level_num, int* ptr_corr_count) {
    int x_moves[8] = {-1, +1, +0, +0, -1, -1, +1, +1}; // up, down, right, left, up-right, up-left, down-right, down-left
    int y_moves[8] = {+0, +0, +1, -1, +1, -1, +1, -1};
    initscr();
    initscr();
    nodelay(stdscr, TRUE);
    noecho();
    cbreak();
    curs_set(FALSE);
    start_color(); 
    srand(time(NULL));  
    for (int i = 0; i < n_rooms_level - 1; i++) {
        position start;
        position end;
        start.x = rooms_of_all_levels[level_num - 1][i].doors_x[0];
        start.y = rooms_of_all_levels[level_num - 1][i].doors_y[0];
        end.x = rooms_of_all_levels[level_num - 1][i + 1].doors_x[1];
        end.y = rooms_of_all_levels[level_num - 1][i + 1].doors_y[1];

        int dir1, dir2;
        if (start.x == rooms_of_all_levels[level_num - 1][i].corner.x) dir1 = 0;
        else if (start.x == rooms_of_all_levels[level_num - 1][i].corner.x + rooms_of_all_levels[level_num - 1][i].length - 1) dir1 = 1;
        else if (start.y == rooms_of_all_levels[level_num - 1][i].corner.y) dir1 = 3;
        else if (start.y == rooms_of_all_levels[level_num - 1][i].corner.y + rooms_of_all_levels[level_num - 1][i].width - 1) dir1 = 2;
        if (end.x == rooms_of_all_levels[level_num - 1][i + 1].corner.x) dir2 = 0;
        else if (end.x == rooms_of_all_levels[level_num - 1][i + 1].corner.x + rooms_of_all_levels[level_num - 1][i + 1].length - 1) dir2 = 1;
        else if (end.y == rooms_of_all_levels[level_num - 1][i + 1].corner.y) dir2 = 3;
        else if (end.y == rooms_of_all_levels[level_num - 1][i + 1].corner.y + rooms_of_all_levels[level_num - 1][i + 1].width - 1) dir2 = 2;
        start.x += x_moves[dir1];
        start.y += y_moves[dir1];
        end.x += x_moves[dir2];
        end.y += y_moves[dir2];

        position current;
        current.x = start.x;
        current.y = start.y;
        int delta_x = end.x - current.x;
        int sign_delta_x = 0;
        int sign_delta_y = 0;
        if(delta_x < 0){
            sign_delta_x = -1;
        }
        else{
            sign_delta_x = 1;
        }
        int delta_y = end.y - start.y;
        int corr_length = abs(delta_x) + abs(delta_y) + 1;
        int y_break;

        if(delta_y < 0){
            sign_delta_y = -1;
        }
        else if(delta_y >0){
            sign_delta_y = 1;
        }

        if (delta_y != 0) {
            if(rooms_of_all_levels[level_num - 1][i - 1].corner.y + rooms_of_all_levels[level_num - 1][i - 1].width - 1  >=  rooms_of_all_levels[level_num - 1][i].corner.y + rooms_of_all_levels[level_num - 1][i].width - 1){
                y_break = rand() % ( abs(end.y - (rooms_of_all_levels[level_num - 1][i - 1].corner.y + rooms_of_all_levels[level_num - 1][i - 1].width)) ) + rooms_of_all_levels[level_num - 1][i - 1].corner.y + rooms_of_all_levels[level_num - 1][i - 1].width + 1;
            }
            else{
                y_break = rand() % delta_y + start.y;
            }
            if(y_break == end.y || y_break == end.y + 1){
                y_break--;
            }

            if(end.x > rooms_of_all_levels[level_num - 1][i - 1].corner.x 
               && rooms_of_all_levels[level_num - 1][i - 1].corner.y + rooms_of_all_levels[level_num - 1][i - 1].width - 1 >= start.y){
                y_break = end.y - 1;
            }
            for (int K = 0 ; start.y + K != y_break + sign_delta_y; K += sign_delta_y){
                // if (*ptr_corr_count + K < MAX_CORR) {
                //     (*address_corridors_of_all_levels)[level_num - 1][*ptr_corr_count + K].x = start.x;
                //     (*address_corridors_of_all_levels)[level_num - 1][*ptr_corr_count + K].y = start.y + K;
                // } else {
                //     printf("Index out of bounds: %d\n", *ptr_corr_count + K);
                //     fflush(stdout);
                //     break;
                // }
                (*address_corridors_of_all_levels)[level_num - 1][*ptr_corr_count + abs(K)].x = start.x ;
                (*address_corridors_of_all_levels)[level_num - 1][*ptr_corr_count + abs(K)].y = start.y + K;
            }
            for (int J = 0 ; (start.x  + J != end.x + 2*sign_delta_x) ; J += sign_delta_x){
                // if (*ptr_corr_count + (y_break - start.y) + abs(J) + 1 < MAX_CORR) {
                // (*address_corridors_of_all_levels)[level_num - 1][*ptr_corr_count + (y_break - start.y) + abs(J) + 1].x = (start.x + sign_delta_x) + J;
                // (*address_corridors_of_all_levels)[level_num - 1][*ptr_corr_count + (y_break - start.y) + abs(J) + 1].y = y_break;
                // } else {
                // // printf("Index out of bounds: %d\n", *ptr_corr_count + (y_break - start.y) + abs(J) + 1);
                // // fflush(stdout);
                // break;
                // }
                (*address_corridors_of_all_levels)[level_num - 1][*ptr_corr_count + abs(y_break - start.y) + abs(J) + 1].x = (start.x + sign_delta_x) + J ;
                (*address_corridors_of_all_levels)[level_num - 1][*ptr_corr_count + abs(y_break - start.y) + abs(J) + 1].y = y_break;
            }
            for (int L = 0 ; (y_break + L != end.y + sign_delta_y) ; L+=sign_delta_y){
                // if (*ptr_corr_count + (y_break - start.y) + abs(delta_x) + 1 + L < MAX_CORR) {
                //     (*address_corridors_of_all_levels)[level_num - 1][*ptr_corr_count + (y_break - start.y) + abs(delta_x) + 1 + L].x = end.x;
                //     (*address_corridors_of_all_levels)[level_num - 1][*ptr_corr_count + (y_break - start.y) + abs(delta_x) + 1 + L].y = y_break + L;
                // } else {
                //     // printf("Index out of bounds: %d\n", *ptr_corr_count + (y_break - start.y) + abs(delta_x) + 1 + L);
                //     // fflush(stdout);
                //     break;
                // }
                (*address_corridors_of_all_levels)[level_num - 1][*ptr_corr_count + abs(y_break - start.y) + abs(delta_x)+1 + abs(L)].x = end.x ;
                (*address_corridors_of_all_levels)[level_num - 1][*ptr_corr_count + abs(y_break - start.y) + abs(delta_x)+1 + abs(L)].y = y_break + L;
            }
            *ptr_corr_count += corr_length;
            // printf("corridor between %d and %d done\n" , i , i+1);
            if(*ptr_corr_count > MAX_CORR){break;}
            // char c = getch();
            // mvprintw(LINES/2 , COLS/2 , "%c" , c);
            for (int roo = 0 ; roo < n_rooms_level ; roo ++){
                print_room(rooms_of_all_levels[level_num - 1] + roo);
            }
            print_corridors((*address_corridors_of_all_levels)[level_num - 1] , *ptr_corr_count);
            // sleep(1);
            refresh();
        } 
        
        else{ // end.y = start.y
            for (int J = 0 ; (start.x  + J != end.x + sign_delta_x) ; J += sign_delta_x){
                (*address_corridors_of_all_levels)[level_num - 1][*ptr_corr_count + abs(J)].x = start.x + J ;
                (*address_corridors_of_all_levels)[level_num - 1][*ptr_corr_count + abs(J)].y = start.y;
            }
            *ptr_corr_count += corr_length;
            for (int roo = 0 ; roo < n_rooms_level ; roo ++){
                print_room(rooms_of_all_levels[level_num - 1] + roo);
            }
            print_corridors((*address_corridors_of_all_levels)[level_num - 1] , *ptr_corr_count);
            sleep(1);
            refresh();
        }
        // with realloc:
        // position* temp = realloc((*address_corridors_of_all_levels)[level_num - 1], (*ptr_corr_count + corr_length) * sizeof(position));
        // if (temp == NULL) {
        //     mvprintw(LINES/2 , COLS/2 , "Memory allocation FAILED!");
        //     break;
        // }
        // (*address_corridors_of_all_levels)[level_num - 1] = temp;
        // abs(K) <= abs(y_break - start.y)
    }
}
 
// function to add the doors and windows to room 
void add_door_and_window(room** address_rooms_this_level , int n_rooms){
    srand(time(NULL));
    for (int i = 0 ; i < n_rooms - 1; i++){
            int x1 = 0;
            int x2 = 0;
            int y1 = 0;
            int y2 = 0;
        // do{
            int wall_1 = 0;
            int wall_2 = 0;
            room r1 = (*address_rooms_this_level)[i];
            room r2 = (*address_rooms_this_level)[i + 1];

            int x_north1 = r1.corner.x;
            int x_south1 = r1.corner.x + r1.length - 1;
            int y_west1 = r1.corner.y;
            int y_east1 = r1.corner.y + r1.width - 1;
            int x_north2 = r2.corner.x;
            int x_south2 = r2.corner.x + r2.length - 1;
            int y_west2 = r2.corner.y;
            int y_east2 = r2.corner.y + r2.width - 1;

            x1 = 0;
            x2 = 0;
            y1 = 0;
            y2 = 0;

            if (r2.corner.y > r1.corner.y + r1.width){
                wall_1 = 2; // east
                x1 = rand() % (r1.length - 2) + x_north1 + 1;
                y1 = y_east1;
                wall_2 = 3; // west
                x2 = rand() % (r2.length - 2) + x_north2 + 1;
                y2 = y_west2;
            }
            else if(r2.corner.x + r2.length < r1.corner.x){
                wall_1 = 0; // north
                x1 = x_north1;
                y1 = rand() % (r1.width - 2) + y_west1 + 1;
                wall_2 = 1; // south
                x2 = x_south2;
                do{
                    y2 = rand() % (r2.width - 2) + y_west2 + 1;
                } while(y2 <= y1);
            }
            else if(r2.corner.x > r1.corner.x + r1.length){
                wall_1 = 1; // south
                x1 = x_south1;
                y1 = rand() % (r1.width - 2) + y_west1 + 1;
                wall_2 = 0; // north
                x2 = x_north2;
                do{
                    y2 = rand() % (r2.width - 2) + y_west2 + 1;
                } while(y2 <= y1);
            }
            else if (r2.corner.y + r2.width < r1.corner.y) { // doesn't happen i guess ...
                wall_1 = 3; // west
                x1 = rand() % (r1.length - 2) + x_north1 + 1;
                y1 = y_west1;
                wall_2 = 2; // east
                x2 = rand() % (r2.length - 2) + x_north2 + 1;
                y2 = y_east2;
            }

            (*address_rooms_this_level)[i].doors_x[0] = x1;
            (*address_rooms_this_level)[i].doors_y[0] = y1;
            (*address_rooms_this_level)[i + 1].doors_x[1] = x2;
            (*address_rooms_this_level)[i + 1].doors_y[1] = y2;
        // } while(y2 <= y1);
    }

}

void print_room(room *Room){ 

    if (Room == NULL) {
    printf("Error: Room is NULL before print_room\n");
    return;
    }
    // printf("Printing room at position (%d, %d)\n", Room->corner.x, Room->corner.y); // Debug print

    start_color();
    attron(COLOR_BLACK);
    position ul_corner;
    ul_corner.x = Room->corner.x;
    ul_corner.y = Room->corner.y;
    if (!Room->hide){ // visible
        // printf("Room is visible\n"); // Debug print

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
        init_color(76, 990 , 570 , 800); // for food
        init_pair(8, 76 , COLOR_BLACK); // for food
        init_color(77, 1000 , 1000 , 0); // for gold
        init_pair(15, 77 , COLOR_BLACK); // for gold
        attron(COLOR_PAIR(Room->type));
        for (int y = ul_corner.y + 1; y < ul_corner.y + Room->width - 1 ; y++){
            for (int x = ul_corner.x + 1 ; x < ul_corner.x + Room->length - 1 ; x++){
                mvprintw(x , y , "%c" , floor);
            }
        }
        attroff(COLOR_PAIR(Room->type));
        for (int i = 0 ; i < 2 ; i++){   
            mvprintw(Room->pillars_x[i],  Room->pillars_y[i] , "O");
        }
        attron(COLOR_PAIR(8));
        for (int i = 0 ; i < Room->n_foods ; i++){   
            if(Room->picked_foods[i] == 0){
                mvprintw(Room->foods_x[i],  Room->foods_y[i] , "f");
            }
        }
        attroff(COLOR_PAIR(8));

        attron(COLOR_PAIR(15));

        for (int i = 0 ; i < Room->n_golds ; i++){   
            if(Room->picked_golds[i] == 0){
                mvprintw(Room->golds_x[i],  Room->golds_y[i] , "g");
            }
        }
        attroff(COLOR_PAIR(15));

        if (Room->room_number == 1){
            mvprintw(Room->doors_x[0],  Room->doors_y[0] , "+");
        }
        else{
            for (int i = 0 ; i < 2 ; i++){
                mvprintw(Room->doors_x[i],  Room->doors_y[i] , "+");
            }  
        }



    } 

    else {
        // printf("Room is hidden\n"); // Debug print
    }
}
 
// function to print corridors 
void print_corridors(position* corridors_of_this_level , int n_of_corr_characters_on_this_level){
    start_color();
    init_pair(100, COLOR_YELLOW, COLOR_BLACK);
    attron(COLOR_PAIR(100));
    for (int i = 0; i <= n_of_corr_characters_on_this_level; i++){
        mvprintw(corridors_of_this_level[i].x, corridors_of_this_level[i].y, "#");
    }
    attroff(COLOR_PAIR(100));
}

// random number of rooms
int number_of_rooms(int difficulty){
    int n_rooms_max = pow(1.4 , difficulty )* 6; 
    int n_rooms_min = 6;
    int n_rooms = rand() % ((n_rooms_max - n_rooms_min)+1) + n_rooms_min;
    return n_rooms;
}

// create new map (level_num-dependent)
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
        // ROOM.ajab = 0;
        ROOM.floor_level = level_num;
        ROOM.hide = 0;
        ROOM.type = room_types[rand() % 10];
        ROOM.length = rand() % (max_length - 6) + 7;
        ROOM.width = rand() % (max_width - 6) + 7;
        if(3 == difficulty){
            ROOM.n_foods = rand() % 3;
        }
        else if(2 == difficulty || 1 == difficulty){
            ROOM.n_foods = rand() % 4;
        }

        ROOM.n_golds = rand() % 3;

        // no food/gold has been picked yet
        for (int F = 0 ; F < ROOM.n_foods ; F++){
            ROOM.picked_foods[F] = 0;
        }
        for (int G = 0 ; G < ROOM.n_golds ; G++){
            ROOM.picked_golds[G] = 0;
        }

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
    
    if (1 == level_num){
        (*address_rooms_of_all_levels)[level_num - 1][1].hide = 0; // the player starts from room index 1 (second room)
        (*address_rooms_of_all_levels)[level_num - 1][0].hide = 0; // the player starts from room index 1 (second room)
    }


    //     // adding doors and windows
    // for (int i = 0 ; i < n_rooms ; i++){
    //     srand(time(NULL));
    //     add_door_and_window((*address_rooms_of_all_levels)[level_num - 1] + i , n_rooms);
    //     // add_pillars((*address_rooms_of_all_levels)[level_num - 1] + i);
    // }
}

// check if new room has overlap with previous ones
int room_valid(room ROOM , room*** address_rooms_of_all_levels , int level_num , int i){
    int x_min = ROOM.corner.x , x_max = ROOM.corner.x + ROOM.length;
    int y_min = ROOM.corner.y , y_max = ROOM.corner.y + ROOM.width;

    // enough space for messages 
    if(x_max >= LINES - 3 || x_min <= 3){
        return 0;
    }

    for (int j = 0 ; j < i ; j++){
        room checking = (*address_rooms_of_all_levels)[level_num - 1][j];
        int check_x_min = checking.corner.x - 3, check_x_max = checking.corner.x + checking.length + 3;
        int check_y_min = checking.corner.y - 3, check_y_max = checking.corner.y + checking.width + 3;

        for (int x = x_min ; x <= x_max ; x++){
            for (int y = y_min ; y <= y_max ; y++){
                if ( (x >= check_x_min && x <= check_x_max) && (y >= check_y_min && y <= check_y_max) ){
                    return 0;
                }
            }
        }
        if(y_min == checking.corner.y + checking.width - 1 || y_min == checking.corner.y + checking.width || y_min == checking.corner.y + checking.width + 1){
            return 0;
        }
    }

    return 1;
}

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
        double min_distance = sqrt(pow( (my_rooms[i - 1].corner.x + my_rooms[i - 1].length/2) - (my_rooms[i].corner.x + my_rooms[i].length/2) , 2) + pow( (my_rooms[i - 1].corner.y + my_rooms[i - 1].width/2) - (my_rooms[i].corner.y + my_rooms[i].width/2), 2));
       
        for (int j = i + 1; j < n_rooms; j++) {
            double d = sqrt( pow((my_rooms[i - 1].corner.x + my_rooms[i - 1].length/2) - (my_rooms[j].corner.x + my_rooms[j].length/2) , 2)  +  pow( (my_rooms[i - 1].corner.y + my_rooms[i - 1].width/2) - (my_rooms[j].corner.y + my_rooms[j].width/2) , 2) );
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