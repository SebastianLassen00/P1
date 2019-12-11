#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commands.h"
#include "constants.h"
#include "database.h"
#include "education.h"
#include "profile.h"
#include "region.h"
#include "subjects.h"
#include "vector.h" 
#include "parser.h"

enum command{find, search, load, save, save_prof, recommend, list, eval, survey, menu, quit, delete};
typedef enum command command;

void introduction(void);
void handleCommand(command c, char arg[MAX_INPUT_LENGTH], int arg_num, struct profile *user, 
                   const struct database *database, struct education *current_education);
command scanCommand(char arg[MAX_INPUT_LENGTH], int *arg_num);
command convertCommand(char s[MAX_COMMAND_LENGTH]);
int argType(command c);
struct profile createBobo(int amount_of_interests);


/** @fn int main(void)
 *  @brief Takes commands from the user and executes those commands until 
 *               the quit command is entered.
 */
int main(void){
    char arg[MAX_INPUT_LENGTH];
    int arg_num = 0;
    command c = menu;
   
    struct database *database;
    struct profile user;
    struct education current_education;

    database = createDatabase(DATABASE_PATH);
    user = createProfile(database->amount_of_interests);    
    current_education = createDefaultEducation(database->amount_of_interests, database->amount_of_educations);

    introduction();

    while(c != quit){
        handleCommand(c, arg, arg_num, &user, database, &current_education);
        c = scanCommand(arg, &arg_num);
    }

    printf("\nThe program will now shut down...\n");

    freeEducation(&current_education);
    freeDatabase(database);
    freeProfile(user);

    return 0;
} 

/** @fn void introduction(void)
 *  @brief Prints information about the program.
 */
void introduction(void){
    printf("This program was made by: A302\n");
    printf("It is designed to applicants for bachelors in Denmark\n");
    printf("The program will use your input to determine a viable educational path\n");
    printf("All recommendations are only recommendations, and they should not be seen as something final\n");
    printf("\n");
}

/** @fn void handleCommand(command c, char arg[MAX_INPUT_LENGTH], int arg_num, struct profile *user, 
 *                         const struct database *database, struct education *current_education){
 *  @brief Calls the function associated with the given command
 *  @param c The enum command which the user have enterd
 *  @param arg The string argument used by some commands
 *  @param arg_num The integer argument used by som commands
 *  @param user A pointer to the profile struct associated with the user of the program
 *  @param database A pointer to the database
 *  @param current_education A pointer to the last shown education
 */
void handleCommand(command c, char arg[MAX_INPUT_LENGTH], int arg_num, struct profile *user, 
                   const struct database *database, struct education *current_education){
    switch(c){
        case find:
            *current_education = findCmd(arg, database);
            break;
        case search:
            searchCmd(arg, database);
            break;
        case load:
            if(checkProfile(arg) == 1){
                freeProfile(*user);
                *user = loadProfile(arg, database->amount_of_interests);
            } else{
                printf("Profile doesn't exist.\n");
            }
            break;
        case save:
            saveCmd(user, current_education);
            break;
        case save_prof:
            saveProfile(*user);  
            break;
        case recommend:
            *current_education = recommendCmd(user, database);
            break;
        case list:
            listCmd(user);
            break;
        case eval:
            evalCmd(user, current_education, arg_num);
            break;
        case survey:
            surveyCmd(user, database);
            break;
        case menu:
            menuCmd();
            break;
        case delete:
            deleteCmd(user, arg_num);
        case quit:
            break;
        default:
            printf("No command found\n");
            break;
    }
}

/** @fn int scanCommand(char arg[MAX_INPUT_LENGTH], int *arg_num)
 *  @brief Finds valid command and argument
 *  @param arg Output parameter for argument string
 *  @param arg_num Output parameter for argument int
 *  @return The enum command associated with the parameter string
 */
command scanCommand(char arg[MAX_INPUT_LENGTH], int *arg_num){
    char command_string[MAX_COMMAND_LENGTH] = "";
    command command_index; 
    int scan_res;

    scan_res = scanf(" %s", command_string);
    
    command_index = convertCommand(command_string);
    if(scan_res == 0 || command_index == -1){
        return -1;
    }

    switch(argType(command_index)){
        case 1:
            fgets(arg, MAX_INPUT_LENGTH - 1, stdin);
            sscanf(arg, " %[^\n]s", arg);
            break;
        case -1:
            scanf(" %d", arg_num);
            clearBuffer();
            break;
        default:
            clearBuffer();
            break;
    }

    return command_index;
}

/** @fn int scanCommand(char arg[MAX_INPUT_LENGTH], int *arg_num)
 *  @brief Compares the entered string to the command words and returns the enum command associated with the string
 *  @param s A command as a string
 *  @return The enum command associated with the parameter string
 */
command convertCommand(char s[MAX_COMMAND_LENGTH]){
    command c;

    if(strcmp(s, "find") == 0){
        c = find;
    } else if(strcmp(s, "search") == 0){
        c = search;
    } else if(strcmp(s, "load") == 0){
        c = load;
    } else if(strcmp(s, "save") == 0){
        c = save;
    } else if(strcmp(s, "save_prof") == 0){
        c = save_prof;
    } else if(strcmp(s, "recommend") == 0){
        c = recommend;
    } else if(strcmp(s, "list") == 0){
        c = list;
    } else if(strcmp(s, "eval") == 0){
        c = eval;
    } else if(strcmp(s, "survey") == 0){
        c = survey;
    } else if(strcmp(s, "menu") == 0){
        c = menu;
    } else if(strcmp(s, "delete") == 0){
        c = delete;
    } else if(strcmp(s, "quit") == 0){
        c = quit;
    } else{
        c = -1;
    }

    return c;
}

/** @fn int argType(command c)
 *  @brief Determines whether the entered command takes a string argument, 
 *         a integer argument or no argument
 *  @param c An Enum command
 *  @return An integer being 0 if the command takes no argument,
 *          1 if the command takes a string argument and -1 if
 *          it takes an integer argument.
 */
int argType(command c){
    return (c == search || c == find || c == load || c == eval || c == delete) ? ((c == find || c == search || c == load) ? 1 : -1) : 0;
}
