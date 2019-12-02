#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "profile.h"
#include "education.h"
#include "subjects.h"
#include "vector.h" 
#include "commands.h"
#include "CuTest.h"
#include "constants.h"

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

