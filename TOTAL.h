// Arvin Rasulzadeh  --  4 0 3 1 1 0 4 2 2  -- FOP Project Phase 2

#ifndef TOTAL_H
#define TOTAL_H
#include <locale.h>
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <ctype.h>
#include <ncurses.h>
#include <math.h>
#include <unistd.h> // for sleep() function (randomizing existance of windows between rooms)
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#define MAX_CORR (184 * 45) 
#define Score_Table "/home/arvin_rsl/Desktop/FOP_Project/Users_Folder/Score_Table.txt"
#define Usernames_File "/home/arvin_rsl/Desktop/FOP_Project/Users_Folder/Rogue_Usernames.txt"
#define MAX_SIZE 1000

typedef struct {
    int x; // row
    int y; // col
} position;

typedef struct{
    // int exists_in_room;
    // position pos;
    int hit_strength;
    /// hits strength (damage to player)
    // 1 : Deamon       (D)
    // 2 : Fire-Breath  (F)
    // 3 : Giant        (G)
    // 1 : Snake        (S)
    // 5 : Undeed       (U)

    int remained_health; // if 0, the enemy vanishes (exists_in_room = 0)
    /// initial health: 
    // 5  : Deamon       (D)
    // 10 : Fire-Breath  (F)
    // 15 : Giant        (G)
    // 20 : Snake        (S)
    // 30 : Undeed       (U)
} enemy;

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
    int number_of_doors; // fixed 2 or 1
    int number_of_windows; // not included in code
    int number_of_pillars; // fixed 3
    position corner; // corner = upper left corner of the room
    int type; // 0 => Regular Room
              // 1 => Battle Room (trap)
              // 2 => Enchant Room
              // 3 => Treasure Room ( Third is the charm :D )
              // 4 => Nightmare Room
/*  Type of Room:    Pillar Char:       Floor Char      Floor & Pillar Color      int type  
    Regular Room          O                 .                   White                 0
    Battle Room        No Pillar            .                   Red                   1      (cancelled)
    Enchant Room          O                 ,                   Magenta               2
    Treasure Room      No Pillar            -                   Yellow                3
    Nightmare Room        O                 ~                   Blue                  4

*/

/// Door(s)
    int doors_x[2];
    int doors_y[2];

/// Pillars  
    // int n_pillars; /// always 3 pillars
    int pillars_x[3];
    int pillars_y[3];
    
/// Foods
    int n_foods;
    int picked_foods[3]; // 1 if food is picked (don't print it anymore); 0 otherwise
    int foods_x[3];
    int foods_y[3];
    int food_types[3]; // 0 = normal // 1 = ideal // 2 = magical // 3 = rotten

/// Golds
    int n_golds;
    int picked_golds[3]; // 1 if food is picked (don't print it anymore); 0 otherwise
    int golds_x[3];
    int golds_y[3];

/// Trap
    int trap_visibility;
    int trap_x;
    int trap_y;

/// Staircase
// staircase is always in room index 3 (4th room). 
    int stair_x; 
    int stair_y;
/// Black Gold
// We either have 1 black gold in room index 0 (room number 1) on each floor level, or we don't have any on that level
    int black_gold; // 0 if no black gold, 1 if there is one
    int black_gold_x;
    int black_gold_y;
/// Weapons
// each element in this array shows the number of the corresponding weapon in room (which is either 0 or 1)
    int weapons[5]; // 0 : Mace (m)
                    // 1 : Dagger (d)
                    // 2 : Magic Wand (w)
                    // 3 : Normal Arrow (a)
                    // 4 : Sword (s)
    int weapons_x[5]; 
    int weapons_y[5]; 
/// Spells
// each element in this array shows the number of the corresponding spell in enchant room (which is either 0 or 1)
    int spells[3];// 0 : Health  → H
                  // 1 : Speed   → $
                  // 2 : Damage  → !
    int spells_x[3];
    int spells_y[3];
    
/// Enemies:
// each element in this array shows the number of the corresponding enemy in room (which is either 0 or 1)
    int enemies[5];
    int enemies_x[5];
    int enemies_y[5];
    int enemies_remained_health[5];
    int can_enemy_move[5];
    // 0 : Deamon       (D)
    // 1 : Fire-Breath  (F)
    // 2 : Giant        (G)
    // 3 : Snake        (S)
    // 4 : Undeed       (U)

} room;


typedef struct 
{
    position pos;
    int health; // MAX = 16
    int how_full; // max: least hungry  ,  min: most hungry (dead)
                // MAX = 5
    int gold_count;
    int food_count;
    int food[4]; // 0 : regular
                 // 1 : ideal
                 // 2 : magical
                 // 3 : rotten
    int current_food;
    int weapons[5]; // 0 : Mace (m)
                    // 1 : Dagger (d)
                    // 2 : Magic Wand (w)
                    // 3 : Normal Arrow (a)
                    // 4 : Sword (s)
    int current_weapon; // 0 : Mace (m)
                        // 1 : Dagger (d)
                        // 2 : Magic Wand (w)
                        // 3 : Normal Arrow (a)
                        // 4 : Sword (s)
    int spells[3]; // 0 : Health → H
                  // 1 : Speed   → $
                  // 2 : Damage  → !
    int current_spell;
    int pick; // 1 if player has enabled picking up "spells" and "weapons" , 0 otherwise
    int color; // ...
    char username[100];
    int won; // 1 if reaches treasure room
    int floor_level;
    int kills;
    int difficulty;

} player;

typedef struct {
    char username[50];
    int rank; // to be calculated, not read
    int total_score;
    int latest_gold;
    int experience;
} ScoreEntry;

//////// new_map:
int valid_4_corr(int , int);
void build_corr(int , position*** , room ** , int , int*);
void build_corr2(int , position*** , room ** , int , int*);
void new_map();
void print_map();
void print_room();
void print_room_even_if_hidden();
void print_corridors();
void add_door_and_window();
void add_pillars();
void add_food();
void add_gold();
void add_black_gold();
void add_trap();
void add_weapon();
// void add_enemy();
void add_enemy2(room**  , int );
void enemy_test_ptr();
void add_spell();
int number_of_rooms();
int room_valid();
int find_min_y();
void sort_rooms();
int can_corridor_pass(int  , int , room*  , int );

//////// pregame_menu:
void pregame_menu();
void settings();
void choose_song();
void choose_color();
void choose_difficulty();
void show_saved_games();
void New_Game();
void print_menu(int , char** , int , int , const char*);
void entrance_menu();
void draw_borders(int);
void draw_title(const char*);
void show_score_table(char* , int );

//////// score table:
int compare_score(const void *, const void *);
int read_score_table2(ScoreEntry *);
void show_score_table2(char* , int );
void show_score_table(char* , int );
int compare_rank(const void *, const void *);
void update_score_table(player);
void draw_borders(int);
void pregame_menu();

//////// entrance menu:
void draw_title(const char*);
void draw_borders(int);
void entrance_menu();
void print_menu(int , char** , int , int , const char*);
void show_score_table(char* , int );

//////// log in :
int check_password();
void log_in();
void draw_borders(int);
void draw_title(const char*);

//////// messages:
void help();
void food_list();
void weapon_list();
void spell_list();
void print_top_message();
void print_bottom_message();

//////// song:
void play_soundtrack(const char *);
void stop_soundtrack();
void choose_soundtrack(int);
void init_audio();

//////// move:
int x_moves[] = {-1 , +1 , +0 , +0 , -1 , -1 , +1 , +1}; // up , down , right , left , up-right , up-left , down-right , down-left
int y_moves[] = {+0 , +0 , +1 , -1 , +1 , -1 , +1 , -1};
int valid_move();
void movement();
void movement2();
void pick(int , int  , int , int , player* , room**  , int );
int in_which_room();
int which_food_in_room();
void trap();
void win();
void death();

//////// new_user:
int already_a_username();
int is_pass_valid();
int is_email_valid();
void generate_pass();
void create_user();
void append_username();
void make_user_directory();
void create_user_data_file();
void draw_borders(int);
void draw_title(const char*);

///////////////// Enemy 
int near_deamon(player );
int near_fire_breathing_monster (player );
int near_giant (room* , int , player ); // check for room index
int near_snake (player );
int near_undeed (player );

/////// save game:
void Pause(room **  , position **  , player  , int* , int*  , int  , int );
void save_data(player , room **, int *, position **, int *, int , int , int);


int compare_score(const void *a, const void *b){
    return ((ScoreEntry *)b)->total_score - ((ScoreEntry *)a)->total_score; // Descending order
}

int read_score_table2(ScoreEntry *entries){
    FILE *file = fopen(Score_Table, "r");
    if (file == NULL) {
        perror("Error opening score table file");
        return 0;
    }

    int player_count;
    fscanf(file, "number of players: %d\n", &player_count);

    for (int i = 0; i < player_count; i++) {
        fscanf(file, "username: %s\ntotal score: %d\nlatest gold count: %d\nexperience: %d\n\n", 
               entries[i].username, 
               &entries[i].total_score, 
               &entries[i].latest_gold, 
               &entries[i].experience);
    }

    fclose(file);
    return player_count;
}

