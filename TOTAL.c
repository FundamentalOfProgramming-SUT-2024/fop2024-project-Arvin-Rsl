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