#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <ctype.h>
#include <ncurses.h>
#include <math.h>
#include <unistd.h> // for sleep() function 
// #define MAX_CORR (int)(184 * 45)
#define MAX_ROOM 16
#include "new_map.h"
#include "move.h"
#include "song.h"
#include "messages.h"
#include <locale.h>

int main(){
    initscr();
    nodelay(stdscr, TRUE);
    noecho();
    cbreak();
    curs_set(FALSE);
    start_color(); 
    srand(time(NULL));  
    setlocale(LC_ALL, "");
    position ** corridors_of_all_levels = (position**)malloc(4 * sizeof(position*));
    for (int i = 0 ; i < 4 ; i++){
        corridors_of_all_levels[i] = (position*)malloc(MAX_CORR * sizeof(position));

        if (corridors_of_all_levels[i] == NULL) {
            endwin();
            printf("Memory allocation FAILED for corridors_of_all_levels[%d]!\n", i);
            return 1;
        }
    }
    room ** rooms_of_all_levels = (room**) malloc (4 * sizeof(room*));
    for (int i = 0 ; i < 4 ; i++){
        rooms_of_all_levels[i] = (room*)malloc(MAX_ROOM * sizeof(room));
        if (rooms_of_all_levels[i] == NULL) {
            endwin();
            printf("Memory allocation FAILED for rooms_of_all_levels[%d]!\n", i);
            return 1;
        }
    }
    int difficulty = 1;
    int n_rooms = number_of_rooms(difficulty);
    int level_num = 1;
    int corr_count_this_level = 0;

    // printf("Before new_map\n");
    new_map(difficulty, n_rooms, &corridors_of_all_levels, level_num, &rooms_of_all_levels);
    // printf("After new_map\n");

    printf("trying to make doors ... \n");
    add_door_and_window(rooms_of_all_levels + level_num - 1 , n_rooms);
    printf("done making doors! :)\n");
    printf("now go for pillars ... \n");

    add_pillars(rooms_of_all_levels + level_num - 1 , n_rooms);

    printf("done with pillars... \n");
    add_food(rooms_of_all_levels + level_num - 1 , n_rooms);
    add_gold(rooms_of_all_levels + level_num - 1 , n_rooms);

    build_corr(n_rooms , &corridors_of_all_levels , rooms_of_all_levels , level_num , &corr_count_this_level);
    

    player me;
    me.pos.x =  rooms_of_all_levels[level_num - 1][1].corner.x  + rooms_of_all_levels[level_num - 1][1].length/2;
    me.pos.y =  rooms_of_all_levels[level_num - 1][1].corner.y  + rooms_of_all_levels[level_num - 1][1].width/2;
    me.food_count = 0;
    me.gold_count = 0;
    me.health = 13;
    me.color = 24;    
    char message[] = "Hi! Welcome to Arvin's Rogue!";


    // Set getch() to be non-blocking
    nodelay(stdscr, TRUE);

    // Initialize audio
    init_audio();

    int current_song = 0; // Start with song1

    // Example: user chooses a soundtrack
    choose_soundtrack(current_song);
    int PiCk = 1;
    while(1){
        // attron(COLOR_PAIR(1));
        for (int i = 0 ; i < n_rooms ; i++){
            init_pair(1 , COLOR_CYAN , COLOR_BLACK);
            print_room(rooms_of_all_levels[level_num - 1] + i);
        }
        print_corridors(corridors_of_all_levels[level_num - 1] , corr_count_this_level);
        // int ch = getch();
        // if (ch == 'q'){
        //     break;
        // }
        print_top_message(message);
        print_bottom_message(&me , level_num);

        init_pair(24 , COLOR_CYAN , COLOR_BLACK);
        attron(COLOR_PAIR(me.color));
        mvprintw(me.pos.x , me.pos.y , "%c" , 'A');
        int ch = getch();
        if (ch == 'q') {
            stop_soundtrack();
            break;  
        }
        else if (ch == 's') {
            // Stop current soundtrack
            stop_soundtrack();

            // Switch to the next song
            current_song += 1;
            init_audio();
            choose_soundtrack(current_song);
        }
        else if (ch == '/') {
            nodelay(stdscr, FALSE);
            help();  // Show help screen if '/' key is pressed

            for (int ro = 0 ; ro < n_rooms ; ro++){
                room ey_baba = rooms_of_all_levels[level_num - 1][ro];
                for(int door = 0 ; door < 2; door++){
                    int X = ey_baba.doors_x[door];
                    int Y = ey_baba.doors_y[door];
                    char there;
                    int x_c = X;
                    int y_c = Y;
                    if(Y == ey_baba.corner.y){
                        there = mvinch(X , Y - 1) & A_CHARTEXT;
                        y_c = Y - 1;
                    }
                    else if (X == ey_baba.corner.x + ey_baba.length - 1){
                        there = mvinch(X+1 , Y) & A_CHARTEXT;
                        x_c = X + 1;
                    }
                    else if (X == ey_baba.corner.x){
                        there = mvinch(X-1 , Y) & A_CHARTEXT;
                        x_c = X - 1;
                    }
                    // there = mvinch(X , Y - 1) & A_CHARTEXT;
                        if( !(there == '_' || there == '|' || there == '.' || there == '~' || there == '-' || there == ',' || there == '#'|| there == 'O' || there == 'f') ){
                            init_pair(36, COLOR_YELLOW, COLOR_BLACK);
                            attron(COLOR_PAIR(36));
                            mvprintw(x_c , y_c , "#");
                            // sleep(1);
                            attroff(COLOR_PAIR(36));
                        }
                }
            }
            
            nodelay(stdscr, TRUE);
        }

        // char standing_on =  mvinch(me.pos.x , me.pos.y) & A_CHARTEXT;
        if (ch == 'p' || ch == 'P') {
        //     clear();
        //     if(PiCk == 0){
        //         // clear();
        //         // mvprintw(LINES - 2 , 3 , "You can pick now!");
        //         PiCk = 1;
        //         attron(COLOR_PAIR(0));
        //         // char message2[] = "You can pick now!";
        //         // print_top_message(message2);
        //         print_corridors(corridors_of_all_levels[level_num - 1] , corr_count_this_level );
        //         attroff(COLOR_PAIR(0));
        //         refresh();
        //     }
        //     else{
        //         // clear();
        //         // mvprintw(LINES - 2 , 3 , "You can not pick now!");
        //         char message2[] = "You can not pick now!";
        //         PiCk = 0;
        //         attron(COLOR_PAIR(1));
        //         // print_top_message(message2);
        //         attroff(COLOR_PAIR(1));
        //         print_corridors(corridors_of_all_levels[level_num - 1] , corr_count_this_level );
        //         refresh();

        //     }
        }


        movement(PiCk , ch , &me , rooms_of_all_levels + level_num - 1 , n_rooms);
        attroff(COLOR_PAIR(me.color));
        print_corridors(corridors_of_all_levels[level_num - 1] , corr_count_this_level );
        attron(COLOR_PAIR(me.color));
        mvprintw(me.pos.x , me.pos.y , "%c" , 'A');
        attroff(COLOR_PAIR(me.color));


        // for (int ro = 0 ; ro < n_rooms ; ro++){
        //     room ey_baba = rooms_of_all_levels[level_num - 1][ro];
        //     for(int door = 0 ; door < 2; door++){
        //         int X = ey_baba.doors_x[door];
        //         int Y = ey_baba.doors_y[door] - 1;
        //         char there = mvinch(X , Y - 1) & A_CHARTEXT;
        //             if( !(there == '_' || there == '|' || there == '.' || there == '~' || there == '-' || there == ',' || there == '#'|| there == 'O' || there == 'f') ){
        //                 init_pair(36, COLOR_YELLOW, COLOR_BLACK);
        //                 attron(COLOR_PAIR(36));
        //                 mvprintw(X , Y , "#");
        //                 attroff(COLOR_PAIR(36));
        //             }
        //     }
        // }


        // print # instead of A if A is not in player's position
        for(int X = 2 ; X < LINES - 1; X++){
            for (int Y = 0 ; Y < COLS ; Y++){
                char there = mvinch(X , Y) & A_CHARTEXT;
                if(there == 'A' && !(X == me.pos.x && Y == me.pos.y)){
                    init_pair(36, COLOR_YELLOW, COLOR_BLACK);
                    attron(COLOR_PAIR(36));
                    mvprintw(X , Y , "%c" , '#');
                    attroff(COLOR_PAIR(36));
                }
            }
        }

        refresh();
        // refresh();
    }
    endwin();
    // Free memory for corridors
    for (int i = 0; i < 4; i++) {
        free(corridors_of_all_levels[i]);
    }
    free(corridors_of_all_levels);

    // Free memory for rooms
    for (int i = 0; i < 4; i++) {
        free(rooms_of_all_levels[i]);
    }
    free(rooms_of_all_levels);
    return 0;
}
