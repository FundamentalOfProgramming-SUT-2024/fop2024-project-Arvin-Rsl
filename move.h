#ifndef MOVE_H
#define MOVE_H
////  library : Move  ////

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
#include "new_map.h"
#include "player.h"

int x_moves[] = {-1 , +1 , +0 , +0 , -1 , -1 , +1 , +1}; // up , down , right , left , up-right , up-left , down-right , down-left
int y_moves[] = {+0 , +0 , +1 , -1 , +1 , -1 , +1 , -1};
int valid_move();
void movement();
// void pick();
void pick(int , int  , int , int , player* , room**  , int );
int in_which_room();
int which_food_in_room();
// returns the index of the room in which player is standing
int in_which_room(room* rooms_this_level , int n_rooms , player hero){
    if ((mvinch(hero.pos.x , hero.pos.y-1) & A_CHARTEXT) == '.' || (mvinch(hero.pos.x , hero.pos.y-1) & A_CHARTEXT) == ',' ||
        (mvinch(hero.pos.x , hero.pos.y-1) & A_CHARTEXT) == '~' || (mvinch(hero.pos.x , hero.pos.y-1) & A_CHARTEXT) == '-' ||
        (mvinch(hero.pos.x , hero.pos.y-1) & A_CHARTEXT) == '_' || (mvinch(hero.pos.x , hero.pos.y-1) & A_CHARTEXT) == '|' ||
        (mvinch(hero.pos.x , hero.pos.y-1) & A_CHARTEXT) == '+' || (mvinch(hero.pos.x , hero.pos.y-1) & A_CHARTEXT) == 'O' || 
        (mvinch(hero.pos.x , hero.pos.y-1) & A_CHARTEXT) == 'f' || (mvinch(hero.pos.x , hero.pos.y-1) & A_CHARTEXT) == 'g' ||
        (mvinch(hero.pos.x , hero.pos.y-1) & A_CHARTEXT) == 'm' || (mvinch(hero.pos.x , hero.pos.y-1) & A_CHARTEXT) == 'd' ||
        (mvinch(hero.pos.x , hero.pos.y-1) & A_CHARTEXT) == 'w' || (mvinch(hero.pos.x , hero.pos.y-1) & A_CHARTEXT) == 'a' ||
        (mvinch(hero.pos.x , hero.pos.y-1) & A_CHARTEXT) == 's'){
        int this_room = 0;
        for (int i = 0 ; i < n_rooms ; i++){
            room r = rooms_this_level[i];
            if( (hero.pos.x >= r.corner.x && hero.pos.x < r.corner.x + r.length) && (hero.pos.y >= r.corner.y && hero.pos.y < r.corner.y + r.width) ){
                this_room = r.room_number;
                mvprintw(LINES - 2 , COLS - 20  , "u r in room index %d" , this_room - 1);
                // sleep(2);
                refresh();
                return this_room - 1;
            }
        }
    }
    else{
        return - 1;
    }
}

// returns the index of food on position x , y
int which_food_in_room(int x , int y , room R){
    for (int i = 0 ; i < R.n_foods ; i++){
        if (x == R.foods_x[i] && y == R.foods_y[i]){
            return i;
        }
    }
    return -1;
}

// returns the index of gold on position x , y
int which_gold_in_room(int x , int y , room R){
    for (int i = 0 ; i < R.n_foods ; i++){
        if (x == R.golds_x[i] && y == R.golds_y[i]){
            return i;
        }
    }
    return -1;
}

