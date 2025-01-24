#ifndef SCORE_TABLE_H
#define SCORE_TABLE_H
////  library : Score Table   ////

// Arvin Rasulzadeh
// 403110422

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <ctype.h>
#include <ncurses.h>
#define Score_Table "/home/arvin_rsl/Desktop/FOP_Project/Users_Folder/Score_Table.txt"
#include "player.h"
#include "entrance_menu.h"
typedef struct {
    char username[50];
    int rank;
    int total_score;
    int latest_gold;
    int experience;
} ScoreEntry;
void show_score_table(char* , int );
void update_score_table(player );
int compare_rank(const void *, const void *);
void update_score_table(player);
void draw_borders(int);
void pregame_menu();

int compare_rank(const void *a, const void *b) {
    return ((ScoreEntry *)a)->rank - ((ScoreEntry *)b)->rank;
}

int read_score_table(ScoreEntry *entries){
    FILE *file = fopen(Score_Table, "r");
    if (file == NULL) {
        perror("Error opening score table file");
        return 0;
    }

    int player_count;
    fscanf(file, "number of players: %d\n", &player_count);

    for (int i = 0; i < player_count; i++) {
        fscanf(file, "username: %s\nrank: %d\ntotal score: %d\nlatest gold count: %d\nexperience: %d\n\n", 
               entries[i].username, 
               &entries[i].rank, 
               &entries[i].total_score, 
               &entries[i].latest_gold, 
               &entries[i].experience);
    }

    fclose(file);
    return player_count;
}

void show_score_table(char* my_username, int page) {
    ScoreEntry entries[100]; 
    int entry_count = read_score_table(entries);
    if (entry_count == 0){
        return;
    }

    // sorting entries by rank
    qsort(entries, entry_count, sizeof(ScoreEntry), compare_rank);

    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
    bkgd(COLOR_PAIR(1));
    keypad(stdscr, TRUE); // enabling keyboard input for the window
    curs_set(0); 

    
    int rank_width = 4;
    int username_width = 20; 
    int score_width = 10;
    int gold_width = 14;
    int games_width = 9;
    int experience_width = 11;
    int table_width = rank_width + username_width + score_width + gold_width + games_width + experience_width + 25; 
    int items_per_page = 10;
    int total_pages = (entry_count + items_per_page - 1) / items_per_page;
    int current_page = page;

    while (1) {
        clear();
        draw_borders(13);

        int start_y = (COLS - table_width) / 2;
        int start_x = (LINES - (items_per_page + 8)) / 2;

        mvprintw(start_x, start_y,     "+------+----------------------+-------------+----------------+-----------+---------------+");
        mvprintw(start_x + 1, start_y, "| Rank | Username             | Total Score | Latest Gold    | Games     | Experience    |");
        mvprintw(start_x + 2, start_y, "+------+----------------------+-------------+----------------+-----------+---------------+");

        int start_index = (current_page - 1) * items_per_page;
        int end_index = start_index + items_per_page > entry_count ? entry_count : start_index + items_per_page;

        for (int i = start_index; i < end_index; i++) {
            int color_pair = 1;
            const char *label = "";

            // top 3 players ONLY on the first page
            if (current_page == 1) {
                if (i - start_index == 0){
                    color_pair = 3;
                    label = "\U0001f947 GOAT"; // Gold medal
                } 
                else if (i - start_index == 1){
                    color_pair = 4;
                    label = "\U0001f948 Runner-Up"; // Silver medal
                } 
                else if (i - start_index == 2){
                    color_pair = 2;
                    label = "\U0001f949 Achiever"; // Bronze medal
                }
            }

            attron(COLOR_PAIR(color_pair));
            if (strcmp(entries[i].username, my_username) == 0) { // the user 
                // Bold my_username
                attron(A_BOLD);
                mvprintw(start_x + (i - start_index) + 3, start_y, "| %*d | %-*s |  %*d | %*d | %*d | %*d   | %s",
                         rank_width, entries[i].rank,
                         username_width, entries[i].username,
                         score_width, entries[i].total_score,
                         gold_width, entries[i].latest_gold,
                         games_width, entries[i].rank, 
                         experience_width, entries[i].experience,
                         label);
                attroff(A_BOLD);
            } 
            else { // others
                mvprintw(start_x + (i - start_index) + 3, start_y, "| %*d | %-*s |  %*d | %*d | %*d | %*d   | %s",
                         rank_width, entries[i].rank,
                         username_width, entries[i].username,
                         score_width, entries[i].total_score,
                         gold_width, entries[i].latest_gold,
                         games_width, entries[i].rank, // It should be `games` field
                         experience_width, entries[i].experience,
                         label);
            }
            attroff(COLOR_PAIR(color_pair));
        }

        mvprintw(start_x + items_per_page + 3, start_y, "+------+----------------------+-------------+----------------+-----------+---------------+");
        attron(COLOR_PAIR(13) | A_BOLD);
        mvprintw(start_x + items_per_page + 5, start_y, "Page %d/%d | Press N for next page, P for previous page, Q to go back to Pregame Menu", current_page, total_pages);
        attroff(COLOR_PAIR(13) | A_BOLD);

        refresh();

        // user input
        int ch = getch();
        if (ch == 'q' || ch == 'Q') {
            pregame_menu(my_username);
            break;
        } 
        else if (ch == 'n' || ch == 'N') {
            if (current_page < total_pages) {
                current_page++;
            }
        } 
        else if (ch == 'p' || ch == 'P') {
            if (current_page > 1) {
                current_page--;
            }
        }
    }
    endwin();
}

// function to update score table when player finishes a game
void update_score_table(player hero){}

#endif