void show_score_table2(char* my_username, int page) {
    ScoreEntry entries[100]; 
    int entry_count = read_score_table2(entries);
    if (entry_count == 0){
        return;
    }

    // sorting entries by total score
    qsort(entries, entry_count, sizeof(ScoreEntry), compare_score);

    for (int i = 0; i < entry_count; i++) {
            entries[i].rank = i + 1;
        }

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
            if (strcmp(entries[i].username, my_username) == 0) { // the user him-/her- self
                // Bold my_username
                attron(A_BOLD | A_ITALIC);
                mvprintw(start_x + (i - start_index) + 3, start_y, "| %*d | %-*s |  %*d | %*d | %*d | %*d   | %s",
                         rank_width, entries[i].rank,
                         username_width, entries[i].username,
                         score_width, entries[i].total_score,
                         gold_width, entries[i].latest_gold,
                         games_width, entries[i].rank, 
                         experience_width, entries[i].experience,
                         label);
                attroff(A_BOLD | A_ITALIC);
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

void append_new_winner(const char *file_path, player winner , int total_score, int experience) {
    FILE *file = fopen(file_path, "r+");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    char* username = winner.username;
    int latest_gold_count = winner.gold_count;
    char line[256];
    int number_of_players = 0;

    // Read the number of players from the file
    if (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "number of players: %d", &number_of_players);
    }

    number_of_players++;

    // Move file pointer back to the beginning of the file
    rewind(file);

    // Write the new number of players to the file
    fprintf(file, "number of players: %d\n", number_of_players);

    // Move file pointer to the end of the file
    fseek(file, 0, SEEK_END);

    // Append the new player's data
    fprintf(file, "\nusername: %s\ntotal score: %d\nlatest gold count: %d\nexperience: %d\n",
            username, total_score, latest_gold_count, experience);

    fclose(file);
}


//////////////////// NEW_GAME:
void New_Game(int difficulty , int chosen_song, int CoLoR , char* username){

    char global_message[100] = "Welcome to Arvin's Rogue!";

    setlocale(LC_ALL, "");
    initscr();
    nodelay(stdscr, TRUE);
    noecho();
    cbreak();
    curs_set(FALSE);
    start_color(); 
    srand(time(NULL));  
    
    init_pair(160 , 160 , COLOR_BLACK);
    init_pair(82 , 82 , COLOR_BLACK);
    init_pair(220 , 220 , COLOR_BLACK);
    init_pair(205 , 205 , COLOR_BLACK);
    init_pair(39 , 39 , COLOR_BLACK);
    init_pair(24 , COLOR_CYAN , COLOR_BLACK);
    // int difficulty = 1;
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
            return ;
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
    int current_spell;


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
    add_black_gold(rooms_of_all_levels + 0 , n_rooms[0]);
    add_weapon(rooms_of_all_levels + 0 , n_rooms[0]);
    add_spell(rooms_of_all_levels + 0 , n_rooms[0]);
    add_enemy2(rooms_of_all_levels + 0 , n_rooms[0]);


    add_food(rooms_of_all_levels + 1 , n_rooms[1]);
    add_gold(rooms_of_all_levels + 1 , n_rooms[1]);
    add_trap(rooms_of_all_levels + 1 , n_rooms[1]);
    add_black_gold(rooms_of_all_levels + 0 , n_rooms[1]);
    add_weapon(rooms_of_all_levels + 1 , n_rooms[1]);
    add_spell(rooms_of_all_levels + 1 , n_rooms[1]);
    add_enemy2(rooms_of_all_levels + 1 , n_rooms[1]);


    add_food(rooms_of_all_levels + 2 , n_rooms[2]);
    add_gold(rooms_of_all_levels + 2 , n_rooms[2]);
    add_trap(rooms_of_all_levels + 2 , n_rooms[2]);
    add_black_gold(rooms_of_all_levels + 0 , n_rooms[2]);
    add_weapon(rooms_of_all_levels + 2 , n_rooms[2]);
    add_spell(rooms_of_all_levels + 2 , n_rooms[2]);
    add_enemy2(rooms_of_all_levels + 2 , n_rooms[2]);

    add_food(rooms_of_all_levels + 3 , n_rooms[3]);
    add_gold(rooms_of_all_levels + 3 , n_rooms[3]);
    add_trap(rooms_of_all_levels + 3 , n_rooms[3]);
    add_black_gold(rooms_of_all_levels + 0 , n_rooms[3]);
    add_weapon(rooms_of_all_levels + 3 , n_rooms[3]);
    add_spell(rooms_of_all_levels + 3 , n_rooms[3]);
    add_enemy2(rooms_of_all_levels + 3 , n_rooms[3]);
    // enemy_test_ptr(rooms_of_all_levels + 3 , n_rooms[3]);

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
    me.food[0] = 0;
    me.food[1] = 0;
    me.food[2] = 0;
    me.food[3] = 0;
    me.current_food = 0; // normal food (default)
    me.gold_count = 0;
    me.health = 16;
    me.how_full = 5;
    me.color = CoLoR; 
    me.pick = 0;  
    me.floor_level = 1;
    me.kills = 0;
    me.difficulty = difficulty;
    
    strcpy(me.username , username);
    me.current_weapon = 0; // 0 : Mace (m)
                        // 1 : Dagger (d)
                        // 2 : Magic Wand (w)
                        // 3 : Normal Arrow (a)
                        // 4 : Sword (s)
    me.current_spell = 0;// 0 : Health H
                         // 1 : Speed $
                         // 2 : Damage !
    for (int w = 0 ; w < 5 ; w++){
        me.weapons[w] = 0;
    }
    me.weapons[0] = 1;
    for (int s = 0 ; s < 3 ; s++){
        me.spells[s] = 0;
    }


    // Set getch() to be non-blocking
    nodelay(stdscr, TRUE);

    // Initialize audio
    init_audio();
    // int chosen_song = 3; // from settings
    int current_song = chosen_song; // Start with song1

    // Example: user chooses a soundtrack
    choose_soundtrack(current_song);
    int PiCk = 1;
    int print_all_Map = 0;

    // For calculating hits and damage, we work with a loop counter
    int hits_loop_counter = 0;
    int rate_hits;
    if(difficulty == 1){
        rate_hits = 17000;
    }
    else if(difficulty == 2){
        rate_hits = 11000;
    }
    else if(difficulty == 3){
        rate_hits = 9000;
    }

    int damage_coeff = 1;
    int speed = 1; // doubles if we use speed spell  OR  temporary fast move is on
    int temp_fast_move_loop_count = 0;
    int n_t_units_fast_active = 3;
    int spell_loop_counter = 0;
    int time_unit = 8000;
    int n_t_units_spell_active = 15;

    int healing_coeff = 1;
    int rate_heal = 50000;
    int health_loop_count = 0;

    int rate_get_hungry = 230000;
    int hunger_loop_count = 0;

    int giant_move_counter = 0;
    int is_giant_moving = 0;
    int n_t_units_giant_move = 5;
    int undead_move_counter = 0;
    int is_undead_moving = 0;
    int n_t_units_undead_move = 5;
    int snake_move_counter = 0;
    int is_snake_moving = 0;

    int Loop_Counter_change_food_with_time = 0;
    int Rate_change_food_with_time = 500000;


    while(1){
        if(!print_all_Map){
          for (int i = 0 ; i < n_rooms[level_num - 1] ; i++){
                print_room(rooms_of_all_levels[level_num - 1] + i);
            }
        }
        else{
            for (int i = 0 ; i < n_rooms[level_num - 1] ; i++){
                print_room_even_if_hidden(rooms_of_all_levels[level_num - 1] + i);
            }
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
                    if(x_c > 2){
                        attron(COLOR_PAIR(36));
                        mvprintw(x_c , y_c , "#");
                        attroff(COLOR_PAIR(36));
                    }
                }
            }
        }
        
        // room exploration
        if(rooms_of_all_levels[level_num - 1][in_which_room(rooms_of_all_levels[level_num - 1] , n_rooms[level_num - 1] , me)].hide == 1){
            rooms_of_all_levels[level_num - 1][in_which_room(rooms_of_all_levels[level_num - 1] , n_rooms[level_num - 1] , me)].hide = 0;
        }
                
        // Winning in the Treasure Room!!
        if(current_song != 6 && level_num == 4 && rooms_of_all_levels[level_num - 1][in_which_room(rooms_of_all_levels[level_num - 1] , n_rooms[level_num - 1] , me)].type == 3
           && !rooms_of_all_levels[level_num - 1][in_which_room(rooms_of_all_levels[level_num - 1] , n_rooms[level_num - 1] , me)].enemies[0]
           && !rooms_of_all_levels[level_num - 1][in_which_room(rooms_of_all_levels[level_num - 1] , n_rooms[level_num - 1] , me)].enemies[1]
           && !rooms_of_all_levels[level_num - 1][in_which_room(rooms_of_all_levels[level_num - 1] , n_rooms[level_num - 1] , me)].enemies[2]
           && !rooms_of_all_levels[level_num - 1][in_which_room(rooms_of_all_levels[level_num - 1] , n_rooms[level_num - 1] , me)].enemies[3]
           && !rooms_of_all_levels[level_num - 1][in_which_room(rooms_of_all_levels[level_num - 1] , n_rooms[level_num - 1] , me)].enemies[4]){
                win(&current_song , &me);
                chosen_song = 6;
                me.won = 1;
                snprintf(global_message, sizeof(char) * 100, "\xF0\x9F\x8E\x89 \xF0\x9F\x8E\x89 \xF0\x9F\x8E\x89                               ");       
                // (global_message , "\xF0\x9F\x8E\x89");
                if (strcmp(me.username , "GUEST") != 0) {
                    char path[1024];
                    snprintf(path, sizeof(path), "/home/arvin_rsl/Desktop/FOP_Project/Users_Folder/%s/user_data.txt", me.username);

                    FILE *file = fopen(path, "r");
                    if (file == NULL) {
                        perror("Error opening file");
                        return ;
                    }
                    char line[256];
                    long long time_creation;
                    long long now;

                    // Get the current time in seconds since the Unix epoch
                    now = (long long)time(NULL);
                    while (fgets(line, sizeof(line), file)) {
                        if (strncmp(line, "time: ", 6) == 0) {
                            sscanf(line + 6, "%lld", &time_creation);
                            break;
                        }
                    }
                    // int log10_value = (int) log10((double)time_creation);
                    // int log10_value_now = (int) log10((double)now);
                    // int exper = 1000* (log10_value_now - log10_value);
                    int exper = abs(now - time_creation) / 100;
                    fclose(file);
                    // I defined :
                        // score: (int)(me.kills * me.gold_count * me.health / 100) 
                        // experience: abs(t_now - time_creation) / 100      
                    append_new_winner(Score_Table , me , (int)(me.kills * me.gold_count * me.health / 100)  , exper);
                    save_data(me , rooms_of_all_levels , n_rooms , corridors_of_all_levels , corr_count , 4 , difficulty , chosen_song);
                }
        }

        // Death!!
        else if(me.health <= 0){
            death();
            snprintf(global_message, sizeof(char) * 100, "\xF0\x9F\x92\x80 \xF0\x9F\x92\x80 \xF0\x9F\x92\x80                                   ");       

        }
        // Nightmare Room song
        else if(current_song != 5 && rooms_of_all_levels[level_num - 1][in_which_room(rooms_of_all_levels[level_num - 1] , n_rooms[level_num - 1] , me)].type == 4){
            // Stop current soundtrack
            stop_soundtrack();
            current_song = 5;
            init_audio();
            choose_soundtrack(current_song);
        }
        // Enchant Room song
        else if(current_song!=4 && rooms_of_all_levels[level_num - 1][in_which_room(rooms_of_all_levels[level_num - 1] , n_rooms[level_num - 1] , me)].type == 2){
            // Enchant Room!!
            stop_soundtrack();
            current_song = 4;
            init_audio();
            choose_soundtrack(current_song);
        }
        // Regular room song
        if(current_song != chosen_song
            && rooms_of_all_levels[level_num - 1][in_which_room(rooms_of_all_levels[level_num - 1] , n_rooms[level_num - 1] , me)].type != 2
            && rooms_of_all_levels[level_num - 1][in_which_room(rooms_of_all_levels[level_num - 1] , n_rooms[level_num - 1] , me)].type != 3
            && rooms_of_all_levels[level_num - 1][in_which_room(rooms_of_all_levels[level_num - 1] , n_rooms[level_num - 1] , me)].type != 4){
            stop_soundtrack();
            current_song = chosen_song;
            init_audio();
            choose_soundtrack(current_song);
        }
        
        print_corridors(corridors_of_all_levels[level_num - 1] , *(corr_count + level_num - 1));

        print_top_message(global_message);
        
        print_bottom_message(&me , level_num);

        attron(COLOR_PAIR(me.color) );
        mvprintw(me.pos.x , me.pos.y , "%c" , 'A');
        int ch = getch();
        if (ch == 'q' || ch == 'Q') {
            stop_soundtrack();
            break;  
        }
        else if (ch == 's') {
            // Stop current soundtrack
            stop_soundtrack();

            // Switch to the next song (don't switch)
            current_song = 3;
            init_audio();
            choose_soundtrack(current_song);
        }
        else if (ch == '/') {
            nodelay(stdscr, FALSE);
            help(&me);  // Show help screen if '/' key is pressed
            nodelay(stdscr, TRUE);
        }
        else if (ch == 'f' || ch == 'F') {
            nodelay(stdscr, FALSE);
            food_list(&me);  // Show food screen if 'f' key is pressed
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
        else if (ch == 'P' || ch == 'p') {
            Pause(rooms_of_all_levels , corridors_of_all_levels , me , n_rooms , corr_count , difficulty , chosen_song);
        }
        else if (ch == 'm' || ch == 'M') {
            if(print_all_Map){
                clear();
                print_all_Map = 0;
            }
            else{
                print_all_Map = 1;
            }
        }
        else if (ch == 'c' || ch == 'C') {
            if(me.food_count > 0){
                if(me.how_full != 5){ // don't consume if health is full
                
                    // if (me.current_food != 3){
                    //     if(me.how_full <= 4){
                    //         me.how_full++; 
                    //     }
                    //     else{
                    //         me.how_full = 5;  // maximum of health 
                    //     }
                    // }
                    // else{
                    //     me.how_full--; 
                    // }

                    switch (me.current_food)
                    {
                    case 0:
                        // normal
                        if (me.food[0] > 0){
                            snprintf(global_message, sizeof(char) * 100, "Normal Food consumed \U0001F96A                                            ");
                            me.food[0] -- ;
                            me.food_count--;
                            if (me.how_full < 5){
                                me.how_full++;
                            }
                            else{
                                me.how_full = 5;
                            }
                            break;
                        }
                        else{
                            me.current_food = 3;
                            if (me.food[3] > 0){
                                me.food[3] --;
                                snprintf(global_message, sizeof(char) * 100, "Rotten Food consumed \U0001F922                                           ");
                                me.health --;
                                me.food_count--;
                                me.how_full--;
                                break;
                            }
                            else{
                                snprintf(global_message, sizeof(char) * 100, "\u2757 Out of Normal Food                                                ");
                                break;
                            }
                        }
                        break;
                    case 1:
                        // ideal
                        if (me.food[1] > 0){
                            snprintf(global_message, sizeof(char) * 100, "Ideal Food consumed \U0001F357                                            ");                    
                            damage_coeff = 2;
                            spell_loop_counter = 0;
                            me.food[1] -- ;
                            me.food_count--;
                            if (me.how_full < 5){
                                me.how_full++;
                            }
                            else{
                                me.how_full = 5;
                            }
                            break;
                        }
                        else{
                            snprintf(global_message, sizeof(char) * 100, "\u2757 Out of Ideal Food                                                ");
                            break;
                        }

                        break;
                    case 2:
                        // magic
                        if (me.food[2] > 0){
                            snprintf(global_message, sizeof(char) * 100, "Magical Food consumed \U0001F36D                                            ");
                            speed = 2;
                            spell_loop_counter = 0;
                            me.food[2] -- ;
                            me.food_count--;
                            if (me.how_full < 5){
                                me.how_full++;
                            }
                            else{
                                me.how_full = 5;
                            }
                            break;
                        }
                        else{
                            snprintf(global_message, sizeof(char) * 100, "\u2757 Out of Magical Food                                                ");
                            break;
                        }

                        break;
                    case 3:
                        // rotten

                        if (me.food[3] > 0){
                            snprintf(global_message, sizeof(char) * 100, "Rotten Food consumed \U0001F922                                           ");
                            me.food[3] -- ;
                            me.health --;
                            me.food_count--;
                            me.how_full--;
                            break;
                        }
                        else{
                            me.current_food = 0;
                            if (me.food[0] > 0){
                                me.food[0] --;
                                snprintf(global_message, sizeof(char) * 100, "Normal Food consumed \U0001F96A                                            ");
                                me.food_count--;
                                me.how_full++;
                                break;
                            }
                            else{
                                snprintf(global_message, sizeof(char) * 100, "\u2757 Out of Normal Food                                                ");
                                break;
                            }
                        }
                        break;
                    default:
                        break;
                    }

                }
                else{
                    snprintf(global_message, sizeof(char) * 100, "\u2755 You are already full                                          ");
                }

            }
            else{
                snprintf(global_message, sizeof(char) * 100, "\u2757 Out of food                                                ");
            }

        }
        else if (ch == ' ') {
            // attack with current weapon in hand

            int room_index = in_which_room(rooms_of_all_levels[level_num - 1] , n_rooms[level_num - 1] , me);
                // 0 : Mace (m)
                // 1 : Dagger (d)
                // 2 : Magic Wand (w)
                // 3 : Normal Arrow (a)
                // 4 : Sword (s)
            
            switch (me.current_weapon)
            {
                int range = 5; 
                int throw_direction = '0';
                int direction = 0;
                int x_next = me.pos.x;
                int y_next = me.pos.y;
                /// Close range
                case 0:
                    // mace
                    int Damage_Mace = damage_coeff * 5;
                    if(near_deamon(me)){
                        int alive_before;
                        int alive_now;
                        if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[0] > 0){
                            alive_before = 1;
                        }
                        else{
                            alive_before =0;
                        }

                        rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[0] -= Damage_Mace;

                        if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[0] > 0){
                            alive_now = 1;
                        }
                        else{
                            alive_now =0;
                        }

                        if(alive_before && !alive_now){
                            clear();
                            me.kills++;
                            snprintf(global_message, sizeof(char) * 100, "\U0001F4AA Deamon was killed!                                      "); 
                        }
                        break;
                    }
                    else if(near_fire_breathing_monster(me)){
                        int alive_before;
                        int alive_now;
                        if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[1] > 0){
                            alive_before = 1;
                        }
                        else{
                            alive_before =0;
                        }

                        rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[1] -= Damage_Mace;

                        if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[1] > 0){
                            alive_now = 1;
                        }
                        else{
                            alive_now =0;
                        }

                        if(alive_before && !alive_now){
                            clear();
                            me.kills++;

                            snprintf(global_message, sizeof(char) * 100, "\U0001F4AA Fire-Breathing Monster was killed!                             "); 
                        }
                        break;
                    }
                    else if(near_giant(rooms_of_all_levels[level_num - 1] , n_rooms[level_num - 1] , me)){
                        int alive_before;
                        int alive_now;
                        if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[2] > 0){
                            alive_before = 1;
                        }
                        else{
                            alive_before =0;
                        }

                        rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[2] -= Damage_Mace;

                        if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[2] > 0){
                            alive_now = 1;
                        }
                        else{
                            alive_now =0;
                        }

                        if(alive_before && !alive_now){
                            clear();
                            me.kills++;

                            is_giant_moving = 0;
                            snprintf(global_message, sizeof(char) * 100, "\U0001F4AA Giant was killed!                                        "); 
                        }
                        break;
                    }
                    else if(near_snake(me)){
                        int alive_before;
                        int alive_now;
                        if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[3] > 0){
                            alive_before = 1;
                        }
                        else{
                            alive_before =0;
                        }

                        rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[3] -= Damage_Mace;

                        if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[3] > 0){
                            alive_now = 1;
                        }
                        else{
                            alive_now =0;
                        }

                        if(alive_before && !alive_now){
                            clear();
                            me.kills++;

                            is_snake_moving = 0;
                            snprintf(global_message, sizeof(char) * 100, "\U0001F4AA Snake was killed!                                            "); 
                        }
                        break;
                    }
                    else if(near_undeed(me)){
                        int alive_before;
                        int alive_now;
                        if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[4] > 0){
                            alive_before = 1;
                        }
                        else{
                            alive_before =0;
                        }

                        rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[4] -= Damage_Mace;

                        if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[4] > 0){
                            alive_now = 1;
                        }
                        else{
                            alive_now =0;
                        }

                        if(alive_before && !alive_now){
                            clear();
                            me.kills++;

                            is_undead_moving = 0;
                            snprintf(global_message, sizeof(char) * 100, "\U0001F4AA Undead is now very much dead ! :)                                      "); 
                        }
                        break;
                    }
                    break;

                case 4:
                    // sword
                    int Damage_Sword = damage_coeff * 10;
                    if(near_deamon(me)){
                        int alive_before;
                        int alive_now;
                        if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[0] > 0){
                            alive_before = 1;
                        }
                        else{
                            alive_before =0;
                        }

                        rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[0] -= Damage_Sword;

                        if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[0] > 0){
                            alive_now = 1;
                        }
                        else{
                            alive_now =0;
                        }

                        if(alive_before && !alive_now){
                            clear();
                            me.kills++;

                            snprintf(global_message, sizeof(char) * 100, "\U0001F4AA Deamon was killed!                                      "); 
                        }
                        break;
                    }
                    else if(near_fire_breathing_monster(me)){
                        int alive_before;
                        int alive_now;
                        if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[1] > 0){
                            alive_before = 1;
                        }
                        else{
                            alive_before =0;
                        }

                        rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[1] -= Damage_Sword;

                        if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[1] > 0){
                            alive_now = 1;
                        }
                        else{
                            alive_now =0;
                        }

                        if(alive_before && !alive_now){
                            clear();
                            me.kills++;

                            snprintf(global_message, sizeof(char) * 100, "\U0001F4AA Fire-Breathing Monster was killed!                             "); 
                        }
                        break;
                    }
                    else if(near_giant(rooms_of_all_levels[level_num - 1] , n_rooms[level_num - 1] , me)){
                        int alive_before;
                        int alive_now;
                        if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[2] > 0){
                            alive_before = 1;
                        }
                        else{
                            alive_before =0;
                        }

                        rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[2] -= Damage_Sword;

                        if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[2] > 0){
                            alive_now = 1;
                        }
                        else{
                            alive_now =0;
                        }

                        if(alive_before && !alive_now){
                            clear();
                            is_giant_moving = 0;
                            me.kills++;

                            snprintf(global_message, sizeof(char) * 100, "\U0001F4AA Giant was killed!                                        "); 
                        }
                        break;
                    }
                    else if(near_snake(me)){
                        int alive_before;
                        int alive_now;
                        if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[3] > 0){
                            alive_before = 1;
                        }
                        else{
                            alive_before =0;
                        }

                        rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[3] -= Damage_Sword;

                        if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[3] > 0){
                            alive_now = 1;
                        }
                        else{
                            alive_now =0;
                        }

                        if(alive_before && !alive_now){
                            clear();
                            is_snake_moving = 0;
                            me.kills++;

                            snprintf(global_message, sizeof(char) * 100, "\U0001F4AA Snake was killed!                                            "); 
                        }
                        break;
                    }
                    else if(near_undeed(me)){
                        int alive_before;
                        int alive_now;
                        if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[4] > 0){
                            alive_before = 1;
                        }
                        else{
                            alive_before =0;
                        }

                        rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[4] -= Damage_Sword;

                        if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[4] > 0){
                            alive_now = 1;
                        }
                        else{
                            alive_now =0;
                        }

                        if(alive_before && !alive_now){
                            clear();
                            is_undead_moving = 0;
                            me.kills++;

                            snprintf(global_message, sizeof(char) * 100, "\U0001F4AA Undead is now very much dead ! :)                                      "); 
                        }
                        break;
                    }
                    break;
                
                /// Far range
        
                case 1:
                    // dagger
                    int Damage_Dagger = damage_coeff * 12;
                    range = 5;
                    throw_direction = '0';
                    while (! (throw_direction == '8' || throw_direction == 'j' || throw_direction == 'J'
                        || throw_direction == '2' || throw_direction == 'k' || throw_direction == 'K'
                        || throw_direction == '6' || throw_direction == 'l' || throw_direction == 'L'
                        || throw_direction == '4' || throw_direction == 'h' || throw_direction == 'H'
                        || throw_direction == '9' || throw_direction == 'y' || throw_direction == 'Y'
                        || throw_direction == '7' || throw_direction == 'u' || throw_direction == 'U'
                        || throw_direction == '3' || throw_direction == 'n' || throw_direction == 'N'
                        || throw_direction == '1' || throw_direction == 'b' || throw_direction == 'B') ){
                            throw_direction = getch();
                    }

                    direction = 0;
                    x_next = me.pos.x;
                    y_next = me.pos.y;
                    // int x_moves[] = {-1 , +1 , +0 , +0 , -1 , -1 , +1 , +1}; // up , down , right , left , up-right , up-left , down-right , down-left
                    // int y_moves[] = {+0 , +0 , +1 , -1 , +1 , -1 , +1 , -1};
                    if (throw_direction == '8' || throw_direction == 'j' || throw_direction == 'J'){
                        direction = 0;
                    }
                    else if (throw_direction == '2' || throw_direction == 'k' || throw_direction == 'K'){
                        direction = 1;
                    }
                    else if (throw_direction == '6' || throw_direction == 'l' || throw_direction == 'L'){
                        direction = 2;
                    }
                    else if (throw_direction == '4' || throw_direction == 'h' || throw_direction == 'H'){
                        direction =3;
                    }
                    else if (throw_direction == '9' || throw_direction == 'y' || throw_direction == 'Y'){
                        direction = 4;
                    }
                    else if (throw_direction == '7' || throw_direction == 'u' || throw_direction == 'U'){
                        direction = 5;
                    }
                    else if (throw_direction == '3' || throw_direction == 'n' || throw_direction == 'N'){
                        direction = 6;
                    }
                    else if (throw_direction == '1' || throw_direction == 'b' || throw_direction == 'B'){
                        direction = 7;
                    }
                    
                    for(int go = 0 ; go < range ; go++){
                        x_next += x_moves[direction];
                        y_next += y_moves[direction];
                        char There = mvinch(x_next , y_next) & A_CHARTEXT;
                        if (valid_move(x_next , y_next) && There != 'G' && There != '+' && There != '<'){
                            continue;
                        }
                        else{

                            if(There == 'D'){
                                clear();
                                snprintf(global_message, sizeof(char) * 100, "Dagger hit the Deamon                                        "); 
                            
                                int alive_before;
                                int alive_now;
                                if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[0] > 0){
                                    alive_before = 1;
                                }
                                else{
                                    alive_before =0;
                                }

                                rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[0] -= Damage_Dagger;

                                if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[0] > 0){
                                    alive_now = 1;
                                }
                                else{
                                    alive_now =0;
                                }

                                if(alive_before && !alive_now){
                                    clear();
                                    me.kills++;
                                    snprintf(global_message, sizeof(char) * 100, "\U0001F4AA Deamon was killed!                                      "); 
                                }
                                break;
                            }
                            else if (There == 'F'){
                                clear();
                                snprintf(global_message, sizeof(char) * 100, "Dagger hit the Fire-Breathin Monster                                        "); 
                            
                                int alive_before;
                                int alive_now;
                                if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[1] > 0){
                                    alive_before = 1;
                                }
                                else{
                                    alive_before =0;
                                }

                                rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[1] -= Damage_Dagger;

                                if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[1] > 0){
                                    alive_now = 1;
                                }
                                else{
                                    alive_now =0;
                                }

                                if(alive_before && !alive_now){
                                    clear();
                                    me.kills++;

                                    snprintf(global_message, sizeof(char) * 100, "\U0001F4AA Fire-Breathing Monster was killed!                                  "); 
                                }
                                break;
                            }
                            else if (There == 'G' && room_index != 0){
                                clear();
                                snprintf(global_message, sizeof(char) * 100, "Dagger hit the Giant                                        "); 
                            
                                int alive_before;
                                int alive_now;
                                if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[2] > 0){
                                    alive_before = 1;
                                }
                                else{
                                    alive_before =0;
                                }

                                rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[2] -= Damage_Dagger;

                                if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[2] > 0){
                                    alive_now = 1;
                                }
                                else{
                                    alive_now =0;
                                }

                                if(alive_before && !alive_now){
                                    clear();
                                    is_giant_moving = 0;
                                    me.kills++;

                                    snprintf(global_message, sizeof(char) * 100, "\U0001F4AA Giant was killed!                                          "); 
                                }
                                break;
                            }
                            else if (There == 'S'){
                                clear();
                                snprintf(global_message, sizeof(char) * 100, "Dagger hit the Snake                                        "); 
                            
                                int alive_before;
                                int alive_now;
                                if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[3] > 0){
                                    alive_before = 1;
                                }
                                else{
                                    alive_before =0;
                                }

                                rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[3] -= Damage_Dagger;

                                if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[3] > 0){
                                    alive_now = 1;
                                }
                                else{
                                    alive_now =0;
                                }

                                if(alive_before && !alive_now){
                                    clear();
                                    is_snake_moving = 0;
                                    me.kills++;

                                    snprintf(global_message, sizeof(char) * 100, "\U0001F4AA Snake was killed!                                          "); 
                                }
                                break;
                            }
                            else if (There == 'U'){
                                clear();
                                snprintf(global_message, sizeof(char) * 100, "Dagger hit the Undead                                        "); 
                                int alive_before;
                                int alive_now;
                                if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[4] > 0){
                                    alive_before = 1;
                                }
                                else{
                                    alive_before =0;
                                }

                                rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[4] -= Damage_Dagger;

                                if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[4] > 0){
                                    alive_now = 1;
                                }
                                else{
                                    alive_now =0;
                                }

                                if(alive_before && !alive_now){
                                    clear();
                                    is_undead_moving = 0;
                                    me.kills++;

                                    snprintf(global_message, sizeof(char) * 100, "\U0001F4AA Undead is now very much dead ! :)                                      "); 
                                }
                                break;
                            }
                            else{
                                clear();
                                snprintf(global_message, sizeof(char) * 100, "Dagger didn't hit anything!                                    "); 
                                break;
                            }
                        }
                    }
                    if (me.weapons[1] <= 0){
                        clear();
                        snprintf(global_message, sizeof(char) * 100, "\xE2\x9D\x97 You are out of Daggers                                       "); 
                    }
                    else{
                        me.weapons[1]--;
                    }

                    break;

                case 3:
                    // arrow
                    int Damage_Arrow = damage_coeff * 5;
                    range = 5; // برد پرتاب
                    throw_direction = '0';
                    while (! (throw_direction == '8' || throw_direction == 'j' || throw_direction == 'J'
                        || throw_direction == '2' || throw_direction == 'k' || throw_direction == 'K'
                        || throw_direction == '6' || throw_direction == 'l' || throw_direction == 'L'
                        || throw_direction == '4' || throw_direction == 'h' || throw_direction == 'H'
                        || throw_direction == '9' || throw_direction == 'y' || throw_direction == 'Y'
                        || throw_direction == '7' || throw_direction == 'u' || throw_direction == 'U'
                        || throw_direction == '3' || throw_direction == 'n' || throw_direction == 'N'
                        || throw_direction == '1' || throw_direction == 'b' || throw_direction == 'B') ){
                            throw_direction = getch();
                    }

                    direction = 0;
                    x_next = me.pos.x;
                    y_next = me.pos.y;
                    // int x_moves[] = {-1 , +1 , +0 , +0 , -1 , -1 , +1 , +1}; // up , down , right , left , up-right , up-left , down-right , down-left
                    // int y_moves[] = {+0 , +0 , +1 , -1 , +1 , -1 , +1 , -1};
                    if (throw_direction == '8' || throw_direction == 'j' || throw_direction == 'J'){
                        direction = 0;
                    }
                    else if (throw_direction == '2' || throw_direction == 'k' || throw_direction == 'K'){
                        direction = 1;
                    }
                    else if (throw_direction == '6' || throw_direction == 'l' || throw_direction == 'L'){
                        direction = 2;
                    }
                    else if (throw_direction == '4' || throw_direction == 'h' || throw_direction == 'H'){
                        direction =3;
                    }
                    else if (throw_direction == '9' || throw_direction == 'y' || throw_direction == 'Y'){
                        direction = 4;
                    }
                    else if (throw_direction == '7' || throw_direction == 'u' || throw_direction == 'U'){
                        direction = 5;
                    }
                    else if (throw_direction == '3' || throw_direction == 'n' || throw_direction == 'N'){
                        direction = 6;
                    }
                    else if (throw_direction == '1' || throw_direction == 'b' || throw_direction == 'B'){
                        direction = 7;
                    }
                    
                    for(int go = 0 ; go < range ; go++){
                        x_next += x_moves[direction];
                        y_next += y_moves[direction];
                        char There = mvinch(x_next , y_next) & A_CHARTEXT;
                        if (valid_move(x_next , y_next) && There != 'G' && There != '+' && There != '<'){
                            continue;
                        }
                        else{

                            if(There == 'D'){
                                clear();
                                snprintf(global_message, sizeof(char) * 100, "Arrow hit the Deamon                                        "); 
                            
                                int alive_before;
                                int alive_now;
                                if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[0] > 0){
                                    alive_before = 1;
                                }
                                else{
                                    alive_before =0;
                                }

                                rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[0] -= Damage_Arrow;

                                if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[0] > 0){
                                    alive_now = 1;
                                }
                                else{
                                    alive_now =0;
                                }

                                if(alive_before && !alive_now){
                                    clear();
                                    me.kills++;

                                    snprintf(global_message, sizeof(char) * 100, "\U0001F4AA Deamon was killed!                                      "); 
                                }
                                break;
                            }
                            else if (There == 'F'){
                                clear();
                                snprintf(global_message, sizeof(char) * 100, "Arrow hit the Fire-Breathin Monster                                        "); 
                            
                                int alive_before;
                                int alive_now;
                                if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[1] > 0){
                                    alive_before = 1;
                                }
                                else{
                                    alive_before =0;
                                }

                                rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[1] -= Damage_Arrow;

                                if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[1] > 0){
                                    alive_now = 1;
                                }
                                else{
                                    alive_now =0;
                                }

                                if(alive_before && !alive_now){
                                    clear();
                                    me.kills++;

                                    snprintf(global_message, sizeof(char) * 100, "\U0001F4AA Fire-Breathing Monster was killed!                                  "); 
                                }
                                break;
                            }
                            else if (There == 'G' && room_index != 0){
                                clear();
                                snprintf(global_message, sizeof(char) * 100, "Arrow hit the Giant                                        "); 
                            
                                int alive_before;
                                int alive_now;
                                if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[2] > 0){
                                    alive_before = 1;
                                }
                                else{
                                    alive_before =0;
                                }

                                rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[2] -= Damage_Arrow;

                                if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[2] > 0){
                                    alive_now = 1;
                                }
                                else{
                                    alive_now =0;
                                }

                                if(alive_before && !alive_now){
                                    clear();
                                    me.kills++;

                                    is_giant_moving = 0;
                                    snprintf(global_message, sizeof(char) * 100, "\U0001F4AA Giant was killed!                                          "); 
                                }
                                break;
                            }
                            else if (There == 'S'){
                                clear();
                                snprintf(global_message, sizeof(char) * 100, "Arrow hit the Snake                                        "); 
                            
                                int alive_before;
                                int alive_now;
                                if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[3] > 0){
                                    alive_before = 1;
                                }
                                else{
                                    alive_before =0;
                                }

                                rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[3] -= Damage_Arrow;

                                if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[3] > 0){
                                    alive_now = 1;
                                }
                                else{
                                    alive_now =0;
                                }

                                if(alive_before && !alive_now){
                                    clear();
                                    me.kills++;

                                    is_snake_moving = 0;
                                    snprintf(global_message, sizeof(char) * 100, "\U0001F4AA Snake was killed!                                          "); 
                                }
                                break;
                            }
                            else if (There == 'U'){
                                clear();
                                snprintf(global_message, sizeof(char) * 100, "Arrow hit the Undead                                        "); 
                                int alive_before;
                                int alive_now;
                                if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[4] > 0){
                                    alive_before = 1;
                                }
                                else{
                                    alive_before =0;
                                }

                                rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[4] -= Damage_Arrow;

                                if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[4] > 0){
                                    alive_now = 1;
                                }
                                else{
                                    alive_now =0;
                                }

                                if(alive_before && !alive_now){
                                    clear();
                                    me.kills++;

                                    is_undead_moving = 0;
                                    snprintf(global_message, sizeof(char) * 100, "\U0001F4AA Undead is now very much dead ! :)                                      "); 
                                }
                                break;
                            }
                            else if(There == '.' || There == '~' || There == '-' ||There == ',' || There == '+' || There == '<') {
                                clear();
                                snprintf(global_message, sizeof(char) * 100, "Arrow didn't hit anything!                                    "); 
                                break;
                            }
                            else{
                                clear();
                                snprintf(global_message, sizeof(char) * 100, "Arrow didn't hit anything!                                    "); 
                                break;
                            }
                        }
                    }
                    if (me.weapons[3] <= 0){
                        clear();
                        snprintf(global_message, sizeof(char) * 100, "\xE2\x9D\x97 You are out of Arrows                                        "); 
                    }
                    else{
                        me.weapons[3]--;
                    }
                    break;

                case 2:
                    // wand
                    int Wand_Damage = damage_coeff * 15;
                    range = 10; // برد پرتاب
                    throw_direction = '0';
                    while (! (throw_direction == '8' || throw_direction == 'j' || throw_direction == 'J'
                        || throw_direction == '2' || throw_direction == 'k' || throw_direction == 'K'
                        || throw_direction == '6' || throw_direction == 'l' || throw_direction == 'L'
                        || throw_direction == '4' || throw_direction == 'h' || throw_direction == 'H'
                        || throw_direction == '9' || throw_direction == 'y' || throw_direction == 'Y'
                        || throw_direction == '7' || throw_direction == 'u' || throw_direction == 'U'
                        || throw_direction == '3' || throw_direction == 'n' || throw_direction == 'N'
                        || throw_direction == '1' || throw_direction == 'b' || throw_direction == 'B') ){
                            throw_direction = getch();
                    }
                    

                    direction = 0;
                    x_next = me.pos.x;
                    y_next = me.pos.y;
                    // int x_moves[] = {-1 , +1 , +0 , +0 , -1 , -1 , +1 , +1}; // up , down , right , left , up-right , up-left , down-right , down-left
                    // int y_moves[] = {+0 , +0 , +1 , -1 , +1 , -1 , +1 , -1};
                    if (throw_direction == '8' || throw_direction == 'j' || throw_direction == 'J'){
                        direction = 0;
                    }
                    else if (throw_direction == '2' || throw_direction == 'k' || throw_direction == 'K'){
                        direction = 1;
                    }
                    else if (throw_direction == '6' || throw_direction == 'l' || throw_direction == 'L'){
                        direction = 2;
                    }
                    else if (throw_direction == '4' || throw_direction == 'h' || throw_direction == 'H'){
                        direction = 3;
                    }
                    else if (throw_direction == '9' || throw_direction == 'y' || throw_direction == 'Y'){
                        direction = 4;
                    }
                    else if (throw_direction == '7' || throw_direction == 'u' || throw_direction == 'U'){
                        direction = 5;
                    }
                    else if (throw_direction == '3' || throw_direction == 'n' || throw_direction == 'N'){
                        direction = 6;
                    }
                    else if (throw_direction == '1' || throw_direction == 'b' || throw_direction == 'B'){
                        direction = 7;
                    }
                    
                    for(int go = 0 ; go < range ; go++){
                        x_next += x_moves[direction];
                        y_next += y_moves[direction];
                        char There = mvinch(x_next , y_next) & A_CHARTEXT;
                        if (valid_move(x_next , y_next) && There != 'G' && There != '+' && There != '<'){
                            continue;
                        }
                        else{

                            if(There == 'D'){
                                clear();
                                snprintf(global_message, sizeof(char) * 100, "Magic Wand hit the Deamon                                        "); 
                                rooms_of_all_levels[level_num - 1][room_index].can_enemy_move[0] = 0;
                                int alive_before;
                                int alive_now;
                                if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[0] > 0){
                                    alive_before = 1;
                                }
                                else{
                                    alive_before =0;
                                }

                                rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[0] -= Wand_Damage;
                                rooms_of_all_levels[level_num - 1][room_index].can_enemy_move[0] = 0;

                                if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[0] > 0){
                                    alive_now = 1;
                                }
                                else{
                                    alive_now =0;
                                }

                                if(alive_before && !alive_now){
                                    clear();
                                    me.kills++;

                                    snprintf(global_message, sizeof(char) * 100, "\U0001F4AA Deamon was killed!                                      "); 
                                }
                                break;
                            }
                            else if (There == 'F'){
                                clear();
                                snprintf(global_message, sizeof(char) * 100, "Magic Wand hit the Fire-Breathin Monster                                        "); 
                                rooms_of_all_levels[level_num - 1][room_index].can_enemy_move[1] = 0;
                            
                                int alive_before;
                                int alive_now;
                                if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[1] > 0){
                                    alive_before = 1;
                                }
                                else{
                                    alive_before =0;
                                }

                                rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[1] -= Wand_Damage;
                                rooms_of_all_levels[level_num - 1][room_index].can_enemy_move[1] = 0;


                                if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[1] > 0){
                                    alive_now = 1;
                                }
                                else{
                                    alive_now =0;
                                }

                                if(alive_before && !alive_now){
                                    clear();
                                    me.kills++;

                                    snprintf(global_message, sizeof(char) * 100, "\U0001F4AA Fire-Breathing Monster was killed!                                  "); 
                                }
                                break;
                            }
                            else if (There == 'G' && room_index != 0){
                                clear();
                                snprintf(global_message, sizeof(char) * 100, "Magic Wand hit the Giant                                        "); 
                                rooms_of_all_levels[level_num - 1][room_index].can_enemy_move[2] = 0;
                            
                                int alive_before;
                                int alive_now;
                                if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[2] > 0){
                                    alive_before = 1;
                                }
                                else{
                                    alive_before =0;
                                }

                                rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[2] -= Wand_Damage;
                                rooms_of_all_levels[level_num - 1][room_index].can_enemy_move[2] = 0;


                                if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[2] > 0){
                                    alive_now = 1;
                                }
                                else{
                                    alive_now =0;
                                }

                                if(alive_before && !alive_now){
                                    clear();
                                    me.kills++;

                                    is_giant_moving = 0;
                                    snprintf(global_message, sizeof(char) * 100, "\U0001F4AA Giant was killed!                                          "); 
                                }
                                break;
                            }
                            else if (There == 'S'){
                                clear();
                                snprintf(global_message, sizeof(char) * 100, "Magic Wand hit the Snake                                        "); 
                                rooms_of_all_levels[level_num - 1][room_index].can_enemy_move[3] = 0;
                            
                                int alive_before;
                                int alive_now;
                                if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[3] > 0){
                                    alive_before = 1;
                                }
                                else{
                                    alive_before =0;
                                }

                                rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[3] -= Wand_Damage;
                                rooms_of_all_levels[level_num - 1][room_index].can_enemy_move[3] = 0;

                                if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[3] > 0){
                                    alive_now = 1;
                                }
                                else{
                                    alive_now =0;
                                }

                                if(alive_before && !alive_now){
                                    clear();
                                    me.kills++;

                                    is_snake_moving = 0;
                                    snprintf(global_message, sizeof(char) * 100, "\U0001F4AA Snake was killed!                                          "); 
                                }
                                break;
                            }
                            else if (There == 'U'){
                                clear();
                                snprintf(global_message, sizeof(char) * 100, "Magic Wand hit the Undead                                        "); 
                                rooms_of_all_levels[level_num - 1][room_index].can_enemy_move[4] = 0;
                                
                                int alive_before;
                                int alive_now;
                                if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[4] > 0){
                                    alive_before = 1;
                                }
                                else{
                                    alive_before =0;
                                }

                                rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[4] -= Wand_Damage;
                                rooms_of_all_levels[level_num - 1][room_index].can_enemy_move[4] = 0;

                                if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[4] > 0){
                                    alive_now = 1;
                                }
                                else{
                                    alive_now =0;
                                }

                                if(alive_before && !alive_now){
                                    clear();
                                    me.kills++;

                                    is_undead_moving = 0;
                                    snprintf(global_message, sizeof(char) * 100, "\U0001F4AA Undead is now very much dead ! :)                                      "); 
                                }
                                break;
                            }
                            else if(There == '.' || There == '~' || There == '-' ||There == ',' || There == '+' || There == '<') {
                                clear();
                                snprintf(global_message, sizeof(char) * 100, "Magic Wand didn't hit anything!                                    "); 
                                break;
                            }
                            else{
                                clear();
                                snprintf(global_message, sizeof(char) * 100, "Magic Wand didn't hit anything!                                    "); 
                                break;
                            }
                        }
                    }
                    if (me.weapons[2] <= 0){
                        clear();
                        snprintf(global_message, sizeof(char) * 100, "\xE2\x9D\x97 You are out of Magic Wands                                   "); 
                    }
                    else{
                        me.weapons[2]--;
                    }
                    break;
                
                default:
                    break;
            }

            for (int enem = 0 ; enem < 5 ; enem++){
                if(rooms_of_all_levels[level_num - 1][room_index].enemies_remained_health[enem] <= 0){
                    rooms_of_all_levels[level_num - 1][room_index].enemies[enem] = 0; // vanish
                }
            }

        }
        else if (ch == 'Z' || ch == 'z') {
            // using spells
            // 0 : Health → H
            // 1 : Speed   → $
            // 2 : Damage  → !
            switch (me.current_spell)
            {
                case 0:
                    // health
                    if (me.spells[0] > 0){
                        me.spells[0]--;
                        clear();
                        snprintf(global_message, sizeof(char) * 100, "\U0001F9EA Health spell activated! You now heal 2x faster \U0001F33F                "); 
                        healing_coeff = 2;
                        //////////////////////////////////////////////////////////////////////////
                    }
                    else{
                        me.spells[0] = 0;
                        clear();
                        snprintf(global_message, sizeof(char) * 100, "\xE2\x9D\x97 You are out of Health spells                              ");  
                    }
                    break;
                case 1:
                    // speed
                    if (me.spells[1] > 0){
                        me.spells[1]--;
                        speed = 2;
                        clear();
                        snprintf(global_message, sizeof(char) * 100, "\U0001F9EA Speed spell activated! You are now 2x faster \u26A1                      "); 
                        spell_loop_counter = 0;
                        // damage_coeff = 2;
                        //////////////////////////////////////////////////////////////////////////
                    }
                    else{
                        me.spells[1] = 0;
                        clear();
                        snprintf(global_message, sizeof(char) * 100, "\xE2\x9D\x97 You are out of Speed spells                              ");  
                    }

                    break;
                case 2:
                    // damage
                    if (me.spells[2] > 0){
                        me.spells[2]--;
                        clear();
                        snprintf(global_message, sizeof(char) * 100, "\U0001F9EA  Damage spell activated! Your hits are now 2x stronger \U0001F4A5                  "); 
                        damage_coeff = 2;
                        spell_loop_counter = 0;
                    }
                    else{
                        me.spells[2] = 0;
                        clear();
                        snprintf(global_message, sizeof(char) * 100, "\xE2\x9D\x97 You are out of Damage spells                              ");  
                    }

                    break;
                default:
                    break;
            }
        }
        else if (ch == 'v' || ch == 'V') {
            speed = 2;
            temp_fast_move_loop_count = 0;
            snprintf(global_message, sizeof(char) * 100, "\U0001F3C3 Temporary Fast Move activated! You now run 2x faster        "); 

        }
        
        // spell time limit :))
        if ((speed != 1 || damage_coeff != 1 || healing_coeff != 1)&& spell_loop_counter/time_unit < n_t_units_spell_active){
            spell_loop_counter++;
            attron(COLOR_PAIR(160));
            mvprintw(LINES - 1 , COLS - 1 - strlen("00:00") , "00:%d " , n_t_units_spell_active - spell_loop_counter/time_unit);
            attroff(COLOR_PAIR(160));
        }
        else if ((speed != 1 || damage_coeff != 1 || healing_coeff != 1)){
            clear();
            spell_loop_counter = 0;
            speed = 1;
            damage_coeff = 1;
            healing_coeff = 1;
        }


        // temp fast move time limit :))
        if ((speed != 1 ) && temp_fast_move_loop_count/time_unit < n_t_units_fast_active){
            temp_fast_move_loop_count++;
            attron(COLOR_PAIR(160));
            mvprintw(LINES - 1 , COLS - 1 - strlen("00:00") , "00:%d " , n_t_units_fast_active - temp_fast_move_loop_count/time_unit);
            attroff(COLOR_PAIR(160));
        }
        else if ((speed != 1)){
            clear();
            temp_fast_move_loop_count = 0;
            speed = 1;
            snprintf(global_message, sizeof(char) * 100, "\U0001F6B6 Temporary Fast Move timed out!                             "); 

        }



        int my_x_before = me.pos.x;
        int my_y_before = me.pos.y;
        movement2(PiCk , ch , &me , rooms_of_all_levels, n_rooms[level_num - 1] , global_message , &level_num , speed);
        int my_x_after = me.pos.x;
        int my_y_after = me.pos.y;

        attroff(COLOR_PAIR(me.color));
        // print_corridors(corridors_of_all_levels[level_num - 1] , *(corr_count + level_num - 1));
        attron(COLOR_PAIR(me.color));
        mvprintw(me.pos.x , me.pos.y , "%c" , 'A');
        attroff(COLOR_PAIR(me.color) );

        if (mvinch(0,0) & A_CHARTEXT != ' '){
            mvprintw(0,0, "%c" , ' ');
        }
        // if (mvinch(1,0) & A_CHARTEXT & A_BOLD != ' '){
        //     mvprintw(1,1, "%c" , ' ');
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

        if(near_deamon(me)){
            snprintf(global_message, sizeof(char) * 100, "\U0001F47F Deamon is hitting you!                          ");
           
            if(hits_loop_counter <= rate_hits){ // 10,000 loops
                hits_loop_counter++;
            }
            else{
                me.health--; // 1 health loss
                hits_loop_counter = 0;
            }
        }
        if(near_fire_breathing_monster(me)){
            snprintf(global_message, sizeof(char) * 100, "\U0001F409 Fire-Breathing Monster is hitting you!                  ");
           
            if(hits_loop_counter <= rate_hits){ // 10,000 loops
                hits_loop_counter++;
            }
            else{
                me.health-=2; // 2 health loss
                hits_loop_counter = 0;
            }
        }
        if(near_giant(rooms_of_all_levels[level_num - 1] , n_rooms[level_num - 1] , me)){
            snprintf(global_message, sizeof(char) * 100, "\U0001F479 Giant is hitting you!                               ");
           
            if(hits_loop_counter <= rate_hits){ // 10,000 loops
                hits_loop_counter++;
            }
            else{
                me.health-=3; // 3 health loss
                hits_loop_counter = 0;
            }
            is_giant_moving = 1;
        }
        // Giant's Movement
        if (is_giant_moving && (my_x_after != my_x_before || my_y_after != my_y_before)){
            int room_index = in_which_room(rooms_of_all_levels[level_num - 1] , n_rooms[level_num - 1] , me);
            if (rooms_of_all_levels[level_num - 1][room_index].can_enemy_move[2]){
                if (my_y_after < rooms_of_all_levels[level_num - 1][room_index].enemies_y[2]
                && valid_move(rooms_of_all_levels[level_num - 1][room_index].enemies_x[2] , rooms_of_all_levels[level_num - 1][room_index].enemies_y[2] - 1)
                && (mvinch(rooms_of_all_levels[level_num - 1][room_index].enemies_x[2] , rooms_of_all_levels[level_num - 1][room_index].enemies_y[2] - 1) & A_CHARTEXT != '+')
                && (mvinch(rooms_of_all_levels[level_num - 1][room_index].enemies_x[2] , rooms_of_all_levels[level_num - 1][room_index].enemies_y[2] - 1) & A_CHARTEXT != '#')){
                    rooms_of_all_levels[level_num - 1][room_index].enemies_y[2]--;
                }
                else if (my_y_after > rooms_of_all_levels[level_num - 1][room_index].enemies_y[2]
                && valid_move(rooms_of_all_levels[level_num - 1][room_index].enemies_x[2] , rooms_of_all_levels[level_num - 1][room_index].enemies_y[2] + 1)
                && (mvinch(rooms_of_all_levels[level_num - 1][room_index].enemies_x[2] , rooms_of_all_levels[level_num - 1][room_index].enemies_y[2] + 1) & A_CHARTEXT != '+')
                && (mvinch(rooms_of_all_levels[level_num - 1][room_index].enemies_x[2] , rooms_of_all_levels[level_num - 1][room_index].enemies_y[2] + 1) & A_CHARTEXT != '#')){
                    rooms_of_all_levels[level_num - 1][room_index].enemies_y[2]++;
                }
                else if (my_x_after > rooms_of_all_levels[level_num - 1][room_index].enemies_x[2]
                && valid_move(rooms_of_all_levels[level_num - 1][room_index].enemies_x[2] + 1, rooms_of_all_levels[level_num - 1][room_index].enemies_y[2])
                && (mvinch(rooms_of_all_levels[level_num - 1][room_index].enemies_x[2] +1, rooms_of_all_levels[level_num - 1][room_index].enemies_y[2]) & A_CHARTEXT != '+')
                && (mvinch(rooms_of_all_levels[level_num - 1][room_index].enemies_x[2] +1, rooms_of_all_levels[level_num - 1][room_index].enemies_y[2]) & A_CHARTEXT != '#')){
                    rooms_of_all_levels[level_num - 1][room_index].enemies_x[2]++;
                }
                else if (my_x_after < rooms_of_all_levels[level_num - 1][room_index].enemies_x[2]
                && valid_move(rooms_of_all_levels[level_num - 1][room_index].enemies_x[2] - 1, rooms_of_all_levels[level_num - 1][room_index].enemies_y[2])
                && (mvinch(rooms_of_all_levels[level_num - 1][room_index].enemies_x[2] -1, rooms_of_all_levels[level_num - 1][room_index].enemies_y[2] ) & A_CHARTEXT != '+')
                && (mvinch(rooms_of_all_levels[level_num - 1][room_index].enemies_x[2] -1, rooms_of_all_levels[level_num - 1][room_index].enemies_y[2] ) & A_CHARTEXT != '#')){
                    rooms_of_all_levels[level_num - 1][room_index].enemies_x[2]--;
                }
                giant_move_counter++;
            }
        }
        // Giant Stop Moving!
        if (giant_move_counter >= n_t_units_giant_move){
            giant_move_counter = 0;
            is_giant_moving = 0;
        }
        
        if(near_snake(me)){
            snprintf(global_message, sizeof(char) * 100, "\U0001F40D Snake is hitting you!                               ");
           
            if(hits_loop_counter <= rate_hits){ // 10,000 loops
                hits_loop_counter++;
            }
            else{
                me.health --; // 1 health loss
                hits_loop_counter = 0;
            }
            is_snake_moving = 1;
        }
         // Snake's Movement
        if (is_snake_moving && (my_x_after != my_x_before || my_y_after != my_y_before)){
            int room_index = in_which_room(rooms_of_all_levels[level_num - 1] , n_rooms[level_num - 1] , me);
            if (rooms_of_all_levels[level_num - 1][room_index].can_enemy_move[3]){
                if (my_y_after < rooms_of_all_levels[level_num - 1][room_index].enemies_y[3]
                && valid_move(rooms_of_all_levels[level_num - 1][room_index].enemies_x[3] , rooms_of_all_levels[level_num - 1][room_index].enemies_y[3] - 1)){
                    rooms_of_all_levels[level_num - 1][room_index].enemies_y[3]--;
                }
                else if (my_y_after > rooms_of_all_levels[level_num - 1][room_index].enemies_y[3]
                && valid_move(rooms_of_all_levels[level_num - 1][room_index].enemies_x[3] , rooms_of_all_levels[level_num - 1][room_index].enemies_y[3] + 1)){
                    rooms_of_all_levels[level_num - 1][room_index].enemies_y[3]++;
                }
                else if (my_x_after > rooms_of_all_levels[level_num - 1][room_index].enemies_x[3]
                && valid_move(rooms_of_all_levels[level_num - 1][room_index].enemies_x[3] + 1, rooms_of_all_levels[level_num - 1][room_index].enemies_y[3])){
                    rooms_of_all_levels[level_num - 1][room_index].enemies_x[3]++;
                }
                else if (my_x_after < rooms_of_all_levels[level_num - 1][room_index].enemies_x[3]
                && valid_move(rooms_of_all_levels[level_num - 1][room_index].enemies_x[3] - 1, rooms_of_all_levels[level_num - 1][room_index].enemies_y[3])){
                    rooms_of_all_levels[level_num - 1][room_index].enemies_x[3]--;
                }
                snake_move_counter++;
            }
        }
        
        if(near_undeed(me)){ ///// bro :|  it's undead!
            snprintf(global_message, sizeof(char) * 100, "\U0001F9DF Undead is hitting you!                               ");
           
            if(hits_loop_counter <= rate_hits){ // 10,000 loops
                hits_loop_counter++;
            }
            else{
                me.health -= 5; // 1 health loss
                hits_loop_counter = 0;
            }
            is_undead_moving = 1;
        }
        // Undead's Movement
        if (is_undead_moving && (my_x_after != my_x_before || my_y_after != my_y_before)){
            int room_index = in_which_room(rooms_of_all_levels[level_num - 1] , n_rooms[level_num - 1] , me);
            if (rooms_of_all_levels[level_num - 1][room_index].can_enemy_move[4]){
                if (my_y_after < rooms_of_all_levels[level_num - 1][room_index].enemies_y[4]
                && valid_move(rooms_of_all_levels[level_num - 1][room_index].enemies_x[4] , rooms_of_all_levels[level_num - 1][room_index].enemies_y[4] - 1)){
                    rooms_of_all_levels[level_num - 1][room_index].enemies_y[4]--;
                }
                else if (my_y_after > rooms_of_all_levels[level_num - 1][room_index].enemies_y[4]
                && valid_move(rooms_of_all_levels[level_num - 1][room_index].enemies_x[4] , rooms_of_all_levels[level_num - 1][room_index].enemies_y[4] + 1)){
                    rooms_of_all_levels[level_num - 1][room_index].enemies_y[4]++;
                }
                else if (my_x_after > rooms_of_all_levels[level_num - 1][room_index].enemies_x[4]
                && valid_move(rooms_of_all_levels[level_num - 1][room_index].enemies_x[4] + 1, rooms_of_all_levels[level_num - 1][room_index].enemies_y[4])){
                    rooms_of_all_levels[level_num - 1][room_index].enemies_x[4]++;
                }
                else if (my_x_after < rooms_of_all_levels[level_num - 1][room_index].enemies_x[4]
                && valid_move(rooms_of_all_levels[level_num - 1][room_index].enemies_x[4] - 1, rooms_of_all_levels[level_num - 1][room_index].enemies_y[4])){
                    rooms_of_all_levels[level_num - 1][room_index].enemies_x[4]--;
                }
                undead_move_counter++;
            }
        }
        // Undead Stop Moving!
        if (undead_move_counter >= n_t_units_undead_move){
            undead_move_counter = 0;
            is_undead_moving = 0;
        }
        
        // get hungry!
        if (hunger_loop_count < rate_get_hungry){
            hunger_loop_count++;
        }
        else{
            hunger_loop_count = 0;
            if(me.how_full > 0){
                me.how_full--;
            }
            clear();
        }

        // get healed!
        if (me.how_full == 5){
            if(health_loop_count < rate_heal/healing_coeff){
                health_loop_count++;
            }
            else{
                health_loop_count = 0;
                me.health++;
                clear();
            }
        }


        // foods change
        if (Loop_Counter_change_food_with_time < Rate_change_food_with_time){
            Loop_Counter_change_food_with_time++;
        }
        else{
                 // 0 : regular
                 // 1 : ideal
                 // 2 : magical
                 // 3 : rotten
            Loop_Counter_change_food_with_time = 0;

            if (me.food[0] > 0){
                me.food[3] += me.food[0];
                me.food[0] = 0;
            }
            if (me.food[1] > 0){
                me.food[0] += me.food[1];
                me.food[1] = 0;
            }
            if (me.food[2] > 0){
                me.food[0] += me.food[2];
                me.food[2] = 0;
            }
            snprintf(global_message, sizeof(char) * 100, "\U0001F940 Your foods are turning rotten!                                                       ");
        }


        refresh();
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
    
}

