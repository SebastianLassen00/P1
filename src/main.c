#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "profile.h"
#include "education.h"
#include "subjects.h"
#include "vector.h" 
#include "commands.h"
#include "CuTest.h"

#define MAX_COMMAND_LENGTH 10
#define MAX_INPUT_LENGTH (MAX_COMMAND_LENGTH + 100)


enum command{find, save, save_prof, recommend, list, eval, test, menu, quit};
typedef enum command command;

/*int main(void){
    char arg[MAX_INPUT_LENGTH], arg_type[MAX_INPUT_LENGTH];
    int arg_num = 0, number_of_educations;
    command c;
    struct education *educations, currentEducation;
    struct profile user;
    struct qualifications subjects;
    char **

    menuCmd();

    do{
        c = scanCommand(arg, &arg_num);
        handleCommand(c, arg, arg_num, user, subjects, educations, 
                      number_of_educations, &currentEducation);
    } while(c != quit);


    return 0;
}*/


/* gcc -Iinclude  */

void testLevelAsValue(CuSuite *tc){
    char cA = 'A', ca = 'a';
    char cB = 'B', cb = 'b';
    char cC = 'C', cc = 'c';
    char cZ = 'Z', cz = 'z';

    int expectedA = (int) A;
    int expectedB = (int) B;
    int expectedC = (int) C;
    int expectedZ = (int) Z;

    CuAssertIntEquals(tc, expectedA, cA);
    CuAssertIntEquals(tc, expectedA, ca);

    CuAssertIntEquals(tc, expectedB, cB);
    CuAssertIntEquals(tc, expectedB, cb);

    CuAssertIntEquals(tc, expectedC, cC);
    CuAssertIntEquals(tc, expectedC, cc);

    CuAssertIntEquals(tc, expectedZ, cZ);
    CuAssertIntEquals(tc, expectedZ, cz);
}

void testValidScaleValue(CuSuite *tc){
    int case1 = -5, eCase1 = 0;
    int case2 = 0,  eCase2 = 0;
    int case3 = 5,  eCase3 = 5;
    int case4 = 10, eCase4 = 10;
    int case5 = 15, eCase5 = 10;

    CuAssertIntEquals(tc, eCase1, case1);
    CuAssertIntEquals(tc, eCase2, case2);
    CuAssertIntEquals(tc, eCase3, case3);
    CuAssertIntEquals(tc, eCase4, case4);
    CuAssertIntEquals(tc, eCase5, case5);
}

void testConvertScale(CuSuite *tc){
    int case0 = 0, case1 = 1, case2 = 2,
        case3 = 3, case4 = 4, case5 = 5,
        case6 = 6, case7 = 7, case8 = 8,
        case9 = 9, case10 = 10;

    double eCase0 = -1.0, eCase1 = -0.8, eCase2 = -0.6,
           eCase3 = -0.4, eCase4 = -0.2, eCase5 = 0.0,
           eCase6 = 0.2, eCase7 = 0.4, eCase8 = 0.6,
           eCase9 = 0.8, eCase10 = 1.0;

    CuAssertDblEquals(tc, eCase0, convertScale(case0));
    CuAssertDblEquals(tc, eCase1, convertScale(case1));
    CuAssertDblEquals(tc, eCase2, convertScale(case2));
    CuAssertDblEquals(tc, eCase3, convertScale(case3));
    CuAssertDblEquals(tc, eCase4, convertScale(case4));
    CuAssertDblEquals(tc, eCase5, convertScale(case5));
    CuAssertDblEquals(tc, eCase6, convertScale(case6));
    CuAssertDblEquals(tc, eCase7, convertScale(case7));
    CuAssertDblEquals(tc, eCase8, convertScale(case8));
    CuAssertDblEquals(tc, eCase9, convertScale(case9));
    CuAssertDblEquals(tc, eCase10, convertScale(case10));
}




CuSuite *testTestCmd(void){
    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testLevelAsValue);
    SUITE_ADD_TEST(suite, testValidScaleValue);
    SUITE_ADD_TEST(suite, testConvertScale);


    return suite;
}




































void handleCommand(command c, char arg[MAX_INPUT_LENGTH], int arg_num, 
                   struct profile user, struct qualifications subjects,
                   struct education *educations, int number_of_educations,
                   struct education *currentEducation){
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
            recommendCmd(educations, user, currentEducation);
            break;
        case list:
            listCmd();
            break;
        case eval:
            evalCmd(arg_num);
            break;
        case test:
            testCmd(user, subjects);
            break;
        case menu:
            menuCmd();
            break;
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