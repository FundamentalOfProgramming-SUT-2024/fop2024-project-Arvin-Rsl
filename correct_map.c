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

char global_message[100] = "Welcome to Arvin's Rogue!";

int main(){
    initscr();
    nodelay(stdscr, TRUE);
    noecho();
    cbreak();
    curs_set(FALSE);
    start_color(); 
    srand(time(NULL));  
    setlocale(LC_ALL, "");
    
    int difficulty = 1;
    // int n_rooms1 = number_of_rooms(difficulty);
    // int n_rooms2 = number_of_rooms(difficulty);
    // int n_rooms3 = number_of_rooms(difficulty);
    // int n_rooms4 = number_of_rooms(difficulty);
    int n_rooms[4];
    for (int q = 0 ; q < 4 ; q++){
        n_rooms[q] = number_of_rooms(difficulty);
    }
    int level_num = 1; // initializing 

    room ** rooms_of_all_levels = (room**) malloc (4 * sizeof(room*));
    for (int i = 0 ; i < 4 ; i++){
        rooms_of_all_levels[i] = (room*) malloc(n_rooms[i] * sizeof(room));
    }

    position ** corridors_of_all_levels = (position**)malloc(4 * sizeof(position*));
    for (int i = 0 ; i < 4 ; i++){
        corridors_of_all_levels[i] = (position*)malloc(MAX_CORR * sizeof(position));

        if (corridors_of_all_levels[i] == NULL) {
            endwin();
            printf("Memory allocation FAILED for corridors_of_all_levels[%d]!\n", i);
            return 1;
        }
    }
    int corr_count[4] = {0};

    printf("trying to make rooms 1 ... \n");
    new_map(difficulty, n_rooms[0], &corridors_of_all_levels, 1, &rooms_of_all_levels);
    printf("done making rooms 1 ! :)\n");

    printf("trying to make rooms 2 ... \n");
    new_map(difficulty, n_rooms[1], &corridors_of_all_levels, 2, &rooms_of_all_levels);
    printf("done making rooms 2 ! :)\n");

    printf("trying to make rooms 3 ... \n");
    new_map(difficulty, n_rooms[2] , &corridors_of_all_levels, 3, &rooms_of_all_levels);
    printf("done making rooms 3 ! :)\n");
    
    printf("trying to make rooms 4 ... \n");
    new_map(difficulty, n_rooms[3], &corridors_of_all_levels, 4, &rooms_of_all_levels);
    printf("done making rooms 4 ! :)\n");


    printf("trying to make doors 1 ... \n");
    add_door_and_window(rooms_of_all_levels + 0 , n_rooms[0]);
    printf("done making doors 1! :)\n");

    printf("trying to make doors 2 ... \n");
    add_door_and_window(rooms_of_all_levels + 1 , n_rooms[1]);
    printf("done making doors 2 ! :)\n");

    printf("trying to make doors 3 ... \n");
    add_door_and_window(rooms_of_all_levels + 2 , n_rooms[2]);
    printf("done making doors 3 ! :)\n");

    printf("trying to make doors 4 ... \n");
    add_door_and_window(rooms_of_all_levels + 3 , n_rooms[3]);
    printf("done making doors 4 ! :)\n");


    printf("now go for pillars 1 ... \n");
    add_pillars(rooms_of_all_levels + 0 , n_rooms[0]);
    printf("done with pillars 1 ... \n");

    printf("now go for pillars 2 ... \n");
    add_pillars(rooms_of_all_levels + 1 , n_rooms[1]);
    printf("done with pillars 2 ... \n");

    printf("now go for pillars 3 ... \n");
    add_pillars(rooms_of_all_levels + 2 , n_rooms[2]);
    printf("done with pillars 3 ... \n");

    printf("now go for pillars 4 ... \n");
    add_pillars(rooms_of_all_levels + 3 , n_rooms[3]);
    printf("done with pillars 4 ... \n");
    
    printf("adding foods/golds/traps ... \n");

    add_food(rooms_of_all_levels + 0 , n_rooms[0]);
    add_gold(rooms_of_all_levels + 0 , n_rooms[0]);
    add_trap(rooms_of_all_levels + 0 , n_rooms[0]);

    add_food(rooms_of_all_levels + 1 , n_rooms[1]);
    add_gold(rooms_of_all_levels + 1 , n_rooms[1]);
    add_trap(rooms_of_all_levels + 1 , n_rooms[1]);

    add_food(rooms_of_all_levels + 2 , n_rooms[2]);
    add_gold(rooms_of_all_levels + 2 , n_rooms[2]);
    add_trap(rooms_of_all_levels + 2 , n_rooms[2]);

    add_food(rooms_of_all_levels + 3 , n_rooms[3]);
    add_gold(rooms_of_all_levels + 3 , n_rooms[3]);
    add_trap(rooms_of_all_levels + 3 , n_rooms[3]);

    printf("done adding foods/golds/traps! \n");
    printf("building corridors of levels \n");

    build_corr2(n_rooms[0] , &corridors_of_all_levels , rooms_of_all_levels , 1 , corr_count + 0);
    build_corr2(n_rooms[1] , &corridors_of_all_levels , rooms_of_all_levels , 2 , corr_count + 1);
    build_corr2(n_rooms[2] , &corridors_of_all_levels , rooms_of_all_levels , 3 , corr_count + 2);
    build_corr2(n_rooms[3] , &corridors_of_all_levels , rooms_of_all_levels , 4 , corr_count + 3);
    
    printf("done building corridors of levels! \n");

    player me;
    me.pos.x =  rooms_of_all_levels[level_num - 1][1].corner.x  + rooms_of_all_levels[level_num - 1][1].length/2;
    me.pos.y =  rooms_of_all_levels[level_num - 1][1].corner.y  + rooms_of_all_levels[level_num - 1][1].width/2;
    me.food_count = 0;
    me.gold_count = 0;
    me.health = 13;
    me.color = 24;   
    me.current_weapon = 3; // 0 : Mace (m)
                        // 1 : Dagger (d)
                        // 2 : Magic Wand (w)
                        // 3 : Normal Arrow (a)
                        // 4 : Sword (s)
    me.current_spell = 0;// 0 : Health ♥ 
                         // 1 : Speed → or $
                         // 2 : Damage $
    for (int w = 0 ; w < 5 ; w++){
        me.weapons[w] = 0;
    }
    for (int s = 0 ; s < 3 ; s++){
        me.spells[s] = 0;
    }


    // Set getch() to be non-blocking
    nodelay(stdscr, TRUE);

    // Initialize audio
    init_audio();

    int current_song = 0; // Start with song1

    // Example: user chooses a soundtrack
    choose_soundtrack(current_song);
    int PiCk = 1;
    while(1){
        for (int i = 0 ; i < n_rooms[level_num - 1] ; i++){
            print_room(rooms_of_all_levels[level_num - 1] + i);
        }

        // no corr char left unprinted:
        for (int ro = 0 ; ro < n_rooms[level_num - 1] ; ro++){
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
        

        if(level_num == 4 && rooms_of_all_levels[level_num - 1][in_which_room(rooms_of_all_levels[level_num - 1] , n_rooms[level_num - 1] , me)].type == 3){
                // Treasure Room!!
                win();
        }
        

        print_corridors(corridors_of_all_levels[level_num - 1] , *(corr_count + level_num - 1));
        // int ch = getch();
        // if (ch == 'q'){
        //     break;
        // }
        print_top_message(global_message);
        
        print_bottom_message(&me , level_num);

        init_pair(24 , COLOR_CYAN , COLOR_BLACK);
        attron(COLOR_PAIR(me.color));
        mvprintw(me.pos.x , me.pos.y , "%c" , 'A');
        int ch = getch();
        if (ch == 'q' || ch == 'Q') {
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
            nodelay(stdscr, TRUE);
        }
        else if (ch == 'f' || ch == 'F') {
            nodelay(stdscr, FALSE);
            food_list(me);  // Show food screen if 'f' key is pressed
            nodelay(stdscr, TRUE);
        }
        else if (ch == 'i' || ch == 'I') {
            nodelay(stdscr, FALSE);
            weapon_list(&me);  // Show weapon screen if 'i' key is pressed
            nodelay(stdscr, TRUE);
        }
        else if (ch == 'x' || ch == 'X') {
            nodelay(stdscr, FALSE);
            spell_list(&me);  // Show spell screen if 'x' key is pressed
            nodelay(stdscr, TRUE);
        }
        else if (ch == 'c' || ch == 'C') {
            if(me.food_count > 0){
                me.food_count--;
                if(me.health <= 14){
                    me.health += 2; 
                }
                else{
                    me.health = 16;  // maximum of health 
                }
            }
            else{
                snprintf(global_message, sizeof(char) * 100, "You are out of food!                              ");
            }

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


        // movement(PiCk , ch , &me , rooms_of_all_levels + level_num - 1 , n_rooms , global_message);
        movement2(PiCk , ch , &me , rooms_of_all_levels, n_rooms[level_num - 1] , global_message , &level_num);
        
        attroff(COLOR_PAIR(me.color));
        // print_corridors(corridors_of_all_levels[level_num - 1] , *(corr_count + level_num - 1));
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

        if (mvinch(0,0) & A_CHARTEXT != ' '){
            mvprintw(0,0, "%c" , ' ');
        }

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
