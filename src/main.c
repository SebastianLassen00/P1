#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 10
#define MAX_INPUT_LENGTH (MAX_COMMAND_LENGTH + 100)

enum command{find, save, save_prof, recommend, list, eval, test, menu, exit};
typedef enum command command;

int argType(command c);
void menuCmd(void);
command scanCommand(char arg[MAX_INPUT_LENGTH], int *arg_num);
command convertCommand(char s[MAX_COMMAND_LENGTH]);

int main(void){
    char arg[MAX_INPUT_LENGTH], arg_type[MAX_INPUT_LENGTH];
    int arg_num = 0;
    command c;



    menuCmd();

    do{
        c = scanCommand(arg, &arg_num);
        handleCommand(c);
    } while(c != exit);


    return 0;
}

void handleCommand(command c, char arg[MAX_INPUT_LENGTH], int arg_num, double interests[], subjects, average_grade){
    switch(c){
        case find:
            findCmd(arg);
            break;
        case save:
            saveCmd();
            break;
        case save_prof:
            saveProfCmd();
            break;
        case recommend:
            recommendCmd();
            break;
        case list:
            listCmd();
            break;
        case eval:
            evalCmd(arg_num);
            break;
        case test:
            testCmd(interests, subjects, average_grade);
            break;
        case menu:
            menuCmd();
            break;
    }
}

void menuCmd(void){
    printf("Usable commands: \n");
    printf("  find |arg| -  finds the education passed through the argument |arg|                    \n"
           "  save       -  saves the current education to a seperate list                           \n"
           "  save_prof  -  saves the current user profile to a .txt-file                            \n"
           "  recommend  -  recommend an education using the current profile                         \n"
           "  list       -  lists all the saved educations                                           \n"
           "  eval |arg| -  evaluates the current education using an integer value between 0 and 100 \n"
           "  test       -  tests the users interests and qualifications                             \n"
           "  menu       -  shows a this menu                                                        \n"
           "  exit       -  exits the program                                                        \n");
}

/** @fn int scanCommand(char arg[MAX_INPUT_LENGTH], int *arg_num)
 *    @brief Finds valid command and argument
 *    @param arg Output parameter for argument string
 *    @param arg_num Output parameter for argument int
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
            scanf(" %s", arg);
            break;
        case -1:
            scanf(" %d", arg_num);
            break;
    }

    clearBuffer();

    return command_index;
}

/*    Outputs enum value if command, else -1 */
command convertCommand(char s[MAX_COMMAND_LENGTH]){
    command c;

    if(strcmp(s, "find") == 0){
        c = find;
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
    } else if(strcmp(s, "test") == 0){
        c = test;
    } else if(strcmp(s, "menu") == 0){
        c = menu;
    } else{
        c = -1;
    }

    return c;
}

/* 1 is string, -1 is int, 0 is no arg */
int argType(command c){
    return (c == find || c == eval) ? ((c == find) ? 1 : -1) : 0;
}




/* Commands:
    find (1 arg, uddannelse)
    save (0 arg)
    save_prof (0 arg)
    recommend (0 arg) 
    list (0 arg)
    eval (1 arg, grade)
    test (0 arg)
    menu (0 arg)

    Low-prio
    load (1 arg)
*/