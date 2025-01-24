#ifndef LOG_IN_H
#define LOG_IN_H

////  library : Log In   ////

// Arvin Rasulzadeh
// 403110422

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <ctype.h>
#include <ncurses.h>
#include "new_user.h"
#define Usernames_File "/home/arvin_rsl/Desktop/FOP_Project/Users_Folder/Rogue_Usernames.txt"
#define MAX_SIZE 1000
#include "pregame_menu.h"
#include "entrance_menu.h" // for design

int check_password();
void log_in();
void draw_borders(int);
void draw_title(const char*);

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
void log_in(){
    
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
        pregame_menu(username);
    }
       
    else if (valid_user && valid_pass) {
        clear();
        // draw_title("Log In");
        draw_borders(12);
        mvprintw(LINES / 2, (COLS - strlen("Log in was successful!"))/ 2, "Log in was successful!");
        mvprintw(LINES / 2 + 2, (COLS - strlen("Press any key to proceed"))/ 2, "Press any key to proceed");
        refresh();
        getch();
        pregame_menu(username);
    }
    endwin();
}
// checked :)
#endif