int near_deamon(player me){
    for(int i = 0 ; i < 8 ; i++){
        int X = me.pos.x + x_moves[i];
        int Y = me.pos.y + y_moves[i];
        char there = mvinch(X , Y) & A_CHARTEXT ;
        if (there == 'D'){
            return 1;
        }
    }
    return 0;
}

int near_fire_breathing_monster(player me){
    for(int i = 0 ; i < 8 ; i++){
        int X = me.pos.x + x_moves[i];
        int Y = me.pos.y + y_moves[i];
        char there = mvinch(X , Y) & A_CHARTEXT ;
        if (there == 'F'){
            return 1;
        }
    }
    return 0;
}

int near_giant(room* rooms_this_level , int n_rooms , player me){ // no Giant in room index 0 (black gold in room index 0)
    for(int i = 0 ; i < 8 ; i++){
        int X = me.pos.x + x_moves[i];
        int Y = me.pos.y + y_moves[i];
        char there = mvinch(X , Y) & A_CHARTEXT ;
        if (there == 'G' && in_which_room(rooms_this_level , n_rooms , me) != 0){
            return 1;
        }
    }
    return 0;
}

int near_snake(player me){
    for(int i = 0 ; i < 8 ; i++){
        int X = me.pos.x + x_moves[i];
        int Y = me.pos.y + y_moves[i];
        char there = mvinch(X , Y) & A_CHARTEXT ;
        if (there == 'S'){
            return 1;
        }
    }
    return 0;
}

int near_undeed(player me){
    for(int i = 0 ; i < 8 ; i++){
        int X = me.pos.x + x_moves[i];
        int Y = me.pos.y + y_moves[i];
        char there = mvinch(X , Y) & A_CHARTEXT ;
        if (there == 'U'){
            return 1;
        }
    }
    return 0;
}

//////////////////////////////SAVE GAME

void save_data(player me, room **rooms_of_all_levels, int n_rooms[4], position **corridors_of_all_levels, int corr_count[4], int level_count , int diff , int song) {
    char filename[150];
    sprintf(filename, "/home/arvin_rsl/Desktop/FOP_Project/Users_Folder/%s/saved_game.txt", me.username);

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Save player data
    fprintf(file, "# Player\n");
    fprintf(file, "won: %d\n", me.won);
    fprintf(file, "Gold: %d\n", me.gold_count);
    fprintf(file, "Health: %d\n", me.health);
    fprintf(file, "Normal Food: %d\n", me.food_count);
    fprintf(file, "Ideal Food: %d\n", me.food[1]);
    fprintf(file, "Magical Food: %d\n", me.food[2]);
    fprintf(file, "Rotten Food: %d\n", me.food[3]);
    for (int i = 0; i < 5; i++) {
        fprintf(file, "%s: %d\n", i == 0 ? "Mace" : i == 1 ? "Dagger" : i == 2 ? "Magic Wand" : i == 3 ? "Normal Arrow" : "Sword", me.weapons[i]);
    }
    fprintf(file, "Spell Health: %d\n", me.spells[0]);
    fprintf(file, "Spell Speed: %d\n", me.spells[1]);
    fprintf(file, "Spell Damage: %d\n", me.spells[2]);
    fprintf(file, "X: %d\n", me.pos.x);
    fprintf(file, "Y: %d\n", me.pos.y);
    // Assuming Floor Level, Difficulty, Color, and Song are part of player structure
    fprintf(file, "Floor Level: %d\n", me.floor_level); // Example logic
    fprintf(file, "Difficulty: %d\n", diff); // Example logic
    fprintf(file, "Color: %d\n", me.color);
    fprintf(file, "Song: %d\n", song); // Example logic

    // Save rooms and corridors data
    fprintf(file, "\n# Rooms\n");
    fprintf(file, "F1 Room Count: %d\n" , n_rooms[0]);
    fprintf(file, "F2 Room Count: %d\n" , n_rooms[1]);
    fprintf(file, "F3 Room Count: %d\n" , n_rooms[2]);
    fprintf(file, "F4 Room Count: %d\n" , n_rooms[3]);
    for (int i = 0; i < level_count; i++) {
        fprintf(file, "\nLevel Num: %d\n", i + 1);

        for (int j = 0; j < n_rooms[i]; j++) {
            room r = rooms_of_all_levels[i][j];
            fprintf(file, "\nRoom Number: %d\n", r.room_number);
            fprintf(file, "Length: %d\n", r.length);
            fprintf(file, "Width: %d\n", r.width);
            fprintf(file, "Hide: %d\n", r.hide);
            fprintf(file, "corner.x: %d\n", r.corner.x);
            fprintf(file, "corner.y: %d\n", r.corner.y);
            fprintf(file, "Type: %d\n", r.type);
            if(r.room_number == 1){
                fprintf(file, "door0.x: %d\n", r.doors_x[0]);
                fprintf(file, "door0.y: %d\n", r.doors_y[0]);
            }
            else{
                fprintf(file, "door0.x: %d\n", r.doors_x[0]);
                fprintf(file, "door1.x: %d\n", r.doors_x[1]);
                fprintf(file, "door0.y: %d\n", r.doors_y[0]);
                fprintf(file, "door1.y: %d\n", r.doors_y[1]);
            }

            fprintf(file, "pillar0.x: %d\n", r.pillars_x[0]);
            fprintf(file, "pillar1.x: %d\n", r.pillars_x[1]);
            fprintf(file, "pillar2.x: %d\n", r.pillars_x[2]);
            fprintf(file, "pillar0.y: %d\n", r.pillars_y[0]);
            fprintf(file, "pillar1.y: %d\n", r.pillars_y[1]);
            fprintf(file, "pillar2.y: %d\n", r.pillars_y[2]);
            fprintf(file, "n_foods: %d\n", r.n_foods);
            for (int k = 0; k < r.n_foods; k++) {
                fprintf(file, "food%d.x: %d\n", k, r.foods_x[k]);
                fprintf(file, "food%d.y: %d\n", k, r.foods_y[k]);
                fprintf(file, "picked_foods%d: %d\n", k, r.picked_foods[k]);
            }
            fprintf(file, "n_golds: %d\n", r.n_golds);
            for (int k = 0; k < r.n_golds; k++) {
                fprintf(file, "gold%d.x: %d\n", k, r.golds_x[k]);
                fprintf(file, "gold%d.y: %d\n", k, r.golds_y[k]);
                fprintf(file, "picked_golds%d: %d\n", k, r.picked_golds[k]);
            }
            fprintf(file, "trap_visibility: %d\n", r.trap_visibility);
            fprintf(file, "trap.x: %d\n", r.trap_x);
            fprintf(file, "trap.y: %d\n", r.trap_y);
            fprintf(file, "stair_x: %d\n", r.stair_x);
            fprintf(file, "stair_y: %d\n", r.stair_y);
            fprintf(file, "black_gold: %d\n", r.black_gold);
            fprintf(file, "black_gold_x: %d\n", r.black_gold_x);
            fprintf(file, "black_gold_y: %d\n", r.black_gold_y);
            for (int k = 0; k < 5; k++) {
                fprintf(file, "weapons%d: %d\n", k, r.weapons[k]);
                fprintf(file, "weapons_x%d: %d\n", k, r.weapons_x[k]);
                fprintf(file, "weapons_y%d: %d\n", k, r.weapons_y[k]);
            }
            for (int k = 0; k < 3; k++) {
                fprintf(file, "spells%d: %d\n", k, r.spells[k]);
                fprintf(file, "spells_x%d: %d\n", k, r.spells_x[k]);
                fprintf(file, "spells_y%d: %d\n", k, r.spells_y[k]);
            }
        }

    }
        
    fprintf(file, "\n# Corridors\n");
    fprintf(file, "F1 Corr Count: %d\n" , corr_count[0]);
    fprintf(file, "F2 Corr Count: %d\n" , corr_count[1]);
    fprintf(file, "F3 Corr Count: %d\n" , corr_count[2]);
    fprintf(file, "F4 Corr Count: %d\n" , corr_count[3]);
    for (int i = 0; i < level_count; i++) {
        fprintf(file, "\nLevel Num: %d\n", i + 1);
        for (int j = 0; j < corr_count[i]; j++) {
            fprintf(file, "(%d,%d)\n", corridors_of_all_levels[i][j].x, corridors_of_all_levels[i][j].y);
        }
    }
    fclose(file);
}

void Pause(room ** rooms_all_levels , position ** corridors_all_levels , player HERO , int* n_rooms , int* corr_count , int diff , int song){
    initscr();
    start_color();
    // init_pair(1, COLOR_WHITE, COLOR_BLACK);
    bkgd(COLOR_PAIR(1));
    keypad(stdscr, TRUE); 
    curs_set(0); 
    int highlight = 1;
    int choice = 0;
    int c;
    char *choices[] = {"Continue Game", "Save Game & Exit" , "Exit Without Saving"}; 

    while (1){
        draw_borders(10);
        print_menu(highlight , choices , 3 , 11 ,"Game Paused");
        c = getch();
        switch(c){
            case KEY_UP:
                if (highlight == 1){
                    highlight = 3;
                    break;
                }
                else if(highlight == 2){
                    highlight--;
                    break;
                }
                else if(highlight == 3){
                    highlight--;
                    break;
                }
            case KEY_DOWN:
                if (highlight == 3){
                    highlight = 1;
                    break;
                }
                else if(highlight == 2){
                    highlight++;
                    break;
                }
                else if(highlight == 1){
                    highlight++;
                    break;
                }
            case 10: // ENTER key
                choice = highlight;
                break;
            default:
                break;
        }

        if (choice != 0){
            break;
        }

    }

    if (choice == 1){
        clear();
    }
    else if (choice == 2){
        clear();
        save_data(HERO , rooms_all_levels , n_rooms , corridors_all_levels , corr_count , 4 , diff , song);
        attron(COLOR_PAIR(3) |A_BOLD);
        // draw_borders(12);
        mvprintw (LINES/2 -1, (COLS - strlen("Game successfully saved!")) /2 , "Game successfully saved!");
        mvprintw (LINES/2 +1 , (COLS - strlen("Going back to pregame menu ... ")) /2 , "Going back to pregame menu ... ");
        refresh();
        sleep(2);
        attroff(COLOR_PAIR(3)|A_BOLD);

        stop_soundtrack();
        for (int i = 0; i < 4; i++) {
            free(corridors_all_levels[i]);
        }
        free(corridors_all_levels);

        // Free memory for rooms
        for (int i = 0; i < 4; i++) {
            free(rooms_all_levels[i]);
        }
        free(rooms_all_levels);
        pregame_menu(HERO.username);
    }



    else if (choice == 3){
        clear();
        initscr();
        int WHAT = 'q';
        while(1){
            attron(A_BOLD);
            mvprintw(LINES / 2, COLS / 2 - strlen("Are you sure? (game won't be saved)")/2 , "Are you sure? (game won't be saved)");
            mvprintw(LINES / 2 + 2, COLS / 2 - strlen("Press Q to go back")/2 , "Press Q to go back");
            mvprintw(LINES / 2 + 4, COLS / 2 - strlen("Press E to Exit")/2 , "Press E to Exit");
            attroff(A_BOLD);
            refresh();
            int WHAT = getch();
            if (WHAT == 'Q' || WHAT == 'q'){
                clear();
                break;
                // pause(rooms_all_levels , corridors_all_levels , HERO);
            }
            else if (WHAT == 'E'|| WHAT == 'e'){
                stop_soundtrack();
                for (int i = 0; i < 4; i++) {
                    free(corridors_all_levels[i]);
                }
                free(corridors_all_levels);

                // Free memory for rooms
                for (int i = 0; i < 4; i++) {
                    free(rooms_all_levels[i]);
                }
                free(rooms_all_levels);
                pregame_menu(HERO.username);
                break;
            }

        }

    }
    
    endwin(); 
}


// function to check if the username already exists
    // returns 0 if username is new
int already_a_username(const char* username){
    FILE * users_fptr = fopen(Usernames_File , "r");
    
    if (users_fptr == NULL){
        printf("username-file not found\n");
        return 0;
    }

    char saved_username[MAX_SIZE];
    // loop over all usernames
    while (fscanf(users_fptr, "%s\n", saved_username) == 1){
        // if the username is already a saved username
        if (strcmp(saved_username, username) == 0){
            fclose(users_fptr);
            return 1;
        }
    }
    // else
    fclose(users_fptr);
    return 0;
}
// checked :)

// function to append the new username to "Usernames_File"
void append_username(const char* new_username){
    FILE * users_fptr = fopen(Usernames_File , "a");
    fprintf(users_fptr , "%s\n" , new_username);
    fclose(users_fptr);
}
// checked :)

// function to create new directory with name = username
void make_user_directory(const char* username){
    char path[] = "/home/arvin_rsl/Desktop/FOP_Project/Users_Folder/";
    strcat(path , username);
    mkdir(path , 0777);
}
// checked :)

// function to create a file named "user_data.txt" in user's folder
void create_user_data_file(const char* username, const char* email, const char* password){

    char path[1024];

    time_t current_time = time(NULL);

    snprintf(path, sizeof(path), "/home/arvin_rsl/Desktop/FOP_Project/Users_Folder/%s/user_data.txt", username);

    FILE *user_data_fptr = fopen(path, "w");

    fprintf(user_data_fptr, "username: %s\nemail: %s\npassword: %s\ntime: %lld\n", username, email, password , (long long)current_time);

    fclose(user_data_fptr);
}

// function to check if password is valid
    // returns 0 if password is invalid 
int is_pass_valid(const char* password){
    int length_pass = strlen(password);
    if(length_pass < 7){
        return 0;
    }
        
    // here we use <ctype.h>'s islower() and isupper() and isdigit()
    // to check if a character is lowercase/uppercase/digit

    int lower_exists = 0 , upper_exists = 0 , digit_exists = 0;

    for (int i = 0 ; i < length_pass ; i++){

        // checking if any lowercase exists inn password
        if (islower(password[i])){
            lower_exists = 1;
        }

        // checking if any uppercase exists inn password
        if (isupper(password[i])){
            upper_exists = 1;
        }

        // checking if any number exists inn password
        if (isdigit(password[i])){
            digit_exists = 1;
        }

    }

    int is_valid = 0;
    if (lower_exists && upper_exists && digit_exists){
        is_valid = 1;
    }

    return is_valid;
}
// checked :)

// function to check if email is valid
    // returns 0 if email is invalid 
int is_email_valid(const char* email){

    /* here we use the 
    char* strchr(const char *string , int c)  function
    where c is the specific character we search for in the string.
    It returns the pointer to the first occurrence of the character,
    or NULL if it doesn't exist in the string.
    */

    /* invalid emails:
        x.@y.z   or  x.@y
        x@.y.z   or  x@.y
        x.y      or  x@y  or  x
        x@y@z    ... (multiple at_signs)
        x@y.     or  x.
        @x       or  @x.y
        x..y@z.w or  x@y..z (consecutive dots)
    */

    // the first '@' in email
    const char* at_sign = strchr(email , '@');

    // no '@' ?
    if (!at_sign){
        return 0;
    }

    // multiple '@' ?
    const char* second_at_sign = strchr(at_sign + 1 , '@');
    if (second_at_sign){
        return 0;
    }

    // the first '.' after '@' 
    const char* dot = strchr(at_sign + 1 , '.');

    // no '.' found after '@' ? 
    if (!dot){
        return 0;
    }

    // is a '.' sticking to '@' ? 
    if (*(at_sign - 1) == '.' || *(at_sign + 1) == '.'){
        return 0;
    }

    // does email begin with '@' ?  or  end with '@' ?
    if (at_sign == email || email[strlen(email) - 1] == '@'){
        return 0;
    }

    // email ends with '.' ?
    if (email[strlen(email) - 1] == '.'){
        return 0;
    }

    // email starts with '.' ?
    if (email[0] == '.'){
        return 0;
    }

    // consecutive dots anywhere in the email ?
    for (const char* p = email; *(p + 1) != '\0'; ++p){
        if (*p == '.' && *(p + 1) == '.'){
            return 0;
        }
    }

    return 1;
}
// checked :)