// pick up (food , weapon , gold)
void pick(int there, int pick_or_not , int x , int y ,player* hero , room** address_to_rooms_this_level , int n_rooms_this_level){
    mvprintw(LINES - 6, 1, "finding the room index");
    refresh();
    int room_index = in_which_room(*address_to_rooms_this_level , n_rooms_this_level , *hero);
    mvprintw(LINES - 7, 1, "room index is %d" , room_index);
    refresh();
    
    if(pick_or_not){ // if player chooses to pick

        // char there = mvinch(x , y) & A_CHARTEXT ;
        mvprintw(LINES - 3 , 1 , "checking mvinch at %d , %d " , x , y);
        refresh();

        if (there != '.'){
            mvprintw(LINES - 4 , 1 , "You are standing on %c" , there);
            refresh();
            hero->food_count++;
            ((*address_to_rooms_this_level) + room_index )->picked_foods[which_food_in_room(x , y , (*address_to_rooms_this_level)[room_index])] = 1;
            // code to not continue printing that f there (add int array of picked_food for each room)
        }
        else if (there == 'g'){
            mvprintw(LINES - 4 , 1 , "You are standing on Gold");
            refresh();

            hero->gold_count++;  
            ((*address_to_rooms_this_level) + room_index )->picked_golds[which_gold_in_room(x , y , (*address_to_rooms_this_level)[room_index])] = 1;
        }

        // int weapons[5]:  // 0 : Mace (m)
                            // 1 : Dagger (d)
                            // 2 : Magic Wand (w)
                            // 3 : Normal Arrow (a)
                            // 4 : Sword (s)
        else if (there == 'm'){
            hero->weapons[0]++;
        }
        else if (there == 'd'){
            hero->weapons[1]++;
        }
        else if (there == 'w'){
            hero->weapons[2]++;
        }
        else if (there == 'a'){
            hero->weapons[3]++;
        }
        else if (there == 's'){
            hero->weapons[4]++;
        }
        else{
            mvprintw(LINES - 4 , 1 , "You are standing on floor");
        }
        // *pick_or_not = 0; // do not pick again (until new command)
    }
    
    else{
        // nothing?
    }

}

// check if the character on (x,y) is valid for passing
int valid_move(int x , int y ){   
    char there = mvinch(x , y) & A_CHARTEXT ;
    if (there == '.'  || there == ',' || there == '-' || there == '~' || there == '#' || there == '+' ){
        return 1;
    }
    else if(there == 'f' || there == 'g'|| there == 'm'|| there == 'd'|| there == 'w'|| there == 'a'|| there == 's'){
        return 2;
    }
    return 0;
}
// checked

