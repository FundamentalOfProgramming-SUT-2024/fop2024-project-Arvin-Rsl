// Arvin Rasulzadeh  --  4 0 3 1 1 0 4 2 2  -- FOP Project Phase 2

#include "TOTAL.h"

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