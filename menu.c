// Arvin Rasulzadeh
// 403110422
// code for checking menu functions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <ctype.h>
#include <ncurses.h>
#include <locale.h>
#include "player.h"
#include "entrance_menu.h"
#include "song.h"
#include "score_table.h"
void show_score_table(char* , int );

int main(){
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    cbreak();
    start_color(); 
    bkgd(COLOR_BLACK);
    while (1){
        entrance_menu();
        refresh();
    }
    endwin();
    return 0;
}
