#ifndef NEW_USER_H
#define NEW_USER_H

////  library : Create New User   ////

// Arvin Rasulzadeh
// 403110422

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <ctype.h>
#include <ncurses.h>
#define Usernames_File "/home/arvin_rsl/Desktop/FOP_Project/Users_Folder/Rogue_Usernames.txt"
#define MAX_SIZE 1000
#include "pregame_menu.h"
#include "entrance_menu.h" // for design


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

    snprintf(path, sizeof(path), "/home/arvin_rsl/Desktop/FOP_Project/Users_Folder/%s/user_data.txt", username);

    FILE *user_data_fptr = fopen(path, "w");

    fprintf(user_data_fptr, "username: %s\nemail: %s\npassword: %s\n", username, email, password);

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
void create_user(){
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
        pregame_menu(username);
    }
    endwin();
}
// checked :)

#endif