// function to generate a random password (with 12 characters)
void generate_pass(char* buffer){
    char all[] = "0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890123456789";
    char lowercase[] = "abcdefghijklmnopqrstuvwxyz";
    char uppercase[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char numbers[] = "0123456789";

    // https://mathbits.com/MathBits/CompSci/LibraryFunc/rand.htm
    srand(time(NULL));

    // at least one character of each type
    buffer[0] = lowercase[rand() % strlen(numbers)];
    buffer[1] = uppercase[rand() % strlen(uppercase)];
    buffer[2] = numbers[rand() % strlen(lowercase)];


    // filling the rest of the password with random characters
    for (size_t i = 3; i < 12; i++) {
        buffer[i] = all[rand() % strlen(all)];
    }

    buffer[12] = '\0';

    // shuffle the password (randomize even more)
    for (size_t i = 0; i < 12; i++){
        size_t j = rand() % (12);
        char temp = buffer[i];
        buffer[i] = buffer[j];
        buffer[j] = temp;
    }
}
// checked :)

// function to create a new user
void create_user(int* ptr_difficulty , int* ptr_color , int* ptr_song ){
    char username[MAX_SIZE], password[MAX_SIZE], email[MAX_SIZE];
    int valid_user = 0, valid_pass = 0, valid_email = 0;

    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    bkgd(COLOR_PAIR(1));

    while (1){
        clear();
        draw_title("New User");
        draw_borders(11);
        mvprintw(LINES / 2 - 3, COLS / 2 - 10, "Enter Username: ");
        echo();
        getstr(username);
        noecho();
        if (already_a_username(username)){
            mvprintw(LINES / 2 - 1, COLS / 2 - 20, "Username already exists! Enter another username ");
            refresh();
            getch();
        } 
        else{
            valid_user = 1;
            break;
        }
    }

    while (1){
        clear();
        draw_title("New User");
        draw_borders(11);
        mvprintw(LINES / 2 - 3, COLS / 2 - 10, "Enter Username: ");
        mvprintw(LINES / 2 - 3, COLS / 2 + 5, "  %s" , username);
        mvprintw(LINES / 2 - 1, COLS / 2 - 10, "Enter email: ");
        echo();
        getstr(email);
        noecho();
        if (is_email_valid(email)){
            valid_email = 1;
            break;
        } 
        else{
            mvprintw(LINES / 2 + 1, COLS / 2 - 15, "Invalid email format! Try again");
            refresh();
            getch();
        }
    }

    clear();
    draw_borders(11);
    mvprintw(LINES / 2 - 3, COLS / 2 - 10, "Enter Username: ");
    mvprintw(LINES / 2 - 3, COLS / 2 + 5, "  %s" , username);
    mvprintw(LINES / 2 - 1, COLS / 2 - 10, "Enter email: ");
    mvprintw(LINES / 2 - 1, COLS / 2 + 5, "  %s" , email);
    mvprintw(LINES / 2 + 1, COLS / 2 - 20, "Do you want a randomly generated password? (y/n)");
    int yes_no = getch();

    while (yes_no != 'Y' && yes_no != 'y' && yes_no != 'N' && yes_no != 'n') {
        mvprintw(LINES / 2 + 3, COLS / 2 - 15, "Please enter either 'y' or 'n' :");
        yes_no = getch();
    }

    if (yes_no == 'Y' || yes_no == 'y') {
        valid_pass = 1;
        char random_pass[MAX_SIZE];
        generate_pass(random_pass);
        strcpy(password, random_pass);
        mvprintw(LINES / 2 + 5, COLS / 2 - 10, "Your password is: %s", password);
        refresh();
        getch();
    } 
    else{
        while (1){
            clear();
            draw_borders(11);
            mvprintw(LINES / 2 - 3, COLS / 2 - 10, "Enter Username: ");
            mvprintw(LINES / 2 - 3, COLS / 2 + 5, "  %s" , username);
            mvprintw(LINES / 2 - 1, COLS / 2 - 10, "Enter email: ");
            mvprintw(LINES / 2 - 1, COLS / 2 + 5, "  %s" , email);
            mvprintw(LINES / 2 + 1, COLS / 2 - 10, "Enter your password: ");
            echo();
            getstr(password);
            noecho();
            if (is_pass_valid(password)) {
                valid_pass = 1;
                break;
            } else {
                mvprintw(LINES / 2 + 3, COLS / 2 - 20, "Invalid Password!");
                mvprintw(LINES / 2 + 5, COLS / 2 - 20, "Your password must satisfy these conditions:");
                mvprintw(LINES / 2 + 6, COLS / 2 - 20, "- Have at least 7 characters");
                mvprintw(LINES / 2 + 7, COLS / 2 - 20, "- Include at least one lowercase English letter");
                mvprintw(LINES / 2 + 8, COLS / 2 - 20, "- Include at least one uppercase English letter");
                mvprintw(LINES / 2 + 9, COLS / 2 - 20, "- Include at least one number");
                refresh();
                getch();
            }
        }
    }

    if (valid_user && valid_pass && valid_email) {
        clear();
        draw_borders(12);
        mvprintw(LINES / 2, COLS / 2 - 15, "New user successfully created!");
        mvprintw(LINES / 2 + 2, COLS / 2 - 15, "Press any key to proceed");
        append_username(username);
        make_user_directory(username);
        create_user_data_file(username, email, password);
        refresh();
        getch();
        pregame_menu(username , ptr_difficulty , ptr_color , ptr_song);
    }
    endwin();
}
// checked :)


// player entered the treasure room!
void win(int* ptr_current_song , player* hero){
    hero->gold_count += 100;
    stop_soundtrack();
    init_audio();
    *ptr_current_song = 6;
    choose_soundtrack(*ptr_current_song);
    attron(A_BOLD | COLOR_PAIR(15) );
    mvprintw(0 , COLS/2 - strlen("YOU WON THE GAME !")/2 , "YOU WON THE GAME !");
    attroff(A_BOLD | COLOR_PAIR(15));
    attron(COLOR_PAIR(16));
    if(strcmp( hero->username , "GUEST") != 0 ){
        mvprintw(2 , COLS/2 - strlen("Congratulations! You've conquered the dungeon and emerged victorious!")/2 , "Congratulations! You've conquered the dungeon and emerged victorious!");
        mvprintw(3 , COLS/2 - strlen("\U0001F6E1 Your game has been saved. Press Q to exit.")/2 , "\U0001F6E1 Your game has been saved. Press Q to exit.");
    
    }
    else{
        mvprintw(2 , COLS/2 - strlen("Congratulations! You've conquered the dungeon and emerged victorious!")/2 , "Congratulations! You've conquered the dungeon and emerged victorious!");
        mvprintw(3 , COLS/2 - strlen("\U00002694 What a shame, the game you won is not saved as you are playing as a guest. Press Q to exit.")/2 , "\U00002694 What a shame, the game you won is not saved as you are playing as a guest. Press Q to exit.");
    }
    attroff(COLOR_PAIR(16));
}

// player's health = 0
void death(){
    // init_color(161 , 161 , COLOR_BLACK);
    init_pair(246 , 246 , COLOR_BLACK);
    stop_soundtrack();
    attron(A_BOLD | COLOR_PAIR(160) );
    mvprintw(0 , COLS/2 - strlen("GAME OVER !")/2 , "GAME OVER !");
    attroff(A_BOLD | COLOR_PAIR(160));
    attron(COLOR_PAIR(246));
    mvprintw(2 , COLS/2 - strlen("You fought bravely, but your journey ends here.")/2 , "You fought bravely, but your journey ends here.");
    mvprintw(3 , COLS/2 - strlen("Maybe next time the odds will be in your favor... Press Q to exit.")/2 , "Maybe next time the odds will be in your favor... Press Q to exit.");
    attroff(COLOR_PAIR(246));   
}

// fell in trap 
void trap(player* hero , char* address_global_message){
    hero->health --;
    // attron(COLOR_PAIR(1));
    snprintf(address_global_message, sizeof(char) * 100, "You fell in trap!                             ");
    // sleep(2);
    // attroff(COLOR_PAIR(1));
}

// returns the index of the room in which player is standing
int in_which_room(room* rooms_this_level , int n_rooms , player hero){
    // if ((mvinch(hero.pos.x , hero.pos.y-1) & A_CHARTEXT) == '.' || (mvinch(hero.pos.x , hero.pos.y-1) & A_CHARTEXT) == ',' ||
    //     (mvinch(hero.pos.x , hero.pos.y-1) & A_CHARTEXT) == '~' || (mvinch(hero.pos.x , hero.pos.y-1) & A_CHARTEXT) == '-' ||
    //     (mvinch(hero.pos.x , hero.pos.y-1) & A_CHARTEXT) == '_' || (mvinch(hero.pos.x , hero.pos.y-1) & A_CHARTEXT) == '|' ||
    //     (mvinch(hero.pos.x , hero.pos.y-1) & A_CHARTEXT) == '+' || (mvinch(hero.pos.x , hero.pos.y-1) & A_CHARTEXT) == 'O' || 
    //     (mvinch(hero.pos.x , hero.pos.y-1) & A_CHARTEXT) == 'f' || (mvinch(hero.pos.x , hero.pos.y-1) & A_CHARTEXT) == 'g' ||
    //     (mvinch(hero.pos.x , hero.pos.y-1) & A_CHARTEXT) == 'm' || (mvinch(hero.pos.x , hero.pos.y-1) & A_CHARTEXT) == 'd' ||
    //     (mvinch(hero.pos.x , hero.pos.y-1) & A_CHARTEXT) == 'w' || (mvinch(hero.pos.x , hero.pos.y-1) & A_CHARTEXT) == 'a' ||
    //     (mvinch(hero.pos.x , hero.pos.y-1) & A_CHARTEXT) == 's' || (mvinch(hero.pos.x , hero.pos.y-1) & A_CHARTEXT) == '^' ||
    //     (mvinch(hero.pos.x , hero.pos.y-1) & A_CHARTEXT) == '<' || (mvinch(hero.pos.x , hero.pos.y-1) & A_CHARTEXT) == 'H' ||
    //     (mvinch(hero.pos.x , hero.pos.y-1) & A_CHARTEXT) == '!' || (mvinch(hero.pos.x , hero.pos.y-1) & A_CHARTEXT) == '$'){
    // if ((mvinch(hero.pos.x , hero.pos.y-1) & A_CHARTEXT) != ' ' && (mvinch(hero.pos.x , hero.pos.y-1) & A_CHARTEXT) != '#'){
        int this_room = 0;
        for (int i = 0 ; i < n_rooms ; i++){
            room r = rooms_this_level[i];
            if( (hero.pos.x >= r.corner.x -1 && hero.pos.x <= r.corner.x + r.length) && (hero.pos.y >= r.corner.y -1 && hero.pos.y <= r.corner.y + r.width) ){
                this_room = r.room_number;
                mvprintw(LINES - 1 , 3  , "You are in room number %d" , this_room);
                // sleep(2);
                refresh();
                return this_room - 1;
            }
        }
    // }
    // else{
    //     return - 1;
    // }
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
    for (int i = 0 ; i < R.n_golds ; i++){
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
    if (there == '.'  || there == ',' || there == '-' || there == '~' || there == '#' || there == '+' || there == '^' || there == '<'){
        return 1;
    }
    else if(there == 'H' || there == '$' || there == '!' || there == 'f' || there == 'G'|| there == 'g'|| there == 'm'|| there == 'd'|| there == 'w'|| there == 'a'|| there == 's' ){
        return 2;
    }
    return 0;
}
// checked


// technically just a switch/case that changes the players position (if valid) .  
void movement2(int PiCk , int ch , player* hero , room** rooms_of_all_levels , int n_rooms_this_level , char* address_global_message, int* ptr_level_num , int speed){

    keypad(stdscr, TRUE);
    position current;
    current.x = hero->pos.x;
    current.y = hero->pos.y;
    int x_new;
    int y_new;
    char ccc;
    int room_num = -1;

    switch (ch) {
        // Up and Down for stairs: (room num here means index)
        case KEY_UP:
            room_num = in_which_room(*(rooms_of_all_levels + *ptr_level_num - 1), n_rooms_this_level, *hero);
            if (3 == room_num && hero->pos.x == (*(rooms_of_all_levels + *ptr_level_num - 1))[3].corner.x + 1 && hero->pos.y == (*(rooms_of_all_levels + *ptr_level_num - 1))[3].corner.y + 1){
                if(*ptr_level_num != 4){
                    snprintf(address_global_message, sizeof(char) * 100, "Going Upstairs ...                               ");
                    // sleep(1);
                    (*ptr_level_num)++;
                    hero->pos.x = rooms_of_all_levels[*ptr_level_num - 1][3].stair_x;
                    hero->pos.y = rooms_of_all_levels[*ptr_level_num - 1][3].stair_y;
                    hero->floor_level++;
                    clear();
                    refresh();
                }
                else{
                    snprintf(address_global_message, sizeof(char) * 100, "You have already reached the top level!                        ");
                }
            }
            break;
        case KEY_DOWN:
            room_num = in_which_room(*(rooms_of_all_levels + *ptr_level_num - 1), n_rooms_this_level, *hero);
            if ( 3 == room_num && hero->pos.x == (*(rooms_of_all_levels + *ptr_level_num - 1))[3].corner.x + 1 && hero->pos.y == (*(rooms_of_all_levels + *ptr_level_num - 1))[3].corner.y + 1){
                if (*ptr_level_num != 1){
                    snprintf(address_global_message, sizeof(char) * 100, "Going Downstairs ...                                     ");
                    // sleep(1);
                    (*ptr_level_num)--;
                    hero->pos.x = rooms_of_all_levels[*ptr_level_num - 1][3].stair_x;
                    hero->pos.y = rooms_of_all_levels[*ptr_level_num - 1][3].stair_y;
                    hero->floor_level--;
                    clear();
                    refresh();
                }
                else{
                    snprintf(address_global_message, sizeof(char) * 100, "You are at the bottom level!                            ");
                }
            }
            break;
        // movement
        case '8': // Up
        case 'J':
        case 'j':
            if (valid_move(current.x + speed*x_moves[0] , current.y + speed*y_moves[0])){
                x_new = current.x + speed*x_moves[0];
                y_new = current.y + speed*y_moves[0];
                }
            else{
                x_new = current.x + x_moves[0];
                y_new = current.y + y_moves[0];
            }
            ccc = mvinch(x_new, y_new) & A_CHARTEXT;
            room_num = in_which_room(*(rooms_of_all_levels + *ptr_level_num - 1), n_rooms_this_level, *hero);

            // trap
            if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->trap_x){
                if(x_new == (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->trap_x && y_new == (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->trap_y){
                    (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->trap_visibility = 1;
                    trap(hero, address_global_message);
                    // clear(); // for message
                }
            }
            // food
            if (ccc == 'f' && room_num >= 0){
                if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                    // not nightmare room
                    hero->food_count++;
                    if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->food_types[which_food_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] == 0){
                        // normal food
                        hero->food[0]++;
                    }
                    else if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->food_types[which_food_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] == 1){
                        // normal food
                        hero->food[1]++;
                    }
                    else if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->food_types[which_food_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] == 2){
                        // normal food
                        hero->food[2]++;
                    }
                    else if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->food_types[which_food_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] == 3){
                        // normal food
                        hero->food[3]++;
                    }
                }
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->picked_foods[which_food_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] = 1;
            }

            // gold
            else if (ccc == 'g' && room_num >= 0){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->picked_golds[which_gold_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] = 1;
                if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->picked_golds[which_gold_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] == 1){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->gold_count++;
                        snprintf(address_global_message, sizeof(char) * 100, "+1 Gold!                                                                        ");
                    }
                }
            }
            else if (ccc == 'G' && room_num == 0){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->black_gold = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->black_gold && rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                    hero->gold_count += 15;
                    snprintf(address_global_message, sizeof(char) * 100, "+15 Gold!                                                                        ");
                }
            }
            // mace 
            else if (ccc == 'm' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[0] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[0]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->weapons[0]++;
                        snprintf(address_global_message, sizeof(char) * 100, "Mace added to pack                                                                       ");
                    }
                }
            }
             // dagger 
            else if (ccc == 'd' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[1] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[1]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->weapons[1]+=10;
                        snprintf(address_global_message, sizeof(char) * 100, "10 Daggers added to pack                                                                       ");
                    }
                }
            }
            // wand 
            else if (ccc == 'w' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[2] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[2]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->weapons[2]+=8;
                        snprintf(address_global_message, sizeof(char) * 100, "8 Magic Wands added to pack                                                                       ");
                    }
                }
            }
            // arrow 
            else if (ccc == 'a' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[3] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[3]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->weapons[3]+=20;
                        snprintf(address_global_message, sizeof(char) * 100, "20 Normal Arrows added to pack                                                                       ");
                    }
                }
            }
            // sword 
            else if (ccc == 's' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[4] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[4]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        if(hero->weapons[4] >= 1){
                            snprintf(address_global_message, sizeof(char) * 100, "You already have a sword                                                                      ");
                        }
                        else{
                            hero->weapons[4] = 1;
                            snprintf(address_global_message, sizeof(char) * 100, "Sword added to pack                                                                       ");
                        }
                    }
                }
            }
            
            // Health Spell 
            else if (ccc == 'H' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[0] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[0]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->spells[0]++;
                        snprintf(address_global_message, sizeof(char) * 100, "Health spell added to pack                                                                       ");
                    }
                }
            }
            // Speed Spell 
            else if (ccc == '$' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[1] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[1]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->spells[1]++;
                        snprintf(address_global_message, sizeof(char) * 100, "Speed spell added to pack                                                                       ");
                    }
                }
            }
            // Damage Spell 
            else if (ccc == '!' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[2] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[2]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->spells[2]++;
                        snprintf(address_global_message, sizeof(char) * 100, "Damage spell added to pack                                                                       ");
                    }
                }
            }
            
            // just move
            if (valid_move(x_new, y_new) == 1){
                hero->pos.x = x_new;
                hero->pos.y = y_new;
            } 
            break;

        case '2': // Down
        case 'K':
        case 'k':       
            if (valid_move(current.x + speed*x_moves[1] , current.y + speed*y_moves[1])){
                x_new = current.x + speed*x_moves[1];
                y_new = current.y + speed*y_moves[1];
                }
            else{
                x_new = current.x + x_moves[1];
                y_new = current.y + y_moves[1];
            }
            ccc = mvinch(x_new , y_new) & A_CHARTEXT;
            room_num = in_which_room(*(rooms_of_all_levels + *ptr_level_num - 1), n_rooms_this_level, *hero);
            // trap
            if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->trap_x){
                if(x_new == (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->trap_x && y_new == (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->trap_y){
                    (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->trap_visibility = 1;
                    trap(hero , address_global_message);

                }
            }

            // food
            if (ccc == 'f' && room_num >= 0){
                if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                    // not nightmare room
                    hero->food_count++;
                    if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->food_types[which_food_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] == 0){
                        // normal food
                        hero->food[0]++;
                    }
                    else if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->food_types[which_food_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] == 1){
                        // normal food
                        hero->food[1]++;
                    }
                    else if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->food_types[which_food_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] == 2){
                        // normal food
                        hero->food[2]++;
                    }
                    else if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->food_types[which_food_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] == 3){
                        // normal food
                        hero->food[3]++;
                    }
                }
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->picked_foods[which_food_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] = 1;
            }
            
            else if (ccc == 'g' && room_num >= 0){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->picked_golds[which_gold_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] = 1;
                if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->picked_golds[which_gold_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] == 1){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->gold_count++;
                        snprintf(address_global_message, sizeof(char) * 100, "+1 Gold!                                                                        ");
                    }
                }
            }
            else if (ccc == 'G' && room_num == 0){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->black_gold = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->black_gold && rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                    hero->gold_count += 15;
                    snprintf(address_global_message, sizeof(char) * 100, "+15 Gold!                                                                        ");
                }
            }
            // mace 
            else if (ccc == 'm' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[0] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[0]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->weapons[0]++;
                        snprintf(address_global_message, sizeof(char) * 100, "Mace added to pack                                                                       ");
                    }
                }
            }
            // dagger 
            else if (ccc == 'd' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[1] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[1]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->weapons[1]+=10;
                        snprintf(address_global_message, sizeof(char) * 100, "10 Daggers added to pack                                                                       ");
                    }
                }
            }
            // wand 
            else if (ccc == 'w' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[2] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[2]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->weapons[2]+=8;
                        snprintf(address_global_message, sizeof(char) * 100, "8 Magic Wands added to pack                                                                       ");
                    }
                }
            }
            // arrow 
            else if (ccc == 'a' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[3] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[3]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->weapons[3]+=20;
                        snprintf(address_global_message, sizeof(char) * 100, "20 Normal Arrows added to pack                                                                       ");
                    }
                }
            }
            // sword 
            else if (ccc == 's' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[4] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[4]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        if(hero->weapons[4] >= 1){
                            snprintf(address_global_message, sizeof(char) * 100, "You already have a sword                                                                      ");
                        }
                        else{
                            hero->weapons[4] = 1;
                            snprintf(address_global_message, sizeof(char) * 100, "Sword added to pack                                                                       ");
                        }
                    }
                }
            }
            
            // Health Spell 
            else if (ccc == 'H' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[0] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[0]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->spells[0]++;
                        snprintf(address_global_message, sizeof(char) * 100, "Health spell added to pack                                                                       ");
                    }
                }
            }
            // Speed Spell 
            else if (ccc == '$' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[1] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[1]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->spells[1]++;
                        snprintf(address_global_message, sizeof(char) * 100, "Speed spell added to pack                                                                       ");
                    }
                }
            }
            // Damage Spell 
            else if (ccc == '!' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[2] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[2]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->spells[2]++;
                        snprintf(address_global_message, sizeof(char) * 100, "Damage spell added to pack                                                                       ");
                    }
                }
            }
            
            if (valid_move(x_new , y_new) == 1){
                hero->pos.x = x_new;
                hero->pos.y = y_new;
            } 
            else if(valid_move(x_new , y_new) == 2){
                // pick(ccc , PiCk ,x_new , y_new, hero ,  rooms_of_all_levels, n_rooms_this_level);
            }
            break;

        case '6': // Right
        case KEY_RIGHT:
        case 'L':
        case 'l':
            if (valid_move(current.x + speed*x_moves[1] , current.y + speed*y_moves[2])){
                x_new = current.x + speed*x_moves[2];
                y_new = current.y + speed*y_moves[2];
                }
            else{
                x_new = current.x + x_moves[2];
                y_new = current.y + y_moves[2];
            }
            ccc = mvinch(x_new , y_new) & A_CHARTEXT;
            room_num = in_which_room(*(rooms_of_all_levels + *ptr_level_num - 1), n_rooms_this_level, *hero);
            // trap
            if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->trap_x){
                if(x_new == (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->trap_x && y_new == (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->trap_y){
                    (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->trap_visibility = 1;
                    trap(hero , address_global_message);

                }
            }
            // food
            if (ccc == 'f' && room_num >= 0){
                if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                    // not nightmare room
                    hero->food_count++;
                    if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->food_types[which_food_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] == 0){
                        // normal food
                        hero->food[0]++;
                    }
                    else if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->food_types[which_food_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] == 1){
                        // normal food
                        hero->food[1]++;
                    }
                    else if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->food_types[which_food_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] == 2){
                        // normal food
                        hero->food[2]++;
                    }
                    else if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->food_types[which_food_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] == 3){
                        // normal food
                        hero->food[3]++;
                    }
                }
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->picked_foods[which_food_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] = 1;
            }
            else if (ccc == 'g' && room_num >= 0){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->picked_golds[which_gold_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] = 1;
                if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->picked_golds[which_gold_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] == 1){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->gold_count++;
                        snprintf(address_global_message, sizeof(char) * 100, "+1 Gold!                                                                        ");
                    }    
                }
            }
            else if (ccc == 'G' && room_num == 0){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->black_gold = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->black_gold && rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                    hero->gold_count += 15;
                    snprintf(address_global_message, sizeof(char) * 100, "+15 Gold!                                                                        ");
                }
            }
            // mace 
            else if (ccc == 'm' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[0] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[0]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->weapons[0]++;
                        snprintf(address_global_message, sizeof(char) * 100, "Mace added to pack                                                                       ");
                    }
                }
            }
             // dagger 
            else if (ccc == 'd' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[1] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[1]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->weapons[1]+=10;
                        snprintf(address_global_message, sizeof(char) * 100, "10 Daggers added to pack                                                                       ");
                    }
                }
            }
            // wand 
            else if (ccc == 'w' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[2] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[2]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->weapons[2]+=8;
                        snprintf(address_global_message, sizeof(char) * 100, "8 Magic Wands added to pack                                                                       ");
                    }
                }
            }
            // arrow 
            else if (ccc == 'a' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[3] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[3]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->weapons[3]+=20;
                        snprintf(address_global_message, sizeof(char) * 100, "20 Normal Arrows added to pack                                                                       ");
                    }
                }
            }
            // sword 
            else if (ccc == 's' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[4] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[4]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        if(hero->weapons[4] >= 1){
                            snprintf(address_global_message, sizeof(char) * 100, "You already have a sword                                                                      ");
                        }
                        else{
                            hero->weapons[4] = 1;
                            snprintf(address_global_message, sizeof(char) * 100, "Sword added to pack                                                                       ");
                        }
                    }
                }
            }
            
            // Health Spell 
            else if (ccc == 'H' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[0] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[0]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->spells[0]++;
                        snprintf(address_global_message, sizeof(char) * 100, "Health spell added to pack                                                                       ");
                    }
                }
            }
            // Speed Spell 
            else if (ccc == '$' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[1] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[1]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->spells[1]++;
                        snprintf(address_global_message, sizeof(char) * 100, "Speed spell added to pack                                                                       ");
                    }
                }
            }
            // Damage Spell 
            else if (ccc == '!' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[2] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[2]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->spells[2]++;
                        snprintf(address_global_message, sizeof(char) * 100, "Damage spell added to pack                                                                       ");
                    }
                }
            }
            
            if (valid_move(x_new , y_new) == 1){
                hero->pos.x = x_new;
                hero->pos.y = y_new;
            } 
            else if(valid_move(x_new , y_new) == 2){
                // pick(ccc , PiCk ,x_new , y_new, hero , rooms_of_all_levels, n_rooms_this_level);
            }
            break;
        case '4': // Left
        case KEY_LEFT:
        case 'H':
        case 'h':
            if (valid_move(current.x + speed*x_moves[3] , current.y + speed*y_moves[3])){
                x_new = current.x + speed*x_moves[3];
                y_new = current.y + speed*y_moves[3];
                }
            else{
                x_new = current.x + x_moves[3];
                y_new = current.y + y_moves[3];
            }
            ccc = mvinch(x_new, y_new) & A_CHARTEXT;
            room_num = in_which_room(*(rooms_of_all_levels + *ptr_level_num - 1), n_rooms_this_level, *hero);
            // trap
            if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->trap_x){
                if(x_new == (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->trap_x && y_new == (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->trap_y){
                    (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->trap_visibility = 1;
                    trap(hero, address_global_message);
                }
            }

            // food
            if (ccc == 'f' && room_num >= 0){
                if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                    // not nightmare room
                    hero->food_count++;
                    if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->food_types[which_food_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] == 0){
                        // normal food
                        hero->food[0]++;
                    }
                    else if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->food_types[which_food_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] == 1){
                        // normal food
                        hero->food[1]++;
                    }
                    else if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->food_types[which_food_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] == 2){
                        // normal food
                        hero->food[2]++;
                    }
                    else if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->food_types[which_food_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] == 3){
                        // normal food
                        hero->food[3]++;
                    }
                }
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->picked_foods[which_food_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] = 1;
            }
            else if (ccc == 'g' && room_num >= 0){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->picked_golds[which_gold_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] = 1;
                if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->picked_golds[which_gold_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] == 1){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->gold_count++;
                        snprintf(address_global_message, sizeof(char) * 100, "+1 Gold!                                                                        ");
                    }
                }
            }
            else if (ccc == 'G' && room_num == 0){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->black_gold = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->black_gold && rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                    hero->gold_count += 15;
                    snprintf(address_global_message, sizeof(char) * 100, "+15 Gold!                                                                        ");
                }
            }
            // mace 
            else if (ccc == 'm' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[0] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[0]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->weapons[0]++;
                        snprintf(address_global_message, sizeof(char) * 100, "Mace added to pack                                                                       ");
                    }
                }
            }
             // dagger 
            else if (ccc == 'd' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[1] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[1]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->weapons[1]+=10;
                        snprintf(address_global_message, sizeof(char) * 100, "10 Daggers added to pack                                                                       ");
                    }
                }
            }
            // wand 
            else if (ccc == 'w' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[2] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[2]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->weapons[2]+=8;
                        snprintf(address_global_message, sizeof(char) * 100, "8 Magic Wands added to pack                                                                       ");
                    }
                }
            }
            // arrow 
            else if (ccc == 'a' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[3] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[3]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->weapons[3]+=20;
                        snprintf(address_global_message, sizeof(char) * 100, "20 Normal Arrows added to pack                                                                       ");
                    }
                }
            }
            // sword 
            else if (ccc == 's' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[4] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[4]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        if(hero->weapons[4] >= 1){
                            snprintf(address_global_message, sizeof(char) * 100, "You already have a sword                                                                      ");
                        }
                        else{
                            hero->weapons[4] = 1;
                            snprintf(address_global_message, sizeof(char) * 100, "Sword added to pack                                                                       ");
                        }
                    }
                }
            }
            
            // Health Spell 
            else if (ccc == 'H' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[0] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[0]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->spells[0]++;
                        snprintf(address_global_message, sizeof(char) * 100, "Health spell added to pack                                                                       ");
                    }
                }
            }
            // Speed Spell 
            else if (ccc == '$' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[1] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[1]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->spells[1]++;
                        snprintf(address_global_message, sizeof(char) * 100, "Speed spell added to pack                                                                       ");
                    }
                }
            }
            // Damage Spell 
            else if (ccc == '!' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[2] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[2]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->spells[2]++;
                        snprintf(address_global_message, sizeof(char) * 100, "Damage spell added to pack                                                                       ");
                    }
                }
            }
            
            if (valid_move(x_new, y_new) == 1){
                hero->pos.x = x_new;
                hero->pos.y = y_new;
            } 
            else if(valid_move(x_new, y_new) == 2){
                // pick(ccc , PiCk ,x_new , y_new, hero , rooms_of_all_levels, n_rooms_this_level);
            }
            break;

        case '9': // Upper right
        case 'U':
        case 'u':
            if (valid_move(current.x + speed*x_moves[4] , current.y + speed*y_moves[4])){
                x_new = current.x + speed*x_moves[4];
                y_new = current.y + speed*y_moves[4];
                }
            else{
                x_new = current.x + x_moves[4];
                y_new = current.y + y_moves[4];
            }
            ccc = mvinch(x_new, y_new) & A_CHARTEXT;
            room_num = in_which_room(*(rooms_of_all_levels + *ptr_level_num - 1), n_rooms_this_level, *hero);
            // trap
            if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->trap_x){
                if(x_new == (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->trap_x && y_new == (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->trap_y){
                    (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->trap_visibility = 1;
                    trap(hero , address_global_message);
                }
            }

            // food
            if (ccc == 'f' && room_num >= 0){
                if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                    // not nightmare room
                    hero->food_count++;
                    if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->food_types[which_food_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] == 0){
                        // normal food
                        hero->food[0]++;
                    }
                    else if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->food_types[which_food_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] == 1){
                        // normal food
                        hero->food[1]++;
                    }
                    else if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->food_types[which_food_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] == 2){
                        // normal food
                        hero->food[2]++;
                    }
                    else if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->food_types[which_food_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] == 3){
                        // normal food
                        hero->food[3]++;
                    }
                }
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->picked_foods[which_food_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] = 1;
            }
            else if (ccc == 'g' && room_num >= 0){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->picked_golds[which_gold_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] = 1;
                if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->picked_golds[which_gold_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] == 1){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->gold_count++;
                        snprintf(address_global_message, sizeof(char) * 100, "+1 Gold!                                                                        ");
                    }
                }
            }
            else if (ccc == 'G' && room_num == 0){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->black_gold = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->black_gold && rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                    hero->gold_count += 15;
                    snprintf(address_global_message, sizeof(char) * 100, "+15 Gold!                                                                        ");
                }
            }
            // mace 
            else if (ccc == 'm' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[0] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[0]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->weapons[0]++;
                        snprintf(address_global_message, sizeof(char) * 100, "Mace added to pack                                                                       ");
                    }
                }
            }
             // dagger 
            else if (ccc == 'd' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[1] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[1]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->weapons[1]+=10;
                        snprintf(address_global_message, sizeof(char) * 100, "10 Daggers added to pack                                                                       ");
                    }
                }
            }
            // wand 
            else if (ccc == 'w' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[2] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[2]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->weapons[2]+=8;
                        snprintf(address_global_message, sizeof(char) * 100, "8 Magic Wands added to pack                                                                       ");
                    }
                }
            }
            // arrow 
            else if (ccc == 'a' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[3] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[3]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->weapons[3]+=20;
                        snprintf(address_global_message, sizeof(char) * 100, "20 Normal Arrows added to pack                                                                       ");
                    }
                }
            }
            // sword 
            else if (ccc == 's' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[4] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[4]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        if(hero->weapons[4] >= 1){
                            snprintf(address_global_message, sizeof(char) * 100, "You already have a sword                                                                      ");
                        }
                        else{
                            hero->weapons[4] = 1;
                            snprintf(address_global_message, sizeof(char) * 100, "Sword added to pack                                                                       ");
                        }
                    }
                }
            }
            
            // Health Spell 
            else if (ccc == 'H' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[0] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[0]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->spells[0]++;
                        snprintf(address_global_message, sizeof(char) * 100, "Health spell added to pack                                                                       ");
                    }
                }
            }
            // Speed Spell 
            else if (ccc == '$' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[1] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[1]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->spells[1]++;
                        snprintf(address_global_message, sizeof(char) * 100, "Speed spell added to pack                                                                       ");
                    }
                }
            }
            // Damage Spell 
            else if (ccc == '!' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[2] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[2]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->spells[2]++;
                        snprintf(address_global_message, sizeof(char) * 100, "Damage spell added to pack                                                                       ");
                    }
                }
            }
            
            if (valid_move(x_new, y_new) == 1){
                hero->pos.x = x_new;
                hero->pos.y = y_new;
            } 
            else if(valid_move(x_new, y_new) == 2){
                // pick(ccc , PiCk ,x_new , y_new, hero , rooms_of_all_levels, n_rooms_this_level);
            }
            break;

        case '7': // Upper left
        case 'Y':
        case 'y':
            if (valid_move(current.x + speed*x_moves[5] , current.y + speed*y_moves[5])){
                x_new = current.x + speed*x_moves[5];
                y_new = current.y + speed*y_moves[5];
                }
            else{
                x_new = current.x + x_moves[5];
                y_new = current.y + y_moves[5];
            }
            ccc = mvinch(x_new , y_new) & A_CHARTEXT;
            room_num = in_which_room(*(rooms_of_all_levels + *ptr_level_num - 1), n_rooms_this_level, *hero);
            // trap
            if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->trap_x){
                if(x_new == (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->trap_x && y_new == (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->trap_y){
                    (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->trap_visibility = 1;
                    trap(hero , address_global_message);
                }
            }

            // food
            if (ccc == 'f' && room_num >= 0){
                if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                    // not nightmare room
                    hero->food_count++;
                    if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->food_types[which_food_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] == 0){
                        // normal food
                        hero->food[0]++;
                    }
                    else if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->food_types[which_food_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] == 1){
                        // normal food
                        hero->food[1]++;
                    }
                    else if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->food_types[which_food_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] == 2){
                        // normal food
                        hero->food[2]++;
                    }
                    else if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->food_types[which_food_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] == 3){
                        // normal food
                        hero->food[3]++;
                    }
                }
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->picked_foods[which_food_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] = 1;
            }
            else if (ccc == 'g' && room_num >= 0){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->picked_golds[which_gold_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] = 1;
                if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->picked_golds[which_gold_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] == 1){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->gold_count++;
                        snprintf(address_global_message, sizeof(char) * 100, "+1 Gold!                                                                        ");
                    }
                }
            }
            else if (ccc == 'G' && room_num == 0){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->black_gold = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->black_gold && rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                    hero->gold_count += 15;
                    snprintf(address_global_message, sizeof(char) * 100, "+15 Gold!                                                                        ");
                }
            }
            // mace 
            else if (ccc == 'm' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[0] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[0]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->weapons[0]++;
                        snprintf(address_global_message, sizeof(char) * 100, "Mace added to pack                                                                       ");
                    }
                }
            }
             // dagger 
            else if (ccc == 'd' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[1] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[1]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->weapons[1]+=10;
                        snprintf(address_global_message, sizeof(char) * 100, "10 Daggers added to pack                                                                       ");
                    }
                }
            }
            // wand 
            else if (ccc == 'w' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[2] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[2]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->weapons[2]+=8;
                        snprintf(address_global_message, sizeof(char) * 100, "8 Magic Wands added to pack                                                                       ");
                    }
                }
            }
            // arrow 
            else if (ccc == 'a' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[3] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[3]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->weapons[3]+=20;
                        snprintf(address_global_message, sizeof(char) * 100, "20 Normal Arrows added to pack                                                                       ");
                    }
                }
            }
            // sword 
            else if (ccc == 's' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[4] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[4]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        if(hero->weapons[4] >= 1){
                            snprintf(address_global_message, sizeof(char) * 100, "You already have a sword                                                                      ");
                        }
                        else{
                            hero->weapons[4] = 1;
                            snprintf(address_global_message, sizeof(char) * 100, "Sword added to pack                                                                       ");
                        }
                    }
                }
            }
            
            // Health Spell 
            else if (ccc == 'H' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[0] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[0]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->spells[0]++;
                        snprintf(address_global_message, sizeof(char) * 100, "Health spell added to pack                                                                       ");
                    }
                }
            }
            // Speed Spell 
            else if (ccc == '$' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[1] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[1]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->spells[1]++;
                        snprintf(address_global_message, sizeof(char) * 100, "Speed spell added to pack                                                                       ");
                    }
                }
            }
            // Damage Spell 
            else if (ccc == '!' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[2] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[2]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->spells[2]++;
                        snprintf(address_global_message, sizeof(char) * 100, "Damage spell added to pack                                                                       ");
                    }
                }
            }
            
            if (valid_move(x_new, y_new) == 1){
                hero->pos.x = x_new;
                hero->pos.y = y_new;
            } 
            else if(valid_move(x_new, y_new) == 2){
                // pick(ccc , PiCk ,x_new , y_new, hero , rooms_of_all_levels, n_rooms_this_level);
            }
            break;

        case '1': // Down left
        case 'B':
        case 'b':
            if (valid_move(current.x + speed*x_moves[7] , current.y + speed*y_moves[7])){
                x_new = current.x + speed*x_moves[7];
                y_new = current.y + speed*y_moves[7];
                }
            else{
                x_new = current.x + x_moves[7];
                y_new = current.y + y_moves[7];
            }
            ccc = mvinch(x_new , y_new) & A_CHARTEXT;
            room_num = in_which_room(*(rooms_of_all_levels + *ptr_level_num - 1), n_rooms_this_level, *hero);
            // trap
            if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->trap_x){
                if(x_new == (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->trap_x && y_new == (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->trap_y){
                    (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->trap_visibility = 1;
                    trap(hero , address_global_message);
                }
            }
            // food
            if (ccc == 'f' && room_num >= 0){
                if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                    // not nightmare room
                    hero->food_count++;
                    if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->food_types[which_food_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] == 0){
                        // normal food
                        hero->food[0]++;
                    }
                    else if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->food_types[which_food_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] == 1){
                        // normal food
                        hero->food[1]++;
                    }
                    else if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->food_types[which_food_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] == 2){
                        // normal food
                        hero->food[2]++;
                    }
                    else if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->food_types[which_food_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] == 3){
                        // normal food
                        hero->food[3]++;
                    }
                }
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->picked_foods[which_food_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] = 1;
            }
            else if (ccc == 'g' && room_num >= 0){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->picked_golds[which_gold_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] = 1;
                if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->picked_golds[which_gold_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] == 1){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->gold_count++;
                        snprintf(address_global_message, sizeof(char) * 100, "+1 Gold!                                                                        ");
                    }
                }
            }
            else if (ccc == 'G' && room_num == 0){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->black_gold = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->black_gold && rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                    hero->gold_count += 15;
                    snprintf(address_global_message, sizeof(char) * 100, "+15 Gold!                                                                        ");
                }
            }
            // mace 
            else if (ccc == 'm' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[0] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[0]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->weapons[0]++;
                        snprintf(address_global_message, sizeof(char) * 100, "Mace added to pack                                                                       ");
                    }
                }
            }
            // dagger 
            else if (ccc == 'd' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[1] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[1]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->weapons[1]+=10;
                        snprintf(address_global_message, sizeof(char) * 100, "10 Daggers added to pack                                                                       ");
                    }
                }
            }
            // wand 
            else if (ccc == 'w' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[2] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[2]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->weapons[2]+=8;
                        snprintf(address_global_message, sizeof(char) * 100, "8 Magic Wands added to pack                                                                       ");
                    }
                }
            }
            // arrow 
            else if (ccc == 'a' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[3] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[3]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->weapons[3]+=20;
                        snprintf(address_global_message, sizeof(char) * 100, "20 Normal Arrows added to pack                                                                       ");
                    }
                }
            }
            // sword 
            else if (ccc == 's' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[4] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[4]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        if(hero->weapons[4] >= 1){
                            snprintf(address_global_message, sizeof(char) * 100, "You already have a sword                                                                      ");
                        }
                        else{
                            hero->weapons[4] = 1;
                            snprintf(address_global_message, sizeof(char) * 100, "Sword added to pack                                                                       ");
                        }
                    }
                }
            }
            // Health Spell 
            else if (ccc == 'H' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[0] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[0]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->spells[0]++;
                        snprintf(address_global_message, sizeof(char) * 100, "Health spell added to pack                                                                       ");
                    }
                }
            }
            // Speed Spell 
            else if (ccc == '$' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[1] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[1]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->spells[1]++;
                        snprintf(address_global_message, sizeof(char) * 100, "Speed spell added to pack                                                                       ");
                    }
                }
            }
            // Damage Spell 
            else if (ccc == '!' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[2] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[2]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->spells[2]++;
                        snprintf(address_global_message, sizeof(char) * 100, "Damage spell added to pack                                                                       ");
                    }
                }
            }
            
            if (valid_move(x_new, y_new) == 1){
                hero->pos.x = x_new;
                hero->pos.y = y_new;
            } 
            else if(valid_move(x_new, y_new) == 2){
                // pick(ccc, PiCk, x_new, y_new, hero, rooms_of_all_levels, n_rooms_this_level);
            }
            break;

        case '3': // Down right
        case 'N':
        case 'n':
            if (valid_move(current.x + speed*x_moves[6] , current.y + speed*y_moves[6])){
                x_new = current.x + speed*x_moves[6];
                y_new = current.y + speed*y_moves[6];
                }
            else{
                x_new = current.x + x_moves[6];
                y_new = current.y + y_moves[6];
            }
            ccc = mvinch(x_new, y_new) & A_CHARTEXT;
            room_num = in_which_room(*(rooms_of_all_levels + *ptr_level_num - 1), n_rooms_this_level, *hero);
            // trap
            if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->trap_x){
                if(x_new == (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->trap_x && y_new == (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->trap_y){
                    (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->trap_visibility = 1;
                    trap(hero , address_global_message);
                }
            }

            // food
            if (ccc == 'f' && room_num >= 0){
                if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                    // not nightmare room
                    hero->food_count++;
                    if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->food_types[which_food_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] == 0){
                        // normal food
                        hero->food[0]++;
                    }
                    else if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->food_types[which_food_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] == 1){
                        // normal food
                        hero->food[1]++;
                    }
                    else if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->food_types[which_food_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] == 2){
                        // normal food
                        hero->food[2]++;
                    }
                    else if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->food_types[which_food_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] == 3){
                        // normal food
                        hero->food[3]++;
                    }
                }
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num)->picked_foods[which_food_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] = 1;
            }
            else if (ccc == 'g' && room_num >= 0){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->picked_golds[which_gold_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] = 1;
                if((*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->picked_golds[which_gold_in_room(x_new, y_new , (*(rooms_of_all_levels + *ptr_level_num - 1))[room_num])] == 1){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->gold_count++;
                        snprintf(address_global_message, sizeof(char) * 100, "+1 Gold!                                                                        ");
                    }
                }
            }
            else if (ccc == 'G' && room_num == 0){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->black_gold = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->black_gold && rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                    hero->gold_count += 15;
                    snprintf(address_global_message, sizeof(char) * 100, "+15 Gold!                                                                        ");
                }
            }
            // mace 
            else if (ccc == 'm' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[0] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[0]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->weapons[0]++;
                        snprintf(address_global_message, sizeof(char) * 100, "Mace added to pack                                                                       ");
                    }
                }
            }
            // dagger 
            else if (ccc == 'd' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[1] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[1]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->weapons[1]+=10;
                        snprintf(address_global_message, sizeof(char) * 100, "10 Daggers added to pack                                                                       ");
                    }
                }
            }
            // wand 
            else if (ccc == 'w' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[2] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[2]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->weapons[2]+=8;
                        snprintf(address_global_message, sizeof(char) * 100, "8 Magic Wands added to pack                                                                       ");
                    }
                }
            }
            // arrow 
            else if (ccc == 'a' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[3] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[3]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->weapons[3]+=20;
                        snprintf(address_global_message, sizeof(char) * 100, "20 Normal Arrows added to pack                                                                       ");
                    }
                }
            }
            // sword 
            else if (ccc == 's' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[4] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->weapons[4]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        if(hero->weapons[4] >= 1){
                            snprintf(address_global_message, sizeof(char) * 100, "You already have a sword                                                                      ");
                        }
                        else{
                            hero->weapons[4] = 1;
                            snprintf(address_global_message, sizeof(char) * 100, "Sword added to pack                                                                       ");
                        }
                    }
                }
            }
            
            // Health Spell 
            else if (ccc == 'H' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[0] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[0]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->spells[0]++;
                        snprintf(address_global_message, sizeof(char) * 100, "Health spell added to pack                                                                       ");
                    }
                }
            }
            // Speed Spell 
            else if (ccc == '$' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[1] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[1]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->spells[1]++;
                        snprintf(address_global_message, sizeof(char) * 100, "Speed spell added to pack                                                                       ");
                    }
                }
            }
            // Damage Spell 
            else if (ccc == '!' && room_num >= 0 && hero->pick){
                (*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[2] = 0;
                if(!(*(rooms_of_all_levels + *ptr_level_num - 1) + room_num )->spells[2]){
                    if(rooms_of_all_levels[*ptr_level_num - 1][room_num].type != 4){
                        // not nightmare room
                        hero->spells[2]++;
                        snprintf(address_global_message, sizeof(char) * 100, "Damage spell added to pack                                                                       ");
                    }
                }
            }
            
            if (valid_move(x_new, y_new) == 1){
                hero->pos.x = x_new;
                hero->pos.y = y_new;
            } 
            else if(valid_move(x_new, y_new) == 2){
                // pick(ccc, PiCk, x_new, y_new, hero, rooms_of_all_levels, n_rooms_this_level);
            }
            break;
    }
}