// technically just a switch/case that changes the players position (if valid) .  
void movement(int PiCk , int ch , player* hero , room** address_to_rooms_this_level , int n_rooms_this_level){ // later in while(1) of the print_map() function: 
                                      // char ch = getchar();
                                      // attron
                                      // mvprintw(hero.pos.x , hero.pos.y , "A");
                                      // attroff

    keypad(stdscr, TRUE);
    position current;
    current.x = hero->pos.x;
    current.y = hero->pos.y;
    int x_new ;
    int y_new ;
    char ccc;
    int room_num = -1;

    switch (ch) {
        case '8': // Up
        case KEY_UP:
        case 'J':
        case 'j':
            x_new = current.x + x_moves[0];
            y_new = current.y + y_moves[0];
            ccc = mvinch(x_new , y_new) & A_CHARTEXT;
            //// PAY Attention: here by room_num I mean room_index
            room_num = in_which_room(*address_to_rooms_this_level , n_rooms_this_level , *hero);
            if (ccc == 'f' && room_num >= 0){
                hero->food_count++;
                ((*address_to_rooms_this_level) + room_num)->picked_foods[which_food_in_room(x_new, y_new , (*address_to_rooms_this_level)[room_num])] = 1;
            }
            else if (ccc == 'g' && room_num >= 0){
                hero->gold_count++;
                ((*address_to_rooms_this_level) + room_num )->picked_golds[which_gold_in_room(x_new, y_new , (*address_to_rooms_this_level)[room_num])] = 1;
            }
            if (valid_move(x_new , y_new) == 1){
                hero->pos.x = x_new;
                hero->pos.y = y_new;
            } 
            else if(valid_move(x_new , y_new) == 2){
                // pick(ccc , PiCk ,x_new , y_new, hero ,  address_to_rooms_this_level, n_rooms_this_level);
            }
            break;

        case '2': // Down
        case KEY_DOWN:
        case 'K':
        case 'k':       
            x_new = current.x + x_moves[1];
            y_new = current.y + y_moves[1];
            ccc = mvinch(x_new , y_new) & A_CHARTEXT;
            room_num = in_which_room(*address_to_rooms_this_level , n_rooms_this_level , *hero);
            if (ccc == 'f' && room_num >= 0){
                hero->food_count++;
                ((*address_to_rooms_this_level) + room_num)->picked_foods[which_food_in_room(x_new, y_new , (*address_to_rooms_this_level)[room_num])] = 1;
            }
            else if (ccc == 'g' && room_num >= 0){
                hero->gold_count++;
                ((*address_to_rooms_this_level) + room_num )->picked_golds[which_gold_in_room(x_new, y_new , (*address_to_rooms_this_level)[room_num])] = 1;
            }
            if (valid_move(x_new , y_new) == 1){
                hero->pos.x = x_new;
                hero->pos.y = y_new;
            } 
            else if(valid_move(x_new , y_new) == 2){
                // pick(ccc , PiCk ,x_new , y_new, hero ,  address_to_rooms_this_level, n_rooms_this_level);
            }
            break;

        case '6': // Right
        case KEY_RIGHT:
        case 'L':
        case 'l':
            x_new = current.x + x_moves[2];
            y_new = current.y + y_moves[2];
            ccc = mvinch(x_new , y_new) & A_CHARTEXT;
            room_num = in_which_room(*address_to_rooms_this_level , n_rooms_this_level , *hero);
            if (ccc == 'f' && room_num >= 0){
                hero->food_count++;
                ((*address_to_rooms_this_level) + room_num)->picked_foods[which_food_in_room(x_new, y_new , (*address_to_rooms_this_level)[room_num])] = 1;
            }
            else if (ccc == 'g' && room_num >= 0){
                hero->gold_count++;
                ((*address_to_rooms_this_level) + room_num)->picked_golds[which_gold_in_room(x_new, y_new , (*address_to_rooms_this_level)[room_num])] = 1;
            }

            if (valid_move(x_new , y_new) == 1){
                hero->pos.x = x_new;
                hero->pos.y = y_new;
            } 
            else if(valid_move(x_new , y_new) == 2){
                // pick(ccc , PiCk ,x_new , y_new, hero ,  address_to_rooms_this_level, n_rooms_this_level);
            }
            break;

        case '4': // Left
        case KEY_LEFT:
        case 'H':
        case 'h':
            x_new = current.x + x_moves[3];
            y_new = current.y + y_moves[3];
            ccc = mvinch(x_new , y_new) & A_CHARTEXT;
            room_num = in_which_room(*address_to_rooms_this_level , n_rooms_this_level , *hero);

            if (ccc == 'f' && room_num >= 0){
                hero->food_count++;
                ((*address_to_rooms_this_level) + room_num)->picked_foods[which_food_in_room(x_new, y_new , (*address_to_rooms_this_level)[room_num])] = 1;
            }
            else if (ccc == 'g' && room_num >= 0){
                hero->gold_count++;
                ((*address_to_rooms_this_level) + room_num)->picked_golds[which_gold_in_room(x_new, y_new , (*address_to_rooms_this_level)[room_num])] = 1;
            }
            if (valid_move(x_new , y_new) == 1){
                hero->pos.x = x_new;
                hero->pos.y = y_new;
            } 
            else if(valid_move(x_new , y_new) == 2){
                // pick(ccc , PiCk ,x_new , y_new, hero ,  address_to_rooms_this_level, n_rooms_this_level);
            }
            break;

        case '9': // Upper right
        case 'U':
        case 'u':
            x_new = current.x + x_moves[4];
            y_new = current.y + y_moves[4];
            ccc = mvinch(x_new , y_new) & A_CHARTEXT;
            room_num = in_which_room(*address_to_rooms_this_level , n_rooms_this_level , *hero);

            if (ccc == 'f' && room_num >= 0){
                hero->food_count++;
                ((*address_to_rooms_this_level) + room_num )->picked_foods[which_food_in_room(x_new, y_new , (*address_to_rooms_this_level)[room_num])] = 1;
            }
            else if (ccc == 'g' && room_num >= 0){
                hero->gold_count++;
                ((*address_to_rooms_this_level) + room_num )->picked_golds[which_gold_in_room(x_new, y_new , (*address_to_rooms_this_level)[room_num])] = 1;
            }
            if (valid_move(x_new , y_new) == 1){
                hero->pos.x = x_new;
                hero->pos.y = y_new;
            } 
            else if(valid_move(x_new , y_new) == 2){
                // pick(ccc , PiCk ,x_new , y_new, hero ,  address_to_rooms_this_level, n_rooms_this_level);
            }
            break;

        case '7': // Upper left
        case 'Y':
        case 'y':
            x_new = current.x + x_moves[5];
            y_new = current.y + y_moves[5];
            ccc = mvinch(x_new , y_new) & A_CHARTEXT;
            room_num = in_which_room(*address_to_rooms_this_level , n_rooms_this_level , *hero);

            if (ccc == 'f' && room_num >= 0){
                hero->food_count++;
                ((*address_to_rooms_this_level) + room_num)->picked_foods[which_food_in_room(x_new, y_new , (*address_to_rooms_this_level)[room_num])] = 1;
            }
            else if (ccc == 'g' && room_num >= 0){
                hero->gold_count++;
                ((*address_to_rooms_this_level) +room_num )->picked_golds[which_gold_in_room(x_new, y_new , (*address_to_rooms_this_level)[room_num])] = 1;
            }
            if (valid_move(x_new , y_new) == 1){
                hero->pos.x = x_new;
                hero->pos.y = y_new;
            } 
            else if(valid_move(x_new , y_new) == 2){
                // pick(ccc , PiCk ,x_new , y_new, hero ,  address_to_rooms_this_level, n_rooms_this_level);
            }
            break;

        case '1': // Down left
        case 'B':
        case 'b':
            x_new = current.x + x_moves[7];
            y_new = current.y + y_moves[7];
            ccc = mvinch(x_new , y_new) & A_CHARTEXT;
            room_num = in_which_room(*address_to_rooms_this_level , n_rooms_this_level , *hero);

            if (ccc == 'f' && room_num >= 0){
                hero->food_count++;
                ((*address_to_rooms_this_level) + room_num)->picked_foods[which_food_in_room(x_new, y_new , (*address_to_rooms_this_level)[room_num])] = 1;
            }
            else if (ccc == 'g' && room_num >= 0){
                hero->gold_count++;
                ((*address_to_rooms_this_level) + room_num )->picked_golds[which_gold_in_room(x_new, y_new , (*address_to_rooms_this_level)[room_num])] = 1;
            }
            if (valid_move(x_new , y_new) == 1){
                hero->pos.x = x_new;
                hero->pos.y = y_new;
            } 
            else if(valid_move(x_new , y_new) == 2){
                // pick(ccc, PiCk ,x_new , y_new, hero ,  address_to_rooms_this_level, n_rooms_this_level);
            }
            break;

        case '3': // Down right
        case 'N':
        case 'n':
            x_new = current.x + x_moves[6];
            y_new = current.y + y_moves[6];
            ccc = mvinch(x_new , y_new) & A_CHARTEXT;
            room_num = in_which_room(*address_to_rooms_this_level , n_rooms_this_level , *hero);

            if (ccc == 'f' && room_num >= 0){
                hero->food_count++;
                ((*address_to_rooms_this_level) + room_num)->picked_foods[which_food_in_room(x_new, y_new , (*address_to_rooms_this_level)[room_num])] = 1;
            }
            else if (ccc == 'g' && room_num >= 0){
                hero->gold_count++;
                ((*address_to_rooms_this_level) + room_num)->picked_golds[which_gold_in_room(x_new, y_new , (*address_to_rooms_this_level)[room_num])] = 1;
            }
            if (valid_move(x_new , y_new) == 1){
                hero->pos.x = x_new;
                hero->pos.y = y_new;
            } 
            else if(valid_move(x_new , y_new) == 2){
                // pick(ccc, PiCk ,x_new , y_new, hero ,  address_to_rooms_this_level, n_rooms_this_level);
            }
            break;
    } 
}

/*
example of movement():
        attron(COLOR_PAIR(me.color));
        mvprintw(me.pos.x , me.pos.y , "%c" , 'A');
        int ch = getch();
        if (ch == 'q') {
            break;  
        }
        movement(ch , &me);
        mvprintw(me.pos.x , me.pos.y , "%c" , 'A');
        attroff(COLOR_PAIR(me.color));
        refresh();
*/
#endif