#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commands.h"
#include "constants.h"
#include "CuTest.h"
#include "database.h"
#include "education.h"
#include "profile.h"
#include "region.h"
#include "subjects.h"
#include "vector.h" 

enum command{find, save, save_prof, recommend, list, eval, test, menu, quit, delete};
typedef enum command command;

void introduction(void);
void handleCommand(command c, char arg[MAX_INPUT_LENGTH], int arg_num, struct profile *user, 
                   const struct database *database, struct education *current_education);
command scanCommand(char arg[MAX_INPUT_LENGTH], int *arg_num);
command convertCommand(char s[MAX_COMMAND_LENGTH]);
int argType(command c);
struct profile createBobo(int amount_of_interests);

int main(void){
    char arg[MAX_INPUT_LENGTH];
    int arg_num = 0;
    command c = menu;
   
    struct database *database;
    struct profile user;
    struct profile bobo;
    struct education current_education;

    database = createDatabase(DATABASE_PATH);
    user = createProfile(database->amount_of_interests);
    bobo = createBobo(database->amount_of_interests);
    current_education = createDefaultEducation(database->amount_of_interests, database->amount_of_educations);

    introduction();

    while(c != quit){
        handleCommand(c, arg, arg_num, &bobo, database, &current_education);
        c = scanCommand(arg, &arg_num);
    }

    printf("\nThe program will now shut down...\n");

    freeEducation(&current_education);
    freeDatabase(database);
    freeProfile(user);

    return 0;
}


void introduction(void){
    printf("This program was made by: A302\n");
    printf("It is designed to applicants for bachelors in Denmark\n");
    printf("The program will use your input to determine a viable educational path\n");
    printf("All recommendations are only recommendations, and they should not be seen as something final\n");
    printf("\n");
}

void handleCommand(command c, char arg[MAX_INPUT_LENGTH], int arg_num, struct profile *user, 
                   const struct database *database, struct education *current_education){
    switch(c){
        case find:
            *current_education = findCmd(arg, database);
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
        case test:
            testCmd(user, database);
            break;
        case menu:
            menuCmd();
            break;
        case delete:
            deleteCmd(user, arg_num);
    }
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
    } else if(strcmp(s, "delete") == 0){
        c = delete;
    }else{
        c = -1;
    }

    return c;
}

/* 1 is string, -1 is int, 0 is no arg */
int argType(command c){
    return (c == find || c == eval || c == delete) ? ((c == find) ? 1 : -1) : 0;
}















































/* gcc -Iinclude  */

void testLevelAsValue(CuTest *tc){
    char cA = 'A', ca = 'a';
    char cB = 'B', cb = 'b';
    char cC = 'C', cc = 'c';
    char cZ = 'Z', cz = 'z';

    int expectedA = (int) A;
    int expectedB = (int) B;
    int expectedC = (int) C;
    int expectedZ = (int) Z;

    CuAssertIntEquals(tc, expectedA, levelAsValue(cA));
    CuAssertIntEquals(tc, expectedA, levelAsValue(ca));

    CuAssertIntEquals(tc, expectedB, levelAsValue(cB));
    CuAssertIntEquals(tc, expectedB, levelAsValue(cb));

    CuAssertIntEquals(tc, expectedC, levelAsValue(cC));
    CuAssertIntEquals(tc, expectedC, levelAsValue(cc));

    CuAssertIntEquals(tc, expectedZ, levelAsValue(cZ));
    CuAssertIntEquals(tc, expectedZ, levelAsValue(cz));
}

void testValidScaleValue(CuTest *tc){
    int case1 = -5, eCase1 = 0;
    int case2 = 0,  eCase2 = 0;
    int case3 = 5,  eCase3 = 5;
    int case4 = 10, eCase4 = 10;
    int case5 = 15, eCase5 = 10;

    CuAssertIntEquals(tc, eCase1, validScaleValue(case1, 0, 10));
    CuAssertIntEquals(tc, eCase2, validScaleValue(case2, 0, 10));
    CuAssertIntEquals(tc, eCase3, validScaleValue(case3, 0, 10));
    CuAssertIntEquals(tc, eCase4, validScaleValue(case4, 0, 10));
    CuAssertIntEquals(tc, eCase5, validScaleValue(case5, 0, 10));
}

void testConvertScale(CuTest *tc){
    int case0 = 0, case1 = 1, case2 = 2,
        case3 = 3, case4 = 4, case5 = 5,
        case6 = 6, case7 = 7, case8 = 8,
        case9 = 9, case10 = 10;

    double eCase0 = -1.0, eCase1 = -0.8, eCase2 = -0.6,
           eCase3 = -0.4, eCase4 = -0.2, eCase5 = 0.0,
           eCase6 = 0.2, eCase7 = 0.4, eCase8 = 0.6,
           eCase9 = 0.8, eCase10 = 1.0;

    CuAssertDblEquals(tc, eCase0, convertScale(case0), 0.01);
    CuAssertDblEquals(tc, eCase1, convertScale(case1), 0.01);
    CuAssertDblEquals(tc, eCase2, convertScale(case2), 0.01);
    CuAssertDblEquals(tc, eCase3, convertScale(case3), 0.01);
    CuAssertDblEquals(tc, eCase4, convertScale(case4), 0.01);
    CuAssertDblEquals(tc, eCase5, convertScale(case5), 0.01);
    CuAssertDblEquals(tc, eCase6, convertScale(case6), 0.01);
    CuAssertDblEquals(tc, eCase7, convertScale(case7), 0.01);
    CuAssertDblEquals(tc, eCase8, convertScale(case8), 0.01);
    CuAssertDblEquals(tc, eCase9, convertScale(case9), 0.01);
    CuAssertDblEquals(tc, eCase10, convertScale(case10), 0.01);
}




CuSuite *testTestCmd(void){
    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testLevelAsValue);
    SUITE_ADD_TEST(suite, testValidScaleValue);
    SUITE_ADD_TEST(suite, testConvertScale);


    return suite;
}