// Function to initialize SDL for audio playback
void init_audio(){
    if (SDL_Init(SDL_INIT_AUDIO) < 0){
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        fprintf(stderr, "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        exit(1);
    }
}

// Function to play a soundtrack
void play_soundtrack(const char *filename){
    Mix_Music *music = Mix_LoadMUS(filename);
    if (music == NULL) {
        fprintf(stderr, "Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
        exit(1);
    }

    if (Mix_PlayMusic(music, -1) < 0){
        fprintf(stderr, "Failed to play music! SDL_mixer Error: %s\n", Mix_GetError());
        exit(1);
    }
}

// Function to stop the soundtrack
void stop_soundtrack(){
    Mix_HaltMusic();
    Mix_CloseAudio();
    SDL_Quit();
}

// Example function where user selects the soundtrack
void choose_soundtrack(int choice){
    char *soundtracks[] = {
                           "/home/arvin_rsl/Desktop/FOP_Project/songs/Firerose-8-bitDungeon.mp3",  // Regular room song1
                           "/home/arvin_rsl/Desktop/FOP_Project/songs/GoleYakh.mp3",  // Regular room song2
                           "/home/arvin_rsl/Desktop/FOP_Project/songs/GTA.mp3",  // Regular room song3
                           "/home/arvin_rsl/Desktop/FOP_Project/songs/DungeonEmperorsTomb-IntoTheCrypt.mp3", // Enchant room 
                           "/home/arvin_rsl/Desktop/FOP_Project/songs/DarkestDungeon.mp3", // Nightmare room
                           "/home/arvin_rsl/Desktop/FOP_Project/songs/FinalFantasy7-VictoryFanfare.mp3"  // Victory song !
    };

    // Play the chosen soundtrack
    if(choice != 0){
        play_soundtrack(soundtracks[choice - 1]);
    }
}

// my LINES is 45 and COLS is 184

// the upper three lines and lower three lines of map are dedicated to messages


// the food list window
void food_list(player* hero){
    int height = 23;
    int width = 52;
    int start_x = (LINES - height) / 2;
    int start_y = (COLS - width) / 2;

    // create a new window for the food screen
    WINDOW *help_win = newwin(height, width, start_x, start_y);

    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    // draw borders around the window
    wattron(help_win, COLOR_PAIR(5));
    box(help_win, 0, 0);
    wattron(help_win, COLOR_PAIR(5));
    init_color(99, 590 , 400 , 800); // for magic food
    init_pair(99, 99 , COLOR_BLACK); // for magic food
    init_color(81, 1000 , 200 , 890); // for ideal food
    init_pair(81, 81 , COLOR_BLACK); // for ideal food

    int title_y = (width - 9) / 2; // length of "FOOD MENU" = 9

    // Print FOOD MENU centered
    wattron(help_win, COLOR_PAIR(8) | A_BOLD);
    mvwprintw(help_win, 1, title_y, "FOOD MENU");
    wattroff(help_win, COLOR_PAIR(8) |A_BOLD);

    char CH = 'n';
    while (CH == 'n' || CH == 'i'|| CH == 'm' || CH == 'N' || CH == 'I' || CH == 'M'){
        mvwprintw(help_win, 12, 1, " To consume food, exit this menu and enter 'C'");
        mvwprintw(help_win, 16, 1, " The current food is bold.");
        mvwprintw(help_win, 18, 1, " To select food type, enter the food's character.");
        mvwprintw(help_win, 20, 1, " Default selected food is Normal.");
        wattron(help_win, COLOR_PAIR(8));
        if(hero->current_food == 0 || hero->current_food == 3) wattron(help_win , A_BOLD);
        mvwprintw(help_win, 3, 1, " Normal Food (N): %d" , hero->food[0] + hero->food[3]); // DOESN'T KNOW ROTTEN OR NOT (yet)
        if(hero->current_food == 0 || hero->current_food == 3) wattroff(help_win , A_BOLD);
        wattroff(help_win, COLOR_PAIR(8));
        wattron(help_win, COLOR_PAIR(81));
        if(hero->current_food == 1) wattron(help_win , A_BOLD);
        mvwprintw(help_win, 5, 1, " Ideal Food (I): %d" , hero->food[1]);
        if(hero->current_food == 1) wattroff(help_win , A_BOLD);
        wattroff(help_win, COLOR_PAIR(81));
        wattron(help_win, COLOR_PAIR(99));
        if(hero->current_food == 2) wattron(help_win , A_BOLD);
        mvwprintw(help_win, 7, 1, " Magical Food (M): %d" , hero->food[2]);
        if(hero->current_food == 2) wattroff(help_win , A_BOLD);
        wattroff(help_win, COLOR_PAIR(99));
        // wattron(help_win, COLOR_PAIR(8));
        // mvwprintw(help_win, 9, 1, " Rotten Food (R): %d" , hero->food[3]);
        // wattroff(help_win, COLOR_PAIR(8));

        CH = wgetch(help_win);

        int norm_is_1_rott_is_0[10] = { 1 , 1 , 1 , 1 , 1 , 1 , 0 , 0 , 0 ,0}; // chances: 60% vs 40%
        int random_norm_or_rott = 1;
        switch (CH)
        {
        case 'n':
        case 'N':

            int n_rott = hero->food[3];
            int n_norm = hero->food[0];
            if (n_norm > 0 && n_rott > 0){
                random_norm_or_rott = norm_is_1_rott_is_0[rand() % 10];
            }
            else if (n_rott <= 0){
                random_norm_or_rott = 1; // norm
            }
            else if (n_norm <= 0){
                random_norm_or_rott = 0; // rott
            }


            if (random_norm_or_rott){
                hero->current_food = 0;
            }
            else{
                hero->current_food = 3;
            }

            break;
        case 'I':
        case 'i':
            hero->current_food = 1;
            break;
        case 'm':
        case 'M':
            hero->current_food = 2;
            break;
        default:
            break;
        }
    }
    
    wrefresh(help_win);

    // wait for user input to close the help screen
    wgetch(help_win);

    // delete the window
    delwin(help_win);
    clear();

}


// the weapon list window
void weapon_list(player* ptr_to_hero){
    int height = 23;
    int width = 55;
    int start_x = (LINES - height) / 2;
    int start_y = (COLS - width) / 2;

    // create a new window for the help screen
    WINDOW *help_win = newwin(height, width, start_x, start_y);

    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    // draw borders around the window
    wattron(help_win, COLOR_PAIR(6));
    box(help_win, 0, 0);
    wattron(help_win, COLOR_PAIR(6));


    int title_y = (width - 11) / 2; // length of "WEAPON MENU" = 11

    // Print WEAPON MENU centered
    wattron(help_win, COLOR_PAIR(160) | A_BOLD);
    mvwprintw(help_win, 1, title_y, "WEAPON MENU");
    wattroff(help_win, COLOR_PAIR(160) | A_BOLD);

    char CH = 'm';
    // CH = wgetch(help_win);
    while (CH == 'm' || CH == 'd'|| CH == 'w'|| CH == 'a' || CH == 's' || CH == 'M' || CH == 'D'|| CH == 'W'|| CH == 'A' || CH == 'S'){
        mvwprintw(help_win, 16, 1, " The current weapon is bold.");
        mvwprintw(help_win, 18, 1, " To select weapon, enter the weapon's character.");
        mvwprintw(help_win, 20, 1, " Default weapon is Mace.");
    
        // print instructions inside the window
        if(ptr_to_hero->current_weapon == 0) wattron(help_win , A_BOLD);
        mvwprintw(help_win, 3, 1, " Mace (m): %d" , ptr_to_hero->weapons[0]);
        if(ptr_to_hero->current_weapon == 0) wattroff(help_win , A_BOLD);

        if(ptr_to_hero->current_weapon == 1) wattron(help_win , A_BOLD);
        mvwprintw(help_win, 5, 1, " Dagger (d): %d" , ptr_to_hero->weapons[1]);
        if(ptr_to_hero->current_weapon == 1) wattroff(help_win , A_BOLD);

        if(ptr_to_hero->current_weapon == 2) wattron(help_win , A_BOLD);
        mvwprintw(help_win, 7, 1, " Magic Wand (w): %d" , ptr_to_hero->weapons[2]);
        if(ptr_to_hero->current_weapon == 2) wattroff(help_win , A_BOLD);

        if(ptr_to_hero->current_weapon == 3) wattron(help_win , A_BOLD);
        mvwprintw(help_win, 9, 1, " Normal Arrow (a): %d" , ptr_to_hero->weapons[3]);
        if(ptr_to_hero->current_weapon == 3) wattroff(help_win , A_BOLD);

        if(ptr_to_hero->current_weapon == 4) wattron( help_win , A_BOLD);
        mvwprintw(help_win, 11, 1, " Sword (s): %d" , ptr_to_hero->weapons[4]);
        if(ptr_to_hero->current_weapon == 4) wattroff( help_win , A_BOLD);
        CH = wgetch(help_win);

        // int whichWeapon = 0;
        // ptr_to_hero->current_weapon = whichWeapon;
        switch (CH)
        {
        case 'm':
        case 'M':
            ptr_to_hero->current_weapon = 0;
            break;
        case 'd':
        case 'D':
            ptr_to_hero->current_weapon = 1;
            break;
        case 'w':
        case 'W':
            ptr_to_hero->current_weapon = 2;
            break;
        case 'a':
        case 'A':
            ptr_to_hero->current_weapon = 3;
            break;
        case 's':
        case 'S':
            ptr_to_hero->current_weapon = 4;
            break;
        
        default:
            break;
        }

        wrefresh(help_win);
    }



    // int CH;
    // CH = wgetch(help_win);
    // while (CH == 'm' || CH == 'd'|| CH == 'w'|| CH == 'a' || CH == 's' || CH == 'M' || CH == 'D'|| CH == 'W'|| CH == 'A' || CH == 'S'){
    //     int whichWeapon = 0;
    //     hero.current_weapon = whichWeapon;
    //     CH = wgetch(help_win);
    // }
    // do {
    //     CH = wgetch(help_win);
    // } while (CH == 'm' || CH == 'd'|| CH == 'w'|| CH == 'a' || CH == 's' || CH == 'M' || CH == 'D'|| CH == 'W'|| CH == 'A' || CH == 'S');

    // delete the window
    delwin(help_win);
    clear();

}


// the weapon list window
void spell_list(player* ptr_to_hero){
    int height = 23;
    int width = 55;
    int start_x = (LINES - height) / 2;
    int start_y = (COLS - width) / 2;

    // create a new window for the help screen
    WINDOW *help_win = newwin(height, width, start_x, start_y);

    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    // draw borders around the window
    wattron(help_win, COLOR_PAIR(4));
    box(help_win, 0, 0);
    wattron(help_win, COLOR_PAIR(4));


    int title_y = (width - 10) / 2; // length of "SPELL MENU" = 10

    // Print SPELL MENU centered
    wattron(help_win, COLOR_PAIR(2) | A_BOLD);
    mvwprintw(help_win, 1, title_y, "SPELL MENU");
    wattroff(help_win, COLOR_PAIR(2) | A_BOLD);

    char CH = 'h';
    while (CH == 'h' || CH == 'd'|| CH == 's' || CH == 'H' || CH == 'D' || CH == 'S'){
        mvwprintw(help_win, 13, 1, " To use spell, exit this menu and enter 'Z'");
        mvwprintw(help_win, 16, 1, " The current spell is bold.");
        mvwprintw(help_win, 18, 1, " To select spell, enter the spell's character.");
        mvwprintw(help_win, 20, 1, " Default selected spell is Health.");
    
        // print instructions inside the window
        if(ptr_to_hero->current_spell == 0) wattron(help_win , A_BOLD);
        mvwprintw(help_win, 4, 1, " Health (h): %d" , ptr_to_hero->spells[0]);
        if(ptr_to_hero->current_spell == 0) wattroff(help_win , A_BOLD);

        if(ptr_to_hero->current_spell == 1) wattron(help_win , A_BOLD);
        mvwprintw(help_win, 6, 1, " Speed (s): %d" , ptr_to_hero->spells[1]);
        if(ptr_to_hero->current_spell == 1) wattroff(help_win , A_BOLD);

        if(ptr_to_hero->current_spell == 2) wattron(help_win , A_BOLD);
        mvwprintw(help_win, 8, 1, " Damage (d): %d" , ptr_to_hero->spells[2]);
        if(ptr_to_hero->current_spell == 2) wattroff(help_win , A_BOLD);
        CH = wgetch(help_win);

        // int whichWeapon = 0;
        // ptr_to_hero->current_weapon = whichWeapon;
        switch (CH)
        {
        case 'h':
        case 'H':
            ptr_to_hero->current_spell = 0;
            break;
        case 'd':
        case 'D':
            ptr_to_hero->current_spell = 2;
            break;
        case 's':
        case 'S':
            ptr_to_hero->current_spell = 1;
            break;
        default:
            break;
        }

        wrefresh(help_win);
    }

    delwin(help_win);
    clear();

}


// print message (top of the map)
void print_top_message(char * message){
    setlocale(LC_ALL, "");
    // HELP
    mvprintw(0 , COLS - 18 - 3 , "Press '/' for help" ); // 18 chars
    mvprintw(0 , 3 , "%s" , message); 
    // usleep(500000);
    // Sleep for 5 seconds without blocking
    // struct timespec req = {5, 0}; // 5 seconds
    // nanosleep(&req, NULL);
}


void print_bottom_message(player* hero , int level_num){

    // int start_col = 0;
    int start_col = (COLS - (14 + 7 + 7 + 16 + 16 + 5 +  4*10) )/ 2;

    // level number
    init_color(93, 697, 1000, 300); // Light green
    init_color(94, 1000, 750, 650);   // Peach
    init_pair(93 , 93 , COLOR_BLACK);
    init_pair(94 , 94 , COLOR_BLACK);
    init_pair(73 , COLOR_CYAN , COLOR_BLACK);
    attron(COLOR_PAIR(73));
    mvprintw(LINES - 1 , start_col , "Floor Level: "); // 13 chars
    attroff(COLOR_PAIR(73));
    mvprintw(LINES - 1 , start_col + 13, "%d" , level_num); // 1 char


    // gold count
    attron(COLOR_PAIR(15));
    mvprintw(LINES - 1 , 10 + start_col + 14 , "Gold: "); // 6 chars
    attroff(COLOR_PAIR(15));
    mvprintw(LINES - 1 , 10 + start_col + 14 + 6 , "%d" , hero->gold_count); // 1 char


    // food count
    // init_pair(75 , COLOR_MAGENTA , COLOR_BLACK);
    attron(COLOR_PAIR(8));
    mvprintw(LINES - 1, 2*10 + start_col + 14 + 7, "Food: " ); // 6 chars
    attroff(COLOR_PAIR(8));
    mvprintw(LINES - 1, 2*10 + start_col + 14 + 7 + 6, "%d" , hero->food_count); // 1 chars


    // health bar (full = 16 , medium = 9 , low = 5)
    if (hero->health > 9){
        init_pair(3 , COLOR_GREEN , COLOR_BLACK);
    }
    else if (5 < hero->health && hero->health <= 9)
    {
        init_pair(3 , COLOR_YELLOW , COLOR_BLACK);
    }
    else if (hero->health <= 5){
        init_pair(3 , COLOR_RED , COLOR_BLACK);
    }
    attron(COLOR_PAIR(93));
    mvprintw(LINES - 1, 3*10 + start_col + 14 + 7 + 7 , "Health: "); // 8 chars
    attron(COLOR_PAIR(93));
    attron(COLOR_PAIR(3));
    for (int i = 0 ; i < 16 ; i++){ // maximum: 16 chars

        if (i < hero->health) {
            mvprintw(LINES - 1, 3*10 + start_col + 14 + 7 + 7 + 8 + i, "\u2665");
        } else {
            mvprintw(LINES - 1, 3*10 + start_col + 14 + 7 + 7 + 8 + i, " ");
        }
        // mvprintw(LINES - 1, 3*10 + start_col + 14 + 7 + 7 + 8 + i, "%c" , '*');
    }
    attroff(COLOR_PAIR(3));
    attron(COLOR_PAIR(94));
    mvprintw(LINES - 1, 4*10 + start_col + 14 + 7 + 7 + 8 + 16, "Hunger: "); // 8 chars
    attroff(COLOR_PAIR(94));
    if (hero->how_full > 3){
        init_pair(99 , COLOR_GREEN , COLOR_BLACK);
    }
    else if (2 < hero->how_full)
    {
        init_pair(99 , COLOR_YELLOW , COLOR_BLACK);
    }
    else if (hero->how_full <= 2){
        init_pair(99 , COLOR_RED , COLOR_BLACK);
    }
    attron(COLOR_PAIR(99));
    for (int i = 0 ; i < 5 ; i++){ // maximum: 5 chars
        if (i < hero->how_full) {
            mvprintw(LINES - 1, 4*10 + start_col + 14 + 7 + 7 + 16 + 16 + i, "\u269C"); /// \U0001F357?
        } else {
            mvprintw(LINES - 1, 4*10 + start_col + 14 + 7 + 7 + 16 + 16 + i, " ");
        }
    }
    attroff(COLOR_PAIR(99));
    
}


// the help screen
void help(player* hero) {
    int height = 30;
    int width = 50;
    int start_x = (LINES - height) / 2;
    int start_y = (COLS - width) / 2;

    // create a new window for the help screen
    WINDOW *help_win = newwin(height, width, start_x, start_y);

    init_pair(6, COLOR_GREEN, COLOR_BLACK);
    // draw borders around the window
    wattron(help_win, COLOR_PAIR(6));
    box(help_win, 0, 0);
    wattron(help_win, COLOR_PAIR(6));

    init_pair(5, COLOR_CYAN, COLOR_BLACK);

    int title_y = (width - 9) / 2; // length of "HELP MENU" = 9

    // Print HELP MENU in cyan color and centered
    wattron(help_win, COLOR_PAIR(5) | A_BOLD);
    mvwprintw(help_win, 1, title_y, "HELP MENU");
    wattroff(help_win, COLOR_PAIR(5) | A_BOLD);
    char CH = 'p';
    while(CH == 'p' || CH == 'P'){
        wattron(help_win, A_BOLD);
        mvwprintw(help_win, 3, 1, " Viewing Foods: F");
        mvwprintw(help_win, 4, 1, " Viewing Weapons: I");
        mvwprintw(help_win, 5, 1, " Viewing Spells: X");
        mvwprintw(help_win, 6, 1, " Temporary Fast Move: V");
        mvwprintw(help_win, 8, 1, " Pick Up option: ");
        wattron(help_win, A_ITALIC);
        if (hero->pick){
            mvwprintw(help_win, 8, 1 + 17, "ON ");
        }
        else{
            mvwprintw(help_win, 8, 1 + 17, "OFF");
        }
        wattroff(help_win, A_ITALIC);

        wattroff(help_win, A_BOLD);
        mvwprintw(help_win, 9, 1, " To turn on/off the Pick Up option, enter 'P'");
        wattron(help_win, A_BOLD);

        int movement_start_x = (height - 16) / 2 + 4; // Vertically center the movement instructions
        int movement_start_y = (width - 15) / 2;     // Horizontally center the movement instructions

        // Print movement instructions inside the window
        mvwprintw(help_win, movement_start_x, 1, " Movement:");
        mvwprintw(help_win, movement_start_x + 1, movement_start_y, "+---+---+---+");
        mvwprintw(help_win, movement_start_x + 2, movement_start_y, "| 7 | 8 | 9 |");
        mvwprintw(help_win, movement_start_x + 3, movement_start_y, "+---+---+---+");
        mvwprintw(help_win, movement_start_x + 4, movement_start_y, "| 4 |   | 6 |");
        mvwprintw(help_win, movement_start_x + 5, movement_start_y, "+---+---+---+");
        mvwprintw(help_win, movement_start_x + 6, movement_start_y, "| 1 | 2 | 3 |");
        mvwprintw(help_win, movement_start_x + 7, movement_start_y, "+---+---+---+");

        // Print alternative movement keys inside the window, centered
        mvwprintw(help_win, movement_start_x + 9, 1, " Alternative Movement:");
        mvwprintw(help_win, movement_start_x + 10, movement_start_y, "+---+---+---+");
        mvwprintw(help_win, movement_start_x + 11, movement_start_y, "| Y | J | U |");
        mvwprintw(help_win, movement_start_x + 12, movement_start_y, "+---+---+---+");
        mvwprintw(help_win, movement_start_x + 13, movement_start_y, "| H |   | L |");
        mvwprintw(help_win, movement_start_x + 14, movement_start_y, "+---+---+---+");
        mvwprintw(help_win, movement_start_x + 15, movement_start_y, "| B | K | N |");
        mvwprintw(help_win, movement_start_x + 16, movement_start_y, "+---+---+---+");

        wattroff(help_win, A_BOLD);

        CH = wgetch(help_win);

        // int whichWeapon = 0;
        // ptr_to_hero->current_weapon = whichWeapon;
        switch (CH)
        {
        case 'p':
        case 'P':
            if(hero->pick == 0){
                hero->pick = 1;
            }
            else{
                hero->pick = 0;
            }
        default:
            break;
        }

        wrefresh(help_win);

    }
    // delete the window
    delwin(help_win);
    clear();

}

void help2(player* hero ) {
    int height = 38;
    int width = 70;
    int start_x = (LINES - height) / 2;
    int start_y = (COLS - width) / 2;

    // create a new window for the help screen
    WINDOW *help_win = newwin(height, width, start_x, start_y);

    init_pair(6, COLOR_GREEN, COLOR_BLACK);
    // draw borders around the window
    wattron(help_win, COLOR_PAIR(6));
    box(help_win, 0, 0);
    wattron(help_win, COLOR_PAIR(6));

    init_pair(5, COLOR_CYAN, COLOR_BLACK);

    int title_y = (width - 9) / 2; // length of "HELP MENU" = 9

    // Print HELP MENU in cyan color and centered
    wattron(help_win, COLOR_PAIR(5) | A_BOLD);
    mvwprintw(help_win, 1, title_y, "HELP MENU");
    wattroff(help_win, COLOR_PAIR(5) | A_BOLD);
    char CH = 'p';

    char* TheColor = "color";
    if(hero->color == 160) {strcpy(TheColor , "Red\0");}
    else if (hero->color == 82) {strcpy(TheColor , "Green\0");}
    else if (hero->color == 220) {strcpy(TheColor , "Yellow\0");}
    else if (hero->color == 205) {strcpy(TheColor , "Pink\0");}
    else if (hero->color == 39) {strcpy(TheColor , "Blue\0");}

    while(CH == 'p' || CH == 'P'){
        wattron(help_win, A_BOLD);

        // print instructions inside the window
        mvwprintw(help_win, 3, 1, " Viewing Foods: F");
        mvwprintw(help_win, 4, 1, " Viewing Weapons: I");
        mvwprintw(help_win, 5, 1, " Viewing Spells: X");
        mvwprintw(help_win, 7, 1, " Pick Up option: ");
        wattron(help_win, A_ITALIC);
        if (hero->pick){
            mvwprintw(help_win, 7, 1 + 17, "ON ");
        }
        else{
            mvwprintw(help_win, 7, 1 + 17, "OFF");
        }
        wattroff(help_win, A_ITALIC);

        wattroff(help_win, A_BOLD);
        mvwprintw(help_win, 8, 1, " To turn on/off the Pick Up option, enter 'P'");
        wattron(help_win, A_BOLD);

        int movement_start_x = (height - 16) / 2 + 4; // Vertically center the movement instructions
        int movement_start_y = (width - 15) / 2;     // Horizontally center the movement instructions

        // Print movement instructions inside the window
        mvwprintw(help_win, movement_start_x, 1, " Movement:");
        mvwprintw(help_win, movement_start_x + 1, movement_start_y, "+---+---+---+");
        mvwprintw(help_win, movement_start_x + 2, movement_start_y, "| 7 | 8 | 9 |");
        mvwprintw(help_win, movement_start_x + 3, movement_start_y, "+---+---+---+");
        mvwprintw(help_win, movement_start_x + 4, movement_start_y, "| 4 |   | 6 |");
        mvwprintw(help_win, movement_start_x + 5, movement_start_y, "+---+---+---+");
        mvwprintw(help_win, movement_start_x + 6, movement_start_y, "| 1 | 2 | 3 |");
        mvwprintw(help_win, movement_start_x + 7, movement_start_y, "+---+---+---+");

        // Print alternative movement keys inside the window, centered
        mvwprintw(help_win, movement_start_x + 9, 1, " Alternative Movement:");
        mvwprintw(help_win, movement_start_x + 10, movement_start_y, "+---+---+---+");
        mvwprintw(help_win, movement_start_x + 11, movement_start_y, "| Y | J | U |");
        mvwprintw(help_win, movement_start_x + 12, movement_start_y, "+---+---+---+");
        mvwprintw(help_win, movement_start_x + 13, movement_start_y, "| H |   | L |");
        mvwprintw(help_win, movement_start_x + 14, movement_start_y, "+---+---+---+");
        mvwprintw(help_win, movement_start_x + 15, movement_start_y, "| B | K | N |");
        mvwprintw(help_win, movement_start_x + 16, movement_start_y, "+---+---+---+");
        wattron(help_win, COLOR_PAIR(hero->color));
        mvwprintw(help_win, movement_start_x + 18, 1, " Your Data:");
        wattroff(help_win, A_BOLD);
        mvwprintw(help_win, movement_start_x + 19, 1, " \tUsername: %s" , hero->username);
        mvwprintw(help_win, movement_start_x + 20, 1, " \tColor: %s" , TheColor);
        mvwprintw(help_win, movement_start_x + 21, 1, " \tDifficulty: %d" , hero->difficulty);
        wattroff(help_win, COLOR_PAIR(hero->color));

        CH = wgetch(help_win);

        // int whichWeapon = 0;
        // ptr_to_hero->current_weapon = whichWeapon;
        switch (CH)
        {
        case 'p':
        case 'P':
            if(hero->pick == 0){
                hero->pick = 1;
            }
            else{
                hero->pick = 0;
            }
        default:
            break;
        }

        wrefresh(help_win);

    }
    // delete the window
    delwin(help_win);
    clear();

}

// already_a_username(): function to check if username exists (using new_user.h library)

// function to check if the password matches the username
int check_password(const char* username, const char* input){
    char path[MAX_SIZE];
    snprintf(path , sizeof(path) , "/home/arvin_rsl/Desktop/FOP_Project/Users_Folder/%s/user_data.txt", username);
    
    FILE* user_data_fptr = fopen(path , "r");

    if (user_data_fptr == NULL){
        mvprintw(LINES / 2 , COLS / 2 , "user_data file not found for this user\n");
        return 0;
    }

    char line[MAX_SIZE]; 
    char password[MAX_SIZE];

    while(fgets(line , sizeof(line) , user_data_fptr)){
        if(strncmp(line , "password: " , 10) == 0){ // we are in the line "password: "
            strcpy(password , line + 10);
            break;
        }
    }
    // removing \n  or  ' ' from password
    int i = 0;
    while( (password[i] != ' ') && (password[i] != '\n') ){
        i++;
    }
    password[i] = '\0';
    fclose(user_data_fptr);
    
    // checking if input matches password
    if (strcmp(password , input) == 0){
        return 1;
    }
    else{
        return 0;
    }
}
// checked :)

// function for login
void log_in(int* ptr_difficulty , int* ptr_color , int* ptr_song ){
    
    char username[MAX_SIZE], pass[MAX_SIZE];
    int valid_user = 0, valid_pass = 0;

    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    bkgd(COLOR_PAIR(1));

    while (1){
        clear();
        draw_title("Log In");
        draw_borders(11);
        mvprintw(LINES / 2 - 3, (COLS - strlen("Enter Username: 00000000"))/ 2, "Enter Username: ");
        echo();
        getstr(username);
        noecho();
        if (!already_a_username(username)){
            mvprintw(LINES / 2 - 1, (COLS - strlen("Username doesn't exist! Try again"))/ 2 , "Username doesn't exist! Try again");
            refresh();
            getch();
        } 
        else{
            valid_user = 1;
            break;
        }
    }

    int forgot = 0;
    while (!forgot){
        clear();
        draw_title("Log In");
        draw_borders(11);
        mvprintw(LINES / 2 - 3, (COLS - strlen("Enter Username: 00000000"))/ 2, "Enter Username: ");
        mvprintw(LINES / 2 - 3, (COLS + strlen("Enter User"))/ 2 , "%s" , username);
        mvprintw(LINES / 2 - 1, (COLS - strlen("Enter Password: 00000000"))/ 2 , "Enter Password: ");
        echo();
        getstr(pass);
        noecho();
        if (check_password(username , pass)){
            valid_pass = 1;
            break;
        } 
        else{
            mvprintw(LINES / 2 + 1, (COLS - strlen("Password doesn't match! Try again"))/ 2 , "Password doesn't match! Try again");
            mvprintw(LINES / 2 + 3, (COLS - strlen("Forgot Password?  Press 'f'"))/ 2, "Forgot Password?  Press 'f'");

            refresh();
            char c = getch();
            if (c == 'f' || c == 'F'){
                forgot = 1;
            }
        }
    }

    if (forgot == 1){
        clear();
        draw_title("Log In");
        draw_borders(11);
        char random_pass[MAX_SIZE];
        generate_pass(random_pass);
        // strcpy(password, random_pass);
        init_pair(101 , COLOR_YELLOW , COLOR_BLACK);
        attron(COLOR_PAIR(101));
        mvprintw(LINES / 2 , (COLS - strlen("Your new password is: 123456789000"))/ 2, "Your new password is: %s", random_pass);
        attroff(COLOR_PAIR(101));
        mvprintw(LINES / 2 + 2, (COLS - strlen("Press any key to proceed"))/ 2, "Press any key to proceed");
        refresh();   

        char path[1024];
        snprintf(path, sizeof(path), "/home/arvin_rsl/Desktop/FOP_Project/Users_Folder/%s/user_data.txt", username);
        FILE *file = fopen(path, "r");
        if (file == NULL) {
            perror("Error opening file");
        }

        char buffer[256];
        char email[256];
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            if (strncmp(buffer, "email:", 6) == 0) {
                sscanf(buffer, "email: %s", email);
                break;
            }
        }

        fclose(file);
        remove(path);
        
        create_user_data_file(username , email , random_pass);

        getch();
        clear();
        draw_borders(12);
        mvprintw(LINES / 2, (COLS - strlen("Log in was successful!"))/ 2 , "Log in was successful!");
        mvprintw(LINES / 2 + 2, (COLS - strlen("Press any key to proceed"))/ 2, "Press any key to proceed");
        refresh();
        getch();
        pregame_menu(username , ptr_difficulty , ptr_color , ptr_song);
    }
       
    else if (valid_user && valid_pass) {
        clear();
        // draw_title("Log In");
        draw_borders(12);
        mvprintw(LINES / 2, (COLS - strlen("Log in was successful!"))/ 2, "Log in was successful!");
        mvprintw(LINES / 2 + 2, (COLS - strlen("Press any key to proceed"))/ 2, "Press any key to proceed");
        refresh();
        getch();
        pregame_menu(username , ptr_difficulty , ptr_color , ptr_song);
    }
    endwin();
}
// checked :)
// function to print the menu options
void print_menu(int highlight , char** choices, int n_choices , int which_color , const char* title){
    // three options
    clear();
    draw_title(title);
    for (int i = 1; i <= n_choices; ++i){
        if (highlight == i){
            attron(A_REVERSE); // highlight the selected option
            mvprintw(LINES / 2 + 2*(i-1), (COLS - strlen(choices[i-1])) / 2, "%s", choices[i-1]);
            attroff(A_REVERSE);
        }
        else{
            mvprintw(LINES / 2 + 2*(i-1), (COLS - strlen(choices[i-1])) / 2, "%s", choices[i-1]);
        }
    }
    draw_borders(which_color);
    refresh();
}
// checked :) ==> It can be used later (e.g. in pregame menu) as well 

// function for entrance menu
void entrance_menu(){
    initscr();
    start_color();
    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    bkgd(COLOR_PAIR(0));
    keypad(stdscr, TRUE); // enable keyboard input for the window
    curs_set(0); // hide cursor
    int highlight = 1;
    int choice = 0;
    int c;
    char *choices[] = {"Log In", "Create New User", "Enter As Guest"}; 

    char* my_username = "GUEST"; // initialize
    int DIFFICULTY = 1;  // initialize
    int HERO_COLOR = 39; // initialize with light blue
    int song  = 2 ; // default = gole yakh
    int* ptr_difficulty = &DIFFICULTY;
    int* ptr_color = &HERO_COLOR;
    int* ptr_song = &song;


    while (1){
        // draw_title("Entrance Menu" , 20);
        print_menu(highlight , choices , 3 , 10 , "Entrance Menu");
        c = getch();
        switch(c){
            case KEY_UP:
                if (highlight == 1){
                    highlight = 3;
                    break;
                }
                else if(highlight == 2){
                    highlight--;
                    break;
                }
                else if(highlight == 3){
                    highlight--;
                    break;
                }
            case KEY_DOWN:
                if (highlight == 3){
                    highlight = 1;
                    break;
                }
                else if(highlight == 2){
                    highlight++;
                    break;
                }
                else if(highlight == 1){
                    highlight++;
                    break;
                }
            case 10: // ENTER key
                choice = highlight;
                break;
            default:
                break;
        }

        if (choice != 0){
            break;
        }

    }

    // call the appropriate function based on the choice
    if (choice == 1){
        log_in(ptr_difficulty , ptr_color , ptr_song);
    }
    else if (choice == 2){
        create_user( ptr_difficulty ,  ptr_color , ptr_song );
    }
    else if (choice == 3){
        clear();
        draw_borders(12);
        mvprintw(LINES / 2, COLS / 2 - strlen("You have entered as guest")/2 , "You have entered as guest");
        mvprintw(LINES / 2 + 2, COLS / 2 - strlen("Press any key to proceed")/2, "Press any key to proceed");
        refresh();
        getch();
        pregame_menu(my_username , ptr_difficulty , ptr_color , ptr_song);
    }

    endwin(); 
}
//checked :)

// design!
void draw_borders(int which_color){
    start_color();
    init_pair(9 , COLOR_WHITE, COLOR_BLACK);
    init_pair(10 , COLOR_CYAN , COLOR_BLACK);
    init_pair(11 , COLOR_RED , COLOR_BLACK);
    init_pair(12 , COLOR_GREEN , COLOR_BLACK);
    init_pair(13 , COLOR_YELLOW , COLOR_BLACK);
    
    attron(COLOR_PAIR(which_color));      
    for (int i = 1; i < COLS - 1; i++) { 
        mvprintw(0, i, "_");         // Top border
        mvprintw(LINES - 2, i, "_"); // Bottom border
    }
    
    for (int i = 1; i < LINES - 1; i++) {
        mvprintw(i, 1, "|");         // Left border
        mvprintw(i, COLS - 2, "|");  // Right border
    }
    attroff(COLOR_PAIR(which_color)); 
}

// title
void draw_title(const char* title){
    init_pair(120 , COLOR_WHITE , COLOR_BLUE);
    attron(COLOR_PAIR(120));
    int y = (COLS - strlen(title) - 16) / 2;
    mvprintw(3, y, " <<==== %s ====>> ", title);
    attroff(COLOR_PAIR(120));
}
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
    qsort(entries, entry_count, sizeof(ScoreEntry), compare_score);

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
            if (strcmp(entries[i].username, my_username) == 0) { // the user him-/her- self
                // Bold my_username
                attron(A_BOLD | A_ITALIC);
                mvprintw(start_x + (i - start_index) + 3, start_y, "| %*d | %-*s |  %*d | %*d | %*d | %*d   | %s",
                         rank_width, entries[i].rank,
                         username_width, entries[i].username,
                         score_width, entries[i].total_score,
                         gold_width, entries[i].latest_gold,
                         games_width, entries[i].rank, 
                         experience_width, entries[i].experience,
                         label);
                attroff(A_BOLD | A_ITALIC);
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

// show the options in pregame menu (Settings , Score Table , New Game , Continue Saved Game , Back)
void pregame_menu(char* my_username , int* ptr_difficulty , int* ptr_color , int* ptr_song){
    setlocale(LC_ALL, "");
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    bkgd(COLOR_PAIR(1));
    keypad(stdscr, TRUE); // enable keyboard input for the window
    curs_set(0); // hide cursor
    int highlight = 1;
    int choice = 0;
    int c;
    char *choices[] = {"Settings", "Score Table", "New Game" , "Continue Saved Game" , "Back to Entrance Menu"}; 
    setlocale(LC_ALL, "");

    while (1){
        clear();
        // draw_title("Pregame Menu");
        print_menu(highlight , choices , 5 , 10 , "Pregame Menu");
        c = getch();
        switch(c){
            case KEY_UP:
                if (highlight == 1){
                    highlight = 5;
                    break;
                }
                else{
                    highlight--;
                    break;
                }
            case KEY_DOWN:
                if (highlight == 5){
                    highlight = 1;
                    break;
                }
                else{
                    highlight++;
                    break;
                }
            case 10: // ENTER key
                choice = highlight;
                break;
            default:
                break;
        }

        if (choice != 0){
            break;
        }

    }

    // call the appropriate function based on the choice
    if (choice == 1){
        settings(my_username , ptr_difficulty , ptr_color , ptr_song);
    }
    else if (choice == 2){
        int start_page = 1;
        // Show the score table starting from the first page
        show_score_table2(my_username, start_page);
    }
    else if (choice == 3){
        clear();
        New_Game(*ptr_difficulty , *ptr_song , *ptr_color , my_username);
    }
    else if (choice == 4){
        // show_saved_games();
    }
    else if (choice == 5){
        entrance_menu();
    }
    endwin(); 
}

// show the options in Settings (Level Of Difficulty , Songs , Hero's Color)
void settings(char* my_username , int* ptr_difficulty , int* ptr_color , int* ptr_song){
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    bkgd(COLOR_PAIR(1));
    keypad(stdscr, TRUE); // enable keyboard input for the window
    curs_set(0); // hide cursor
    int highlight = 1;
    int choice = 0;
    int c;
    char *choices[] = {"Level Of Difficulty", "Songs", "Hero's Color" , "Back to Pregame Menu"}; 

    while (1){
        // draw_title("Settings");
        print_menu(highlight , choices , 4 , 10 , "Settings");
        c = getch();
        switch(c){
            case KEY_UP:
                if (highlight == 1){
                    highlight = 4;
                    break;
                }
                else{
                    highlight--;
                    break;
                }
            case KEY_DOWN:
                if (highlight == 4){
                    highlight = 1;
                    break;
                }
                else{
                    highlight++;
                    break;
                }
            case 10: // ENTER key
                choice = highlight;
                break;
            default:
                break;
        }

        if (choice != 0){
            break;
        }

    }

    // call the appropriate function based on the choice
    if (choice == 1){
        choose_difficulty(ptr_difficulty , ptr_color , ptr_song, my_username);
    }
    else if (choice == 2){
        choose_song(ptr_difficulty , ptr_color , ptr_song , my_username);
    }
    else if (choice == 3){
        choose_color(ptr_difficulty , ptr_color  , ptr_song, my_username);
    }
    else if (choice == 4){
        pregame_menu(my_username , ptr_difficulty , ptr_color , ptr_song);
    }
    endwin(); 
}

// choose level of difficulty:  
                                //     1 for Easy   
                                //     2 for Medium   
                                //     3 for Hard   
void choose_difficulty(int* ptr_diff ,  int* ptr_color , int* ptr_song,  char* my_username){
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    bkgd(COLOR_PAIR(1));
    keypad(stdscr, TRUE); // enable keyboard input for the window
    curs_set(0); // hide cursor
    int highlight = 1;
    int choice = 0;
    int c;
    char *choices[] = {"Easy (default)", "Medium", "Hard" , "Back"}; 
    while (1){
        // draw_title("Difficulty");
        print_menu(highlight , choices , 4 , 11 , "Difficulty");
        c = getch();
        switch(c){
            case KEY_UP:
                if (highlight == 1){
                    highlight = 4;
                    break;
                }
                else{
                    highlight--;
                    break;
                }
            case KEY_DOWN:
                if (highlight == 4){
                    highlight = 1;
                    break;
                }
                else{
                    highlight++;
                    break;
                }
            case 10: // ENTER key
                choice = highlight;
                break;
            default:
                break;
        }

        if (choice != 0){
            break;
        }
    }


    if(choice == 2){
        *ptr_diff = 2;
        settings(my_username , ptr_diff , ptr_color , ptr_song);
    }
    else if(choice == 3){
        *ptr_diff = 3;
        settings(my_username , ptr_diff , ptr_color , ptr_song);
    }    
    else if(choice == 1){
        *ptr_diff = 1;
        settings(my_username , ptr_diff , ptr_color , ptr_song);
    }
    else if (choice == 4){
        settings(my_username , ptr_diff , ptr_color , ptr_song);
    }
    // else{
    //     *ptr_diff = 1;
    // }
    endwin(); 
}

// choose Hero's color:   
                                //     RED      1 
                                //     GREEN	2  
                                //     BLUE	    3  
                                //     MAGENTA  4   
                                //     CYAN	    5  
void choose_color(int*ptr_difficulty , int* ptr_color , int*ptr_song,  char* my_username){
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    bkgd(COLOR_PAIR(1));
    keypad(stdscr, TRUE); // enable keyboard input for the window
    curs_set(0); // hide cursor
    int highlight = 1;
    int choice = 0;
    int c;
    char *choices[] = {"Red", "Green", "Yellow" , "Pink" , "Blue" , "Back"}; 
    while (1){
        // draw_title("Hero's Color");
        print_menu(highlight , choices , 6 , 9 , "Player's Color");
        c = getch();
        switch(c){
            case KEY_UP:
                if (highlight == 1){
                    highlight = 6;
                    break;
                }
                else{
                    highlight--;
                    break;
                }
            case KEY_DOWN:
                if (highlight == 6){
                    highlight = 1;
                    break;
                }
                else{
                    highlight++;
                    break;
                }
            case 10: // ENTER key
                choice = highlight;
                break;
            default:
                break;
        }

        if (choice != 0){
            break;
        }
    }
    if(choice == 1){
        // red
        *ptr_color = 160;
        settings(my_username , ptr_difficulty , ptr_color , ptr_song);
    }
    else if(choice == 2){
        // green
        *ptr_color = 82;
        settings(my_username , ptr_difficulty , ptr_color , ptr_song);
    }
    else if(choice == 3){
        // yellow
        *ptr_color = 220;
        settings(my_username , ptr_difficulty , ptr_color , ptr_song);
    }
    else if(choice == 4){
        // pink
        *ptr_color = 205;
        settings(my_username , ptr_difficulty , ptr_color , ptr_song);
    }
    else if(choice == 5){
        // blue (light blue)
        *ptr_color = 39;
        settings(my_username , ptr_difficulty , ptr_color , ptr_song);
    }
    else if (choice == 6){
        settings(my_username , ptr_difficulty , ptr_color , ptr_song);
    }

    endwin(); 
}

// choose theme songs (for regular room type) 
                                //     1 for song1   
                                //     2 for song2   
                                //     3 for song3
void choose_song(int* ptr_diff , int * ptr_color , int* song , char* my_username){

    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    bkgd(COLOR_PAIR(1));
    keypad(stdscr, TRUE); // enable keyboard input for the window
    curs_set(0); // hide cursor
    int highlight = 1;
    int choice = 0;
    int c;
    char *choices[] = {"Song 1", "Song 2 (default)" , "Song 3" , "None" ,"Back"}; 
    init_audio();
    while (1){
        // draw_title(/);
        print_menu(highlight , choices , 5 , 12 , "Theme Song");
        if(1 == highlight || 2 == highlight || 3 == highlight){
            choose_soundtrack(highlight);
        }
        else if (4 == highlight || 5 == highlight){
            stop_soundtrack();
        }

        c = getch();
        switch(c){
            case KEY_UP:
                if (highlight == 1){
                    highlight = 5;
                    break;
                }
                else{
                    highlight--;
                    break;
                }
            case KEY_DOWN:
                if (highlight == 5){
                    highlight = 1;
                    break;
                }
                else{
                    highlight++;
                    break;
                }
            case 10: // ENTER key
                choice = highlight;
                break;
            default:
                break;
        }

        if (choice != 0){
            break;
        }
    }

    if(choice == 1){
        *song = 1;
        settings(my_username , ptr_diff , ptr_color , song);

    }
    else if(choice == 2){
        *song = 2;
        settings(my_username , ptr_diff , ptr_color , song);

    }   
    else if(choice == 3){
        *song = 3;
        settings(my_username , ptr_diff , ptr_color , song);

    }
    else if (choice == 5){
        stop_soundtrack();
        settings(my_username , ptr_diff , ptr_color , song);
    }
    else if (choice == 4){
        
        choice = 0;
        // choose_soundtrack(choice);
        *song = choice;
        settings(my_username , ptr_diff , ptr_color , song);

    }
    
    endwin(); 
}


// function to add spells to enchant room (1 or 0 of each spell)
void add_spell(room** address_rooms_this_level , int n_rooms){
    srand(time(NULL));
    for (int i = 0 ; i < n_rooms ; i++){
    
        room r1 = (*address_rooms_this_level)[i];
        if (r1.type == 2){
            // Enchant Room
        
            int x_north1 = r1.corner.x;
            int x_south1 = r1.corner.x + r1.length - 1;
            int y_west1 = r1.corner.y;
            int y_east1 = r1.corner.y + r1.width - 1;
            for (int W = 0 ; W < 3 ; W++){
                r1.spells[W] = rand() % 2;
                (*address_rooms_this_level)[i].spells[W] = r1.spells[W] ;
            }
            
            int k0 = 0;
            int k1 = 0;
            int k2 = 0;

            while (k0 != r1.spells[0]){
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
                for (int G = 0 ; G < r1.n_golds ; G++){
                    if(x == r1.golds_x[G] && y == r1.golds_y[G]){
                        // the random location overlaps with a gold
                        overlap = 1;
                    }
                }
                if(r1.black_gold){
                    if(x == r1.black_gold_x && y == r1.black_gold_y){
                        // the random location overlaps with a black gold
                        overlap = 1;
                    }
                }
            
                if(!overlap){
                    (*address_rooms_this_level)[i].spells_x[0] = x;
                    (*address_rooms_this_level)[i].spells_y[0] = y;
                    k0 = r1.spells[0];
                }

            }
        
            while (k1 != r1.spells[1]){
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
                for (int G = 0 ; G < r1.n_golds ; G++){
                    if(x == r1.golds_x[G] && y == r1.golds_y[G]){
                        // the random location overlaps with a gold
                        overlap = 1;
                    }
                }
                if(r1.black_gold){
                    if(x == r1.black_gold_x && y == r1.black_gold_y){
                        // the random location overlaps with a black gold
                        overlap = 1;
                    }
                }
            
                if(!overlap){
                    (*address_rooms_this_level)[i].spells_x[1] = x;
                    (*address_rooms_this_level)[i].spells_y[1] = y;
                    k1 = r1.spells[1];
                }

            }
            
            while (k2 != r1.spells[2]){
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
                for (int G = 0 ; G < r1.n_golds ; G++){
                    if(x == r1.golds_x[G] && y == r1.golds_y[G]){
                        // the random location overlaps with a gold
                        overlap = 1;
                    }
                }
                if(r1.black_gold){
                    if(x == r1.black_gold_x && y == r1.black_gold_y){
                        // the random location overlaps with a black gold
                        overlap = 1;
                    }
                }
            
                if(!overlap){
                    (*address_rooms_this_level)[i].spells_x[2] = x;
                    (*address_rooms_this_level)[i].spells_y[2] = y;
                    k2 = r1.spells[2];
                }

            }
        }
    }


}




void add_enemy2(room** address_rooms_this_level , int n_rooms){
    srand(time(NULL));
    for (int i = 0 ; i < n_rooms ; i++){
        /// Index:
        // 0 : Deamon       (D)
        // 1 : Fire-Breath  (F)
        // 2 : Giant        (G)
        // 3 : Snake        (S)
        // 4 : Undeed       (U)
        /// Hit Strength:
        // 1 : Deamon       (D)
        // 2 : Fire-Breath  (F)
        // 3 : Giant        (G)
        // 1 : Snake        (S)
        // 5 : Undeed       (U)
        /// Initial Health: 
        // 5  : Deamon       (D)
        // 10 : Fire-Breath  (F)
        // 15 : Giant        (G)
        // 20 : Snake        (S)
        // 30 : Undead       (U)
        room r1 = (*address_rooms_this_level)[i];
        if (r1.type != 2 && r1.room_number != 2){
            int x_north1 = r1.corner.x;
            int x_south1 = r1.corner.x + r1.length - 1;
            int y_west1 = r1.corner.y;
            int y_east1 = r1.corner.y + r1.width - 1;
            r1.enemies_remained_health[0] = 5;
            r1.enemies_remained_health[1] = 10;
            r1.enemies_remained_health[2] = 15;
            r1.enemies_remained_health[3] = 20;
            r1.enemies_remained_health[4] = 30;
            for (int ajab = 0 ; ajab < 5 ; ajab++){
                (*address_rooms_this_level)[i].enemies_remained_health[ajab] = r1.enemies_remained_health[ajab];
            }
            r1.can_enemy_move[0] = 0;
            r1.can_enemy_move[1] = 0;
            r1.can_enemy_move[2] = 1;
            r1.can_enemy_move[3] = 1;
            r1.can_enemy_move[4] = 1;
            for (int ajab = 0 ; ajab < 5 ; ajab++){
                (*address_rooms_this_level)[i].can_enemy_move[ajab] = r1.can_enemy_move[ajab];
            }
            for (int E = 0 ; E < 5 ; E++){
                r1.enemies[E] = rand() % 2;
                if (r1.type == 1){
                    r1.enemies[E] = 1; // all enemies in battle room
                }
                if(r1.room_number == 1){ // no 'G'iant in room index 0 because of black 'G'old
                    r1.enemies[2] = 0;
                }
                if (r1.type == 3){
                    // treasue room
                    r1.enemies[E] = 1;
                }
                (*address_rooms_this_level)[i].enemies[E] = r1.enemies[E];
            }
            
            int k0 = 0; // D
            int k1 = 0; // F
            int k2 = 0; // G (Never in Room Index 0)
            int k3 = 0; // S
            int k4 = 0; // U


            while (k0 != r1.enemies[0]){
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
                for (int G = 0 ; G < r1.n_golds ; G++){
                    if(x == r1.golds_x[G] && y == r1.golds_y[G]){
                        // the random location overlaps with a gold
                        overlap = 1;
                    }
                }
                if(r1.black_gold){
                    if(x == r1.black_gold_x && y == r1.black_gold_y){
                        // the random location overlaps with a black gold
                        overlap = 1;
                    }
                }
                for (int ww = 0 ; ww < 5 ; ww++){
                    if(r1.weapons[ww]){
                        if(x == r1.weapons_x[ww] && y == r1.weapons_y[ww]){
                            // the random location overlaps with a weapon
                            overlap = 1;
                        }
                    }
                }
                if(!overlap){
                    // (*address_rooms_this_level)[i].Deamon.exists_in_room = 1;
                    // (*address_rooms_this_level)[i].Deamon.remained_health = 5;
                    // (*address_rooms_this_level)[i].Deamon.hit_strength = 1;
                    (*address_rooms_this_level)[i].enemies_x[0]= x;
                    (*address_rooms_this_level)[i].enemies_y[0]= y;
                    // r1.Deamon.exists_in_room = 1;
                    // r1.Deamon.remained_health = 5;
                    // r1.Deamon.hit_strength = 1;
                    r1.enemies_x[0] = x;
                    r1.enemies_y[0] = y;
                    k0 = r1.enemies[0];
                }

            }

            while (k1 != r1.enemies[1]){
                int x = rand() % (x_south1 - x_north1 - 3) + x_north1 + 2;
                int y = rand() % (y_east1 - y_west1 - 3) + y_west1 + 2;

                int overlap = 0;
                if(x == r1.enemies_x[0] && y == r1.enemies_y[0]){
                    overlap = 1;
                }
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
                for (int G = 0 ; G < r1.n_golds ; G++){
                    if(x == r1.golds_x[G] && y == r1.golds_y[G]){
                        // the random location overlaps with a gold
                        overlap = 1;
                    }
                }
                if(r1.black_gold){
                    if(x == r1.black_gold_x && y == r1.black_gold_y){
                        // the random location overlaps with a black gold
                        overlap = 1;
                    }
                }
                for (int ww = 0 ; ww < 5 ; ww++){
                    if(r1.weapons[ww]){
                        if(x == r1.weapons_x[ww] && y == r1.weapons_y[ww]){
                            // the random location overlaps with a weapon
                            overlap = 1;
                        }
                    }
                }
                if(!overlap){
                    //////////////change deamon after dinner:
                    // (*address_rooms_this_level)[i].Fire_Breath.exists_in_room = 1;
                    // (*address_rooms_this_level)[i].Fire_Breath.remained_health = 10;
                    // (*address_rooms_this_level)[i].Fire_Breath.hit_strength = 2;
                    (*address_rooms_this_level)[i].enemies_x[1]= x;
                    (*address_rooms_this_level)[i].enemies_y[1]= y;
                    r1.enemies_x[1]= x;
                    r1.enemies_y[1] = y;
                    // r1.Fire_Breath.exists_in_room = 1;
                    // r1.Fire_Breath.remained_health = 10;
                    // r1.Fire_Breath.hit_strength = 2;
                    // r1.Fire_Breath.pos.x = x;
                    // r1.Fire_Breath.pos.y = y;
                    k1 = r1.enemies[1];
                }

            }

            while (k2 != r1.enemies[2]){
                int x = rand() % (x_south1 - x_north1 - 3) + x_north1 + 2;
                int y = rand() % (y_east1 - y_west1 - 3) + y_west1 + 2;

                int overlap = 0;
                if(x == r1.enemies_x[0] && y == r1.enemies_y[0]){
                    overlap = 1;
                }
                if(x == r1.enemies_x[1] && y == r1.enemies_y[1]){
                    overlap = 1;
                }
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
                for (int G = 0 ; G < r1.n_golds ; G++){
                    if(x == r1.golds_x[G] && y == r1.golds_y[G]){
                        // the random location overlaps with a gold
                        overlap = 1;
                    }
                }
                if(r1.black_gold){
                    if(x == r1.black_gold_x && y == r1.black_gold_y){
                        // the random location overlaps with a black gold
                        overlap = 1;
                    }
                }
                for (int ww = 0 ; ww < 5 ; ww++){
                    if(r1.weapons[ww]){
                        if(x == r1.weapons_x[ww] && y == r1.weapons_y[ww]){
                            // the random location overlaps with a weapon
                            overlap = 1;
                        }
                    }
                }
                if(!overlap){
                    //////////////change deamon after dinner:
                    // (*address_rooms_this_level)[i].Giant.exists_in_room = 1;
                    // (*address_rooms_this_level)[i].Giant.remained_health = 15;
                    // (*address_rooms_this_level)[i].Giant.hit_strength = 3;
                    (*address_rooms_this_level)[i].enemies_x[2] = x;
                    (*address_rooms_this_level)[i].enemies_y[2] = y;
                    // r1.Giant.exists_in_room = 1;
                    // r1.Giant.remained_health = 15;
                    // r1.Giant.hit_strength = 3;
                    r1.enemies_x[2]= x;
                    r1.enemies_y[2] = y;
                    k2 = r1.enemies[2];
                }

            }

            while (k3 != r1.enemies[3]){
                int x = rand() % (x_south1 - x_north1 - 3) + x_north1 + 2;
                int y = rand() % (y_east1 - y_west1 - 3) + y_west1 + 2;

                int overlap = 0;
                if(x == r1.enemies_x[0] && y == r1.enemies_y[0]){
                    overlap = 1;
                }
                if(x == r1.enemies_x[1] && y == r1.enemies_y[1]){
                    overlap = 1;
                }
                if(x == r1.enemies_x[2] && y == r1.enemies_y[2]){
                    overlap = 1;
                }
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
                for (int G = 0 ; G < r1.n_golds ; G++){
                    if(x == r1.golds_x[G] && y == r1.golds_y[G]){
                        // the random location overlaps with a gold
                        overlap = 1;
                    }
                }
                if(r1.black_gold){
                    if(x == r1.black_gold_x && y == r1.black_gold_y){
                        // the random location overlaps with a black gold
                        overlap = 1;
                    }
                }
                for (int ww = 0 ; ww < 5 ; ww++){
                    if(r1.weapons[ww]){
                        if(x == r1.weapons_x[ww] && y == r1.weapons_y[ww]){
                            // the random location overlaps with a weapon
                            overlap = 1;
                        }
                    }
                }
                if(!overlap){
                    //////////////change deamon after dinner:
                    // (*address_rooms_this_level)[i].Snake.exists_in_room = 1;
                    // (*address_rooms_this_level)[i].Snake.remained_health = 20;
                    // (*address_rooms_this_level)[i].Snake.hit_strength = 1;
                    (*address_rooms_this_level)[i].enemies_x[3] = x;
                    (*address_rooms_this_level)[i].enemies_y[3] = y;
                    // r1.Snake.exists_in_room = 1;
                    // r1.Snake.remained_health = 20;
                    // r1.Snake.hit_strength = 1;
                    r1.enemies_x[3] = x;
                    r1.enemies_y[3] = y;
                    k3 = r1.enemies[3];
                }

            }

            while (k4 != r1.enemies[4]){
                int x = rand() % (x_south1 - x_north1 - 3) + x_north1 + 2;
                int y = rand() % (y_east1 - y_west1 - 3) + y_west1 + 2;

                int overlap = 0;
                if(x == r1.enemies_x[0] && y == r1.enemies_y[0]){
                    overlap = 1;
                }
                if(x == r1.enemies_x[1] && y == r1.enemies_y[1]){
                    overlap = 1;
                }
                if(x == r1.enemies_x[2] && y == r1.enemies_y[2]){
                    overlap = 1;
                }
                if(x == r1.enemies_x[3] && y == r1.enemies_y[3]){
                    overlap = 1;
                }
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
                for (int G = 0 ; G < r1.n_golds ; G++){
                    if(x == r1.golds_x[G] && y == r1.golds_y[G]){
                        // the random location overlaps with a gold
                        overlap = 1;
                    }
                }
                if(r1.black_gold){
                    if(x == r1.black_gold_x && y == r1.black_gold_y){
                        // the random location overlaps with a black gold
                        overlap = 1;
                    }
                }
                for (int ww = 0 ; ww < 5 ; ww++){
                    if(r1.weapons[ww]){
                        if(x == r1.weapons_x[ww] && y == r1.weapons_y[ww]){
                            // the random location overlaps with a weapon
                            overlap = 1;
                        }
                    }
                }
                if(!overlap){
                    //////////////change deamon after dinner:
                    // (*address_rooms_this_level)[i].Undeed.exists_in_room = 1;
                    // (*address_rooms_this_level)[i].Undeed.remained_health = 30;
                    // (*address_rooms_this_level)[i].Undeed.hit_strength = 5;
                    (*address_rooms_this_level)[i].enemies_x[4] = x;
                    (*address_rooms_this_level)[i].enemies_y[4] = y;
                    // r1.Undeed.exists_in_room = 1;
                    // r1.Undeed.remained_health = 30;
                    // r1.Undeed.hit_strength = 5;
                    // r1.Undeed_x = x;
                    // r1.Undeed_y = y;
                    k4 = r1.enemies[4];
                }
            }
        }   
    }
}


// function to add weapons to room (1 or 0 of each weapon) -- if the room is not enchant room
void add_weapon(room** address_rooms_this_level , int n_rooms){
    srand(time(NULL));
    for (int i = 0 ; i < n_rooms ; i++){
    
        room r1 = (*address_rooms_this_level)[i];
        if (r1.type != 2 && r1.type != 1){
            int x_north1 = r1.corner.x;
            int x_south1 = r1.corner.x + r1.length - 1;
            int y_west1 = r1.corner.y;
            int y_east1 = r1.corner.y + r1.width - 1;
            for (int W = 0 ; W < 5 ; W++){
                r1.weapons[W] = rand() % 2;
                if(W == 0){
                    r1.weapons[W] = 0; // mace cannot be collected (we just have one in hand by default)
                }
                (*address_rooms_this_level)[i].weapons[W] = r1.weapons[W] ;
            }
            
            int k0 = 0;
            int k1 = 0;
            int k2 = 0;
            int k3 = 0;
            int k4 = 0;


            while (k0 != r1.weapons[0]){
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
                for (int G = 0 ; G < r1.n_golds ; G++){
                    if(x == r1.golds_x[G] && y == r1.golds_y[G]){
                        // the random location overlaps with a gold
                        overlap = 1;
                    }
                }
                if(r1.black_gold){
                    if(x == r1.black_gold_x && y == r1.black_gold_y){
                        // the random location overlaps with a black gold
                        overlap = 1;
                    }
                }
            
                if(!overlap){
                    (*address_rooms_this_level)[i].weapons_x[0] = x;
                    (*address_rooms_this_level)[i].weapons_y[0] = y;
                    k0 = r1.weapons[0];
                }

            }

            while (k1 != r1.weapons[1]){
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
                for (int G = 0 ; G < r1.n_golds ; G++){
                    if(x == r1.golds_x[G] && y == r1.golds_y[G]){
                        // the random location overlaps with a gold
                        overlap = 1;
                    }
                }
                if(r1.black_gold){
                    if(x == r1.black_gold_x && y == r1.black_gold_y){
                        // the random location overlaps with a black gold
                        overlap = 1;
                    }
                }
            
                if(!overlap){
                    (*address_rooms_this_level)[i].weapons_x[1] = x;
                    (*address_rooms_this_level)[i].weapons_y[1] = y;
                    k1 = r1.weapons[1];
                }

            }
            
            while (k2 != r1.weapons[2]){
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
                for (int G = 0 ; G < r1.n_golds ; G++){
                    if(x == r1.golds_x[G] && y == r1.golds_y[G]){
                        // the random location overlaps with a gold
                        overlap = 1;
                    }
                }
                if(r1.black_gold){
                    if(x == r1.black_gold_x && y == r1.black_gold_y){
                        // the random location overlaps with a black gold
                        overlap = 1;
                    }
                }
            
                if(!overlap){
                    (*address_rooms_this_level)[i].weapons_x[2] = x;
                    (*address_rooms_this_level)[i].weapons_y[2] = y;
                    k2 = r1.weapons[2];
                }

            }

            while (k3 != r1.weapons[3]){
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
                for (int G = 0 ; G < r1.n_golds ; G++){
                    if(x == r1.golds_x[G] && y == r1.golds_y[G]){
                        // the random location overlaps with a gold
                        overlap = 1;
                    }
                }
                if(r1.black_gold){
                    if(x == r1.black_gold_x && y == r1.black_gold_y){
                        // the random location overlaps with a black gold
                        overlap = 1;
                    }
                }
            
                if(!overlap){
                    (*address_rooms_this_level)[i].weapons_x[3] = x;
                    (*address_rooms_this_level)[i].weapons_y[3] = y;
                    k3 = r1.weapons[3];
                }

            }

            while (k4 != r1.weapons[4]){
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
                for (int G = 0 ; G < r1.n_golds ; G++){
                    if(x == r1.golds_x[G] && y == r1.golds_y[G]){
                        // the random location overlaps with a gold
                        overlap = 1;
                    }
                }
                if(r1.black_gold){
                    if(x == r1.black_gold_x && y == r1.black_gold_y){
                        // the random location overlaps with a black gold
                        overlap = 1;
                    }
                }
            
                if(!overlap){
                    (*address_rooms_this_level)[i].weapons_x[4] = x;
                    (*address_rooms_this_level)[i].weapons_y[4] = y;
                    k4 = r1.weapons[4];
                }

            }
            
        }   
    }
}

// function to add 3 traps to the whole floor-level 
void add_trap(room** address_rooms_this_level , int n_rooms){ // first food, then gold, then traps
    srand(time(NULL));
    // NOT in room number 2 (index 1) because player starts there
    int which_room1 = rand() % n_rooms;
    if(which_room1 == 1){
        which_room1++;
    }
    int which_room2 = rand() % n_rooms;
    int which_room3 = rand() % n_rooms;
    do{
        which_room2 = rand() % n_rooms;
        which_room3 = rand() % n_rooms;
    } while(which_room2 == which_room1 || which_room2 == which_room3 || which_room3 == which_room1 || which_room2 == 1 || which_room3 == 1 );

    room r1 = (*address_rooms_this_level)[which_room1];
    room r2 = (*address_rooms_this_level)[which_room2];
    room r3 = (*address_rooms_this_level)[which_room3];

    int x_north1 = r1.corner.x;
    int x_south1 = r1.corner.x + r1.length - 1;
    int y_west1 = r1.corner.y;
    int y_east1 = r1.corner.y + r1.width - 1;

    int x_north2 = r2.corner.x;
    int x_south2 = r2.corner.x + r2.length - 1;
    int y_west2 = r2.corner.y;
    int y_east2 = r2.corner.y + r2.width - 1;
    
    int x_north3 = r3.corner.x;
    int x_south3 = r3.corner.x + r3.length - 1;
    int y_west3 = r3.corner.y;
    int y_east3 = r3.corner.y + r3.width - 1;

    int k1 = 0;
    while (k1 < 1){
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
        for (int G = 0 ; G < r1.n_golds ; G++){
            if(x == r1.golds_x[G] && y == r1.golds_y[G]){
                // the random location overlaps with a gold
                overlap = 1;
            }
        }
        
        if(!overlap){
            (*address_rooms_this_level)[which_room1].trap_x = x;
            (*address_rooms_this_level)[which_room1].trap_y = y;
            k1++;
        }
    }
    int k2 = 0;
    while (k2 < 1){
        int x = rand() % (x_south2 - x_north2 - 3) + x_north2 + 2;
        int y = rand() % (y_east2 - y_west2 - 3) + y_west2 + 2;

        int overlap = 0;
        for (int P = 0 ; P < 3 ; P++){
            if(x == r2.pillars_x[P] && y == r2.pillars_y[P]){
                // the random location overlaps with a pillar
                overlap = 1;
            }
        }
        for (int F = 0 ; F < r2.n_foods ; F++){
            if(x == r2.foods_x[F] && y == r2.foods_y[F]){
                // the random location overlaps with a food
                overlap = 1;
            }
        }
        for (int G = 0 ; G < r2.n_golds ; G++){
            if(x == r2.golds_x[G] && y == r2.golds_y[G]){
                // the random location overlaps with a gold
                overlap = 1;
            }
        }
        
        if(!overlap){
            (*address_rooms_this_level)[which_room2].trap_x = x;
            (*address_rooms_this_level)[which_room2].trap_y = y;
            k2++;
        }
    }
    int k3 = 0;
    while (k3 < 1){
        int x = rand() % (x_south3 - x_north3 - 3) + x_north3 + 2;
        int y = rand() % (y_east3 - y_west3 - 3) + y_west3 + 2;

        int overlap = 0;
        for (int P = 0 ; P < 3 ; P++){
            if(x == r3.pillars_x[P] && y == r3.pillars_y[P]){
                // the random location overlaps with a pillar
                overlap = 1;
            }
        }
        for (int F = 0 ; F < r3.n_foods ; F++){
            if(x == r3.foods_x[F] && y == r3.foods_y[F]){
                // the random location overlaps with a food
                overlap = 1;
            }
        }
        for (int G = 0 ; G < r3.n_golds ; G++){
            if(x == r3.golds_x[G] && y == r3.golds_y[G]){
                // the random location overlaps with a gold
                overlap = 1;
            }
        }
        
        if(!overlap){
            (*address_rooms_this_level)[which_room3].trap_x = x;
            (*address_rooms_this_level)[which_room3].trap_y = y;
            k3++;
        }
    }
    
}

// function to add black gold to room index 0
void add_black_gold(room** address_rooms_this_level , int n_rooms){ // first food, then gold
    srand(time(NULL));
    
    room r1 = (*address_rooms_this_level)[0];
    int x_north1 = r1.corner.x;
    int x_south1 = r1.corner.x + r1.length - 1;
    int y_west1 = r1.corner.y;
    int y_east1 = r1.corner.y + r1.width - 1;
    r1.black_gold = rand() % 2;
    (*address_rooms_this_level)[0].black_gold = r1.black_gold;

    int k = 0 ;
    while (k < r1.black_gold ){
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
        for (int G = 0 ; G < r1.n_golds ; G++){
            if(x == r1.golds_x[G] && y == r1.golds_y[G]){
                // the random location overlaps with a gold
                overlap = 1;
            }
        }
        

        if(!overlap){
            (*address_rooms_this_level)[0].black_gold_x = x;
            (*address_rooms_this_level)[0].black_gold_y = y;

            k++;
        }

    }
        

}

// function to add golds to room 
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
    int which_food_type[10] = {0 , 0 , 0 , 0 , 1 , 1 , 2 , 2 , 3 , 3};
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
                (*address_rooms_this_level)[i].food_types[k] = which_food_type[rand() % 10];
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
    // initscr();
    // nodelay(stdscr, TRUE);
    // noecho();
    // cbreak();
    // curs_set(FALSE);
    // start_color(); 
    // srand(time(NULL));  
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
            // for (int roo = 0 ; roo < n_rooms_level ; roo ++){
            //     print_room(rooms_of_all_levels[level_num - 1] + roo);
            // }
            // print_corridors((*address_corridors_of_all_levels)[level_num - 1] , *ptr_corr_count);
            // sleep(1);
            // refresh();
        } 
        
        else{ // end.y = start.y
            for (int J = 0 ; (start.x  + J != end.x + sign_delta_x) ; J += sign_delta_x){
                (*address_corridors_of_all_levels)[level_num - 1][*ptr_corr_count + abs(J)].x = start.x + J ;
                (*address_corridors_of_all_levels)[level_num - 1][*ptr_corr_count + abs(J)].y = start.y;
            }
            *ptr_corr_count += corr_length;
            // for (int roo = 0 ; roo < n_rooms_level ; roo ++){
            //     print_room(rooms_of_all_levels[level_num - 1] + roo);
            // }
            // print_corridors((*address_corridors_of_all_levels)[level_num - 1] , *ptr_corr_count);
            // sleep(1);
            // refresh();
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
 
void build_corr2(int n_rooms_level, position*** address_corridors_of_all_levels, room ** rooms_of_all_levels, int level_num, int* ptr_corr_count) {
    int x_moves[8] = {-1, +1, +0, +0, -1, -1, +1, +1}; // up, down, right, left, up-right, up-left, down-right, down-left
    int y_moves[8] = {+0, +0, +1, -1, +1, -1, +1, -1};

    for (int i = 0; i < n_rooms_level - 1; i++) {
        if (i < 0 || i >= n_rooms_level) continue;
        
        position start; // ROOM INDEX i
        position end;   // ROOM INDEX i + 1
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
        int sign_delta_x = (delta_x < 0) ? -1 : 1;
        int delta_y = end.y - start.y;
        int corr_length = abs(delta_x) + abs(delta_y) + 1;
        int y_break;
        int sign_delta_y = (delta_y < 0) ? -1 : (delta_y > 0) ? 1 : 0;

        // Adjust y_break calculation to avoid negative indices
        if (delta_y != 0) {
            if(i > 0 && rooms_of_all_levels[level_num - 1][i - 1].corner.y + rooms_of_all_levels[level_num - 1][i - 1].width - 1 >= rooms_of_all_levels[level_num - 1][i].corner.y + rooms_of_all_levels[level_num - 1][i].width - 1) {
                if(i <= n_rooms_level - 3 && (rooms_of_all_levels[level_num - 1][i + 2].corner.y < rooms_of_all_levels[level_num - 1][i + 1].corner.y) ){
                    y_break = start.y;
                }
                else{
                    y_break = rand() % (abs(end.y - (rooms_of_all_levels[level_num - 1][i - 1].corner.y + rooms_of_all_levels[level_num - 1][i - 1].width))) + rooms_of_all_levels[level_num - 1][i - 1].corner.y + rooms_of_all_levels[level_num - 1][i - 1].width + 1;
                }
            }
            else {
                if(i <= n_rooms_level - 3 && (rooms_of_all_levels[level_num - 1][i + 2].corner.y < rooms_of_all_levels[level_num - 1][i + 1].corner.y) ){
                    y_break = start.y;
                    // y_break = rand() % abs(rooms_of_all_levels[level_num - 1][i + 2].corner.y - start.y) + start.y;
                }
                else{
                    y_break = rand() % abs(delta_y) + start.y;
                }
            }
            if (y_break == end.y || y_break == end.y + 1) {
                y_break--;
            }

            if (end.x > rooms_of_all_levels[level_num - 1][i - 1].corner.x && rooms_of_all_levels[level_num - 1][i - 1].corner.y + rooms_of_all_levels[level_num - 1][i - 1].width - 1 >= start.y) {
                y_break = end.y - 1;
            }
            for (int K = 0; start.y + K != y_break + sign_delta_y; K += sign_delta_y) {
                if ((*ptr_corr_count + abs(K)) < MAX_CORR) {
                    (*address_corridors_of_all_levels)[level_num - 1][*ptr_corr_count + abs(K)].x = start.x;
                    (*address_corridors_of_all_levels)[level_num - 1][*ptr_corr_count + abs(K)].y = start.y + K;
                }
            }
            for (int J = 0; (start.x + J != end.x + 2 * sign_delta_x); J += sign_delta_x) {
                if ((*ptr_corr_count + abs(y_break - start.y) + abs(J) + 1) < MAX_CORR) {
                    (*address_corridors_of_all_levels)[level_num - 1][*ptr_corr_count + abs(y_break - start.y) + abs(J) + 1].x = (start.x + sign_delta_x) + J;
                    (*address_corridors_of_all_levels)[level_num - 1][*ptr_corr_count + abs(y_break - start.y) + abs(J) + 1].y = y_break;
                }
            }
            for (int L = 0; (y_break + L != end.y + sign_delta_y); L += sign_delta_y) {
                if ((*ptr_corr_count + abs(y_break - start.y) + abs(delta_x) + 1 + abs(L)) < MAX_CORR) {
                    (*address_corridors_of_all_levels)[level_num - 1][*ptr_corr_count + abs(y_break - start.y) + abs(delta_x) + 1 + abs(L)].x = end.x;
                    (*address_corridors_of_all_levels)[level_num - 1][*ptr_corr_count + abs(y_break - start.y) + abs(delta_x) + 1 + abs(L)].y = y_break + L;
                }
            }
            *ptr_corr_count += corr_length;
            if (*ptr_corr_count > MAX_CORR) break;
        } else { 
            for (int J = 0; (start.x + J != end.x + sign_delta_x); J += sign_delta_x) {
                if ((*ptr_corr_count + abs(J)) < MAX_CORR) {
                    (*address_corridors_of_all_levels)[level_num - 1][*ptr_corr_count + abs(J)].x = start.x + J;
                    (*address_corridors_of_all_levels)[level_num - 1][*ptr_corr_count + abs(J)].y = start.y;
                }
            }
            *ptr_corr_count += corr_length;
        }
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
                // y1 = rand() % (y_west2 - y_west1) + y_west1 + 1;
                if(y_west2 > y_west1 + 1){
                    y1 = rand() % (y_west2 - y_west1) + y_west1 + 1;
                }
                else{
                    if(y_east2 < y_east1){
                        y1 = rand() % (y_east2 - y_west1 - 1) + y_west1 + 1;
                    }
                    else{
                        y1 = rand() % (y_east1 - y_west1 - 1) + y_west1 + 1;
                    }
                    // y1 = rand() % (y_west2 + (int)(2*r2.width/3) - y_west1) + y_west1 + 1;
                }
                wall_2 = 1; // south
                x2 = x_south2;
                int attempts = 0;
                printf("begin do/while door... \n");
                do{
                    y2 = rand() % (r2.width - 1) + y_west2;
                    attempts++;
                    if (attempts > 100) { // Safety mechanism to break out of the loop
                        mvprintw(LINES/2 , COLS/2 - strlen("In making doors, loop safety break to prevent infinite loop. Quit and try again")/2, "In making doors, loop safety break to prevent infinite loop. Quit and try again\n\n\n\n");
                        sleep(2);
                        refresh();
                        break;
                    }
                } while(y2 < y1);
                printf("DONE do/while door... \n");
            }
            else if(r2.corner.x > r1.corner.x + r1.length){
                wall_1 = 1; // south
                x1 = x_south1;
                if(y_west2 > y_west1 + 1){
                    y1 = rand() % (y_west2 - y_west1) + y_west1 + 1;
                }
                else{
                    if(y_east2 < y_east1){
                        y1 = rand() % (y_east2 - y_west1 - 1) + y_west1 + 1;
                    }
                    else{
                        y1 = rand() % (y_east1 - y_west1 - 1) + y_west1 + 1;
                    }
                    // y1 = rand() % (y_west2 + (int)(2*r2.width/3) - y_west1) + y_west1 + 1;
                }
                wall_2 = 0; // north
                x2 = x_north2;
                int attempts = 0;
                printf("begin do/while door... \n");
                do{
                    y2 = rand() % (r2.width - 1) + y_west2;
                    attempts++;
                    if (attempts > 100) { // Safety mechanism to break out of the loop
                        mvprintw(LINES/2 , COLS/2 - strlen("In making doors, loop safety break to prevent infinite loop. Quit and try again")/2, "In making doors, loop safety break to prevent infinite loop. Quit and try again\n\n\n\n");
                        sleep(2);
                        refresh();
                        break;
                    }
                } while(y2 < y1);
                printf("DONE do/while door... \n");

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

void print_room_even_if_hidden(room* Room){


    if (Room == NULL) {
    printf("Error: Room is NULL before print_room\n");
    return;
    }
    // printf("Printing room at position (%d, %d)\n", Room->corner.x, Room->corner.y); // Debug print
    // setlocale(LC_ALL, "");
    start_color();
    // attron(COLOR_BLACK);
    // attron(COLOR_BLACK);
    position ul_corner;
    ul_corner.x = Room->corner.x;
    ul_corner.y = Room->corner.y;

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
        init_pair(0 , COLOR_WHITE , COLOR_BLACK); // regular
        init_pair(1 , COLOR_WHITE , COLOR_BLACK); 
        init_pair(35, 161 , COLOR_BLACK); // battle
        init_pair(2 , 53 , COLOR_BLACK); // enchant
        init_color(70, 1000 , 1000 , 0); // treasure room
        init_pair(33, 70 , COLOR_BLACK); // treasure room
        // init_pair(3 , COLOR_YELLOW , COLOR_BLACK); 
        init_pair(4 , COLOR_BLUE , COLOR_BLACK); 

        init_color(76, 990 , 570 , 800); // 8 for normal/rotten food
        init_pair(8, 76 , COLOR_BLACK); // 8 for  normal/rotten food
        init_color(109, 590 , 400 , 800); // 109 for magical food
        init_pair(109, 109 , COLOR_BLACK); // 109 for magical food
        init_color(81, 1000 , 200 , 890); // 81 for ideal food
        init_pair(81, 81 , COLOR_BLACK); // 81 for ideal food

        init_color(77, 1000 , 1000 , 0); // for gold
        init_pair(15, 77 , COLOR_BLACK); // for gold
        init_color(78, 700, 700, 0); // for black gold
        init_pair(16, 78 , COLOR_BLACK); // for black gold

        if(Room->type == 3){
            attron(COLOR_PAIR(33));
        }
        else if (Room->type == 1){
            attron(COLOR_PAIR(35));
        }
        else{
            attron(COLOR_PAIR(Room->type));
        }
        for (int y = ul_corner.y + 1; y < ul_corner.y + Room->width - 1 ; y++){
            for (int x = ul_corner.x + 1 ; x < ul_corner.x + Room->length - 1 ; x++){
                mvprintw(x , y , "%c" , floor);
            }
        }
        if(Room->trap_x){ // cannot be zero if there is trap in room
            if(Room->trap_visibility){
                mvprintw(Room->trap_x , Room->trap_y , "^");
            }
        }
        if(Room->type == 3){
            attroff(COLOR_PAIR(33));
        }
        else if (Room->type == 1){
            attroff(COLOR_PAIR(35));
        }
        else{
            attroff(COLOR_PAIR(Room->type));
        }

        if(Room->type != 3){ // Treasure room is empty of these!
            // pillars
            for (int i = 0 ; i < 3 ; i++){   
                mvprintw(Room->pillars_x[i],  Room->pillars_y[i] , "O");
            }

            if (Room->type !=2 ){// Enchant room is empty of these!
                // food
                for (int i = 0 ; i < Room->n_foods ; i++){  
                    if(Room->food_types[i] == 0 || Room->food_types[i] == 3){
                        attron(COLOR_PAIR(8)); // normal or rotten
                    }
                    else if(Room->food_types[i] == 1){
                        attron(COLOR_PAIR(81)); // ideal
                    }
                    else if(Room->food_types[i] == 2){
                        attron(COLOR_PAIR(109)); // magical
                    } 
                    if(Room->picked_foods[i] == 0){
                        
                        mvprintw(Room->foods_x[i],  Room->foods_y[i] , "f" );

                    }
                    if(Room->food_types[i] == 0 || Room->food_types[i] == 3){
                        attroff(COLOR_PAIR(8)); // normal or rotten
                    }
                    else if(Room->food_types[i] == 1){
                        attroff(COLOR_PAIR(81)); // ideal
                    }
                    else if(Room->food_types[i] == 2){
                        attroff(COLOR_PAIR(109)); // magical
                    }
                }

                // gold
                attron(COLOR_PAIR(15));
                for (int i = 0 ; i < Room->n_golds ; i++){   
                    if(Room->picked_golds[i] == 0){
                        mvprintw(Room->golds_x[i],  Room->golds_y[i] , "g");
                    }
                }
                attroff(COLOR_PAIR(15));

                // black gold
                attron(COLOR_PAIR(16));
                if(Room->black_gold == 1){
                    mvprintw(Room->black_gold_x,  Room->black_gold_y , "G");
                }
                attroff(COLOR_PAIR(16));
            }

            // weapons
            init_pair(239 , 239 , COLOR_BLACK);
            attron(COLOR_PAIR(239) | A_BOLD);
            for (int Weap = 0 ; Weap < 5 ; Weap++){
                if(Room->weapons[Weap]){

                    if(Weap == 0){
                        // mace
                        mvprintw(Room->weapons_x[Weap] , Room->weapons_y[Weap] , "m");
                    }
                    else if(Weap == 1){
                        // dagger
                        mvprintw(Room->weapons_x[Weap] , Room->weapons_y[Weap] , "d");
                    }
                    else if(Weap == 2){
                        // wand
                        mvprintw(Room->weapons_x[Weap] , Room->weapons_y[Weap] , "w");
                    }
                    else if(Weap == 3){
                        // arrow
                        mvprintw(Room->weapons_x[Weap] , Room->weapons_y[Weap] , "a");
                    }
                    else if(Weap == 4){
                        // sword
                        mvprintw(Room->weapons_x[Weap] , Room->weapons_y[Weap] , "s");
                    }
                }
            }
            attroff(COLOR_PAIR(239) | A_BOLD);


            // spells
            init_pair(47 , 47 , COLOR_BLACK); // health
            init_pair(45 , 45 , COLOR_BLACK); // speed
            init_pair(209 , 209 , COLOR_BLACK); // damage
            for (int Weap = 0 ; Weap < 3 ; Weap++){
                if(Room->spells[Weap] != 0){

                    if(Weap == 0){
                        // health
                        attron(COLOR_PAIR(47) | A_BOLD);
                        mvprintw(Room->spells_x[Weap] , Room->spells_y[Weap] , "H");
                        attroff(COLOR_PAIR(47) | A_BOLD);
                    }
                    else if(Weap == 1){
                        // speed
                        if(Room->spells_x[Weap] > 1){
                            attron(COLOR_PAIR(45) | A_BOLD);
                            mvprintw(Room->spells_x[Weap] , Room->spells_y[Weap] , "$");
                            attroff(COLOR_PAIR(45) | A_BOLD);
                        }
                    }
                    else if(Weap == 2){
                        // damage
                        attron(COLOR_PAIR(209) | A_BOLD);
                        mvprintw(Room->spells_x[Weap] , Room->spells_y[Weap] , "!");
                        attroff(COLOR_PAIR(209) | A_BOLD);
                    }

                }
            }

        }
        if(Room->enemies[0]){
            attron(COLOR_PAIR(160) | A_ITALIC);
            mvprintw(Room->enemies_x[0],  Room->enemies_y[0] , "D");

        }
        if(Room->enemies[1]){
            mvprintw(Room->enemies_x[1],  Room->enemies_y[1] , "F");

        }
        if(Room->enemies[2]){
            mvprintw(Room->enemies_x[2],  Room->enemies_y[2] , "G");

        }
        if(Room->enemies[3]){
            mvprintw(Room->enemies_x[3],  Room->enemies_y[3] , "S");

        }
        if(Room->enemies[4]){
            mvprintw(Room->enemies_x[4],  Room->enemies_y[4] , "U");

        }
        attroff(COLOR_PAIR(160) | A_ITALIC);

        // staircase
        if (Room->room_number == 4){
            // room index 3 (STAIRS!)
            mvprintw(Room->stair_x , Room->stair_y , "<");
        }
        
        // doors
        if (Room->room_number == 1){
            mvprintw(Room->doors_x[0],  Room->doors_y[0] , "+");
        }
        else{
            for (int i = 0 ; i < 2 ; i++){
                mvprintw(Room->doors_x[i],  Room->doors_y[i] , "+");
            }  
        }

}

void print_room(room *Room){ 

    if (Room == NULL) {
    printf("Error: Room is NULL before print_room\n");
    return;
    }
    // printf("Printing room at position (%d, %d)\n", Room->corner.x, Room->corner.y); // Debug print
    // setlocale(LC_ALL, "");
    start_color();
    // attron(COLOR_BLACK);
    // attron(COLOR_BLACK);
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
        init_pair(0 , COLOR_WHITE , COLOR_BLACK); // regular
        init_pair(35, 161 , COLOR_BLACK); // battle
        init_pair(1 , COLOR_WHITE , COLOR_BLACK); 
        init_pair(2 , 53 , COLOR_BLACK); // enchant
        init_color(70, 1000 , 1000 , 0); // treasure room
        init_pair(33, 70 , COLOR_BLACK); // treasure room
        // init_pair(3 , COLOR_YELLOW , COLOR_BLACK); 
        init_pair(4 , COLOR_BLUE , COLOR_BLACK); 
        init_color(76, 990 , 570 , 800); // 8 for normal/rotten food
        init_pair(8, 76 , COLOR_BLACK); // 8 for  normal/rotten food
        init_color(109, 590 , 400 , 800); // 109 for magical food
        init_pair(109, 109 , COLOR_BLACK); // 109 for magical food
        init_color(81, 1000 , 200 , 890); // 81 for ideal food
        init_pair(81, 81 , COLOR_BLACK); // 81 for ideal food
        init_color(77, 1000 , 1000 , 0); // for gold
        init_pair(15, 77 , COLOR_BLACK); // for gold
        init_color(78, 700, 700, 0); // for black gold
        init_pair(16, 78 , COLOR_BLACK); // for black gold
        init_pair(160, 160 , COLOR_BLACK); // for black gold

        if(Room->type == 3){
            attron(COLOR_PAIR(33));
        }
        else if (Room->type == 1){
            attron(COLOR_PAIR(35));
        }
        else{
            attron(COLOR_PAIR(Room->type));
        }
        for (int y = ul_corner.y + 1; y < ul_corner.y + Room->width - 1 ; y++){
            for (int x = ul_corner.x + 1 ; x < ul_corner.x + Room->length - 1 ; x++){
                mvprintw(x , y , "%c" , floor);
            }
        }
        if(Room->trap_x){ // cannot be zero if there is trap in room
            if(Room->trap_visibility){
                mvprintw(Room->trap_x , Room->trap_y , "^");
            }
        }
        if(Room->type == 3){
            attroff(COLOR_PAIR(33));
        }
        else if (Room->type == 1){
            attroff(COLOR_PAIR(35));
        }
        else{
            attroff(COLOR_PAIR(Room->type));
        }
        attroff(COLOR_PAIR(Room->type));

        if(Room->type != 3){ // Treasure room is empty of these!
            // pillars
            for (int i = 0 ; i < 3 ; i++){   
                mvprintw(Room->pillars_x[i],  Room->pillars_y[i] , "O");
            }

            if (Room->type !=2 ){// Enchant room is empty of these!
                // food
                for (int i = 0 ; i < Room->n_foods ; i++){  
                    if(Room->food_types[i] == 0 || Room->food_types[i] == 3){
                        attron(COLOR_PAIR(8)); // normal or rotten
                    }
                    else if(Room->food_types[i] == 1){
                        attron(COLOR_PAIR(81)); // ideal
                    }
                    else if(Room->food_types[i] == 2){
                        attron(COLOR_PAIR(109)); // magical
                    } 
                    if(Room->picked_foods[i] == 0){
                        
                        mvprintw(Room->foods_x[i],  Room->foods_y[i] , "f" );

                    }
                    if(Room->food_types[i] == 0 || Room->food_types[i] == 3){
                        attroff(COLOR_PAIR(8)); // normal or rotten
                    }
                    else if(Room->food_types[i] == 1){
                        attroff(COLOR_PAIR(81)); // ideal
                    }
                    else if(Room->food_types[i] == 2){
                        attroff(COLOR_PAIR(109)); // magical
                    }
                }

                // gold
                attron(COLOR_PAIR(15));
                for (int i = 0 ; i < Room->n_golds ; i++){   
                    if(Room->picked_golds[i] == 0){
                        mvprintw(Room->golds_x[i],  Room->golds_y[i] , "g");
                    }
                }
                attroff(COLOR_PAIR(15));

                // black gold
                attron(COLOR_PAIR(16));
                if(Room->black_gold == 1){
                    mvprintw(Room->black_gold_x,  Room->black_gold_y , "G");
                }
                attroff(COLOR_PAIR(16));
            }

            // weapons
            init_pair(239 , 239 , COLOR_BLACK);
            attron(COLOR_PAIR(239) | A_BOLD);
            for (int Weap = 0 ; Weap < 5 ; Weap++){
                if(Room->weapons[Weap]){

                    if(Weap == 0){
                        // mace
                        mvprintw(Room->weapons_x[Weap] , Room->weapons_y[Weap] , "m");
                    }
                    else if(Weap == 1){
                        // dagger
                        mvprintw(Room->weapons_x[Weap] , Room->weapons_y[Weap] , "d");
                    }
                    else if(Weap == 2){
                        // wand
                        mvprintw(Room->weapons_x[Weap] , Room->weapons_y[Weap] , "w");
                    }
                    else if(Weap == 3){
                        // arrow
                        mvprintw(Room->weapons_x[Weap] , Room->weapons_y[Weap] , "a");
                    }
                    else if(Weap == 4){
                        // sword
                        mvprintw(Room->weapons_x[Weap] , Room->weapons_y[Weap] , "s");
                    }
                }
            }
            attroff(COLOR_PAIR(239) | A_BOLD);


            // spells
            init_pair(47 , 47 , COLOR_BLACK); // health
            init_pair(45 , 45 , COLOR_BLACK); // speed
            init_pair(209 , 209 , COLOR_BLACK); // damage
            for (int Weap = 0 ; Weap < 3 ; Weap++){
                if(Room->spells[Weap] != 0){

                    if(Weap == 0){
                        // health
                        attron(COLOR_PAIR(47) | A_BOLD);
                        mvprintw(Room->spells_x[Weap] , Room->spells_y[Weap] , "H");
                        attroff(COLOR_PAIR(47) | A_BOLD);
                    }
                    else if(Weap == 1){
                        // speed
                        if(Room->spells_x[Weap] > 1){
                            attron(COLOR_PAIR(45) | A_BOLD);
                            mvprintw(Room->spells_x[Weap] , Room->spells_y[Weap] , "$");
                            attroff(COLOR_PAIR(45) | A_BOLD);
                        }
                    }
                    else if(Weap == 2){
                        // damage
                        attron(COLOR_PAIR(209) | A_BOLD);
                        mvprintw(Room->spells_x[Weap] , Room->spells_y[Weap] , "!");
                        attroff(COLOR_PAIR(209) | A_BOLD);
                    }

                }
            }

        }
        
        // staircase
        if (Room->room_number == 4){
            // room index 3 (STAIRS!)
            mvprintw(Room->stair_x , Room->stair_y , "<");
        }
        
        // doors
        if (Room->room_number == 1){
            mvprintw(Room->doors_x[0],  Room->doors_y[0] , "+");
        }
        else{
            for (int i = 0 ; i < 2 ; i++){
                mvprintw(Room->doors_x[i],  Room->doors_y[i] , "+");
            }  
        }

        // // enemies
        attron(COLOR_PAIR(160) | A_ITALIC);
        if(Room->enemies[0]){
            attron(COLOR_PAIR(160) | A_ITALIC);
            mvprintw(Room->enemies_x[0],  Room->enemies_y[0] , "D");

        }
        if(Room->enemies[1]){
            attron(COLOR_PAIR(160) | A_ITALIC);
            mvprintw(Room->enemies_x[1],  Room->enemies_y[1] , "F");

        }
        if(Room->enemies[2]){
            attron(COLOR_PAIR(160) | A_ITALIC);
            mvprintw(Room->enemies_x[2],  Room->enemies_y[2] , "G");

        }
        if(Room->enemies[3]){
            attron(COLOR_PAIR(160) | A_ITALIC);
            mvprintw(Room->enemies_x[3],  Room->enemies_y[3] , "S");

        }
        if(Room->enemies[4]){
            attron(COLOR_PAIR(160) | A_ITALIC);
            mvprintw(Room->enemies_x[4],  Room->enemies_y[4] , "U");

        }
        attroff(COLOR_PAIR(160) | A_ITALIC);

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
    int room_types[14] = {0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 2 , 2 , 4 , 4 , 1};

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
        ROOM.hide = 1;
        if (4 == level_num && done_rooms == n_rooms - 1){
            ROOM.type = 3;
        }
        else{
            // int room_types[14] = {0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 2 , 2 , 4 , 4 , 1};
            ROOM.type = room_types[rand() % 14];
        }
        ROOM.length = rand() % (max_length - 6) + 7;
        ROOM.width = rand() % (max_width - 6) + 7;
        if(3 == difficulty){
            ROOM.n_foods = rand() % 3;
        }
        else if(2 == difficulty || 1 == difficulty){
            ROOM.n_foods = rand() % 4;
        }
        if (ROOM.type == 1){
            ROOM.n_foods = 0;
        }

        ROOM.n_golds = rand() % 3;
        if (ROOM.type == 1){
            ROOM.n_golds = 0;
        }

        // no food/gold has been picked yet
        for (int F = 0 ; F < ROOM.n_foods ; F++){
            ROOM.picked_foods[F] = 0;
        }
        for (int G = 0 ; G < ROOM.n_golds ; G++){
            ROOM.picked_golds[G] = 0;
        }

        ROOM.corner.x = rand() % (max_x_for_corner - min_x_for_corner) + min_x_for_corner;
        ROOM.corner.y = rand() % (max_y_for_corner - min_y_for_corner) + min_y_for_corner;
        ROOM.trap_visibility = 0;
        ROOM.trap_x = 0; // initialized: if later a room's trap_x is zero it means no trap in room
        ROOM.trap_y = 0;
        ROOM.stair_x = 0;
        ROOM.stair_y = 0;
        ROOM.black_gold = 0;
        ROOM.black_gold_x = 0;
        ROOM.black_gold_y = 0;
        for (int W = 0 ; W < 5 ; W++){
            ROOM.weapons[W] = 0;
            ROOM.weapons_x[W] = 0;
            ROOM.weapons_y[W] = 0;
        }
        for (int W = 0 ; W < 5 ; W++){
            ROOM.enemies[W] = 0;
            ROOM.weapons_x[W] = 0;
            ROOM.weapons_y[W] = 0;
        }
        for (int S = 0 ; S<3 ;S++){
            ROOM.spells[S] = 0;
            ROOM.spells_x[S] = 0;
            ROOM.spells_y[S] = 0;
        }

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

    sort_rooms((*address_rooms_of_all_levels)[level_num - 1] , n_rooms);
    
    if (1 == level_num){
        (*address_rooms_of_all_levels)[level_num - 1][1].hide = 0; // the player starts from room index 1 (second room)
        // (*address_rooms_of_all_levels)[level_num - 1][0].hide = 0; // the player starts from room index 1 (second room)
    }
    else{
        (*address_rooms_of_all_levels)[level_num - 1][3].hide = 0; // the staircase in all levels
    }

    // adding stair (up left corner of room)
    (*address_rooms_of_all_levels)[level_num - 1][3].stair_x = (*address_rooms_of_all_levels)[level_num - 1][3].corner.x + 1;
    (*address_rooms_of_all_levels)[level_num - 1][3].stair_y = (*address_rooms_of_all_levels)[level_num - 1][3].corner.y + 1;
    
    if ((*address_rooms_of_all_levels)[3][3].type == 3){
        (*address_rooms_of_all_levels)[3][3].type = 0;
        (*address_rooms_of_all_levels)[3][4].type = 3;
    }
    
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