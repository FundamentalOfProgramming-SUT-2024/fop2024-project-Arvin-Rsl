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

int check_password();
void log_in();
// already_a_username(): function to check if username exists (using new_user.h library)

// function to check if the password matches the username
int check_password(const char* username, const char* input){
    char path[MAX_SIZE];
    snprintf(path , sizeof(path) , "/home/arvin_rsl/Desktop/FOP_Project/Users_Folder/%s/user_data.txt", username);
    
    FILE* user_data_fptr = fopen(path , "r");

    if (user_data_fptr == NULL){
        printf("user_data file not found for this user\n");
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
        mvprintw(LINES / 2 - 3, COLS / 2 - 10, "Enter Username: ");
        echo();
        getstr(username);
        noecho();
        if (!already_a_username(username)){
            mvprintw(LINES / 2 - 1, COLS / 2 - 20, "Username doesn't exist! Try again");
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
        mvprintw(LINES / 2 - 3, COLS / 2 - 10, "Enter Username: ");
        mvprintw(LINES / 2 - 3, COLS / 2 + 5, username);
        mvprintw(LINES / 2 - 1, COLS / 2 - 10, "Enter Password: ");
        echo();
        getstr(pass);
        noecho();
        if (check_password(username , pass)){
            valid_pass = 1;
            break;
        } 
        else{
            mvprintw(LINES / 2 + 1, COLS / 2 - 15, "Password doesn't match! Try again");
            refresh();
            getch();
        }
    }
       
    if (valid_user && valid_pass) {
        clear();
        mvprintw(LINES / 2, COLS / 2 - 10, "Log in was successful!");
        mvprintw(LINES / 2 + 2, COLS / 2 - 11, "Press any key to proceed");
        refresh();
        getch();
    }
    endwin();
}
// checked :)
#endif
