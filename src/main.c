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
#include "parser.h"

enum command{find, search, load, save, save_prof, recommend, list, eval, test, menu, quit, delete};
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
/*int main(void){
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
    freeProfile(bobo);

    return 0;
} */

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
            loadProfile(arg, database->amount_of_interests);
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
        case quit:
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
            scanf(" %s", arg);
            break;
        case -1:
            scanf(" %d", arg_num);
            break;
    }

    clearBuffer();

    return command_index;
}

/** @fn int scanCommand(char arg[MAX_INPUT_LENGTH], int *arg_num)
 *  @brief Compares the entered string to the command words and returns
 *         the enum command associated with the string
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
    } else if(strcmp(s, "test") == 0){
        c = test;
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















































/* gcc -Iinclude  */



/* ------------------ TEST OF LevelAsValue(char c) -------------------- */
void testLevelAsValueA(CuTest *tc){
    int expected = (int) A;
    char C = 'A', c = 'a';

    CuAssertIntEquals(tc, expected, levelAsValue(C));
    CuAssertIntEquals(tc, expected, levelAsValue(c));
}

void testLevelAsValueB(CuTest *tc){
    int expected = (int) B;
    char C = 'B', c = 'b';

    CuAssertIntEquals(tc, expected, levelAsValue(C));
    CuAssertIntEquals(tc, expected, levelAsValue(c));
}

void testLevelAsValueC(CuTest *tc){
    int expected = (int) C;
    char C = 'C', c = 'c';

    CuAssertIntEquals(tc, expected, levelAsValue(C));
    CuAssertIntEquals(tc, expected, levelAsValue(c));
}

void testLevelAsValueZ(CuTest *tc){
    int expected = (int) Z;
    char C = 'Z', c = 'z';

    CuAssertIntEquals(tc, expected, levelAsValue(C));
    CuAssertIntEquals(tc, expected, levelAsValue(c));
}

CuSuite *testSuiteLevelAsValue(void){
    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testLevelAsValueA);
    SUITE_ADD_TEST(suite, testLevelAsValueB);
    SUITE_ADD_TEST(suite, testLevelAsValueC);
    SUITE_ADD_TEST(suite, testLevelAsValueZ);

    return suite;
}
/* ------------------ END OF LevelAsValue(char c) --------------------- */

/* ------------------ TEST OF validScaleValue(int value, int start, int end) -------------------- */
void testValidScaleValueN5(CuTest *tc){
    int actual = -5, expected = 0;
    CuAssertIntEquals(tc, expected, validScaleValue(actual, 0, 10));
}

void testValidScaleValue0(CuTest *tc){
    int actual = 0, expected = 0;
    CuAssertIntEquals(tc, expected, validScaleValue(actual, 0, 10));
}

void testValidScaleValue5(CuTest *tc){
    int actual = 5, expected = 5;
    CuAssertIntEquals(tc, expected, validScaleValue(actual, 0, 10));
}

void testValidScaleValue10(CuTest *tc){
    int actual = 10, expected = 10;
    CuAssertIntEquals(tc, expected, validScaleValue(actual, 0, 10));
}

void testValidScaleValue15(CuTest *tc){
    int actual = 15, expected = 10;
    CuAssertIntEquals(tc, expected, validScaleValue(actual, 0, 10));
}

CuSuite *testSuiteValidScaleValue(void){
    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testValidScaleValueN5);
    SUITE_ADD_TEST(suite, testValidScaleValue0);
    SUITE_ADD_TEST(suite, testValidScaleValue5);
    SUITE_ADD_TEST(suite, testValidScaleValue10);
    SUITE_ADD_TEST(suite, testValidScaleValue15);

    return suite;
}
/* ------------------ END OF validScaleValue(int value, int start, int end) --------------------- */

/* ------------------ TEST OF convertScale(int value) -------------------- */
void testConvertScale0(CuTest *tc){
    int actual = 0;
    double expected = -1.0;
    CuAssertDblEquals(tc, expected, convertScale(actual), 0.01);
}

void testConvertScale5(CuTest *tc){
    int actual = 5;
    double expected = 0.0;
    CuAssertDblEquals(tc, expected, convertScale(actual), 0.01);
}

void testConvertScale10(CuTest *tc){
    int actual = 0;
    double expected = 1.0;
    CuAssertDblEquals(tc, expected, convertScale(actual), 0.01);
}

CuSuite *testSuiteConvertScale(void){
    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testConvertScale0);
    SUITE_ADD_TEST(suite, testConvertScale5);
    SUITE_ADD_TEST(suite, testConvertScale10);

    return suite;
}
/* ------------------ END OF convertScale(int value) --------------------- */

/* ------------------ TEST OF isQualified(struct profile user, struct education edu) ------------------ */
int baseIsQualified(int user1, int user2, int edu1, int edu2){
    struct profile user = createProfile(0);
    struct education edu = createDefaultEducation(0, 2);

    user.qualifications.subjects[0].level = user1;
    user.qualifications.subjects[1].level = user2;


    edu.required_qualifications.subjects[0].name = 0;
    edu.required_qualifications.subjects[1].name = 1;
    edu.required_qualifications.subjects[0].level = edu1;
    edu.required_qualifications.subjects[1].level = edu2;

    return isQualified(user, edu);
}

/* Tests:
        LL - first is lower, second is lower        -- Expect 0
        LS - first is lower, second is same         -- Expect 0
        LH - first is lower, second is higher       -- Expect 0
        SL - first is same, second is lower         -- Expect 0
        SS - first is same, second is same          -- Expect 1
        SH - first is same, second is higher        -- Expect 1
        HL - first is higher, second is lower       -- Expect 0
        HS - first is higher, second is same        -- Expect 1
        HH - first is higher, second is higher      -- Expect 1
*/
void testIsQualifiedLL(CuTest *tc){
    int expected = 0;
    int u1 = C, u2 = C, e1 = B, e2 = B;

    CuAssertIntEquals(tc, expected, baseIsQualified(u1, u2, e1, e2));
}

void testIsQualifiedLS(CuTest *tc){
    int expected = 0;
    int u1 = C, u2 = B, e1 = B, e2 = B;

    CuAssertIntEquals(tc, expected, baseIsQualified(u1, u2, e1, e2));
}

void testIsQualifiedLH(CuTest *tc){
    int expected = 0;
    int u1 = C, u2 = A, e1 = B, e2 = B;

    CuAssertIntEquals(tc, expected, baseIsQualified(u1, u2, e1, e2));
}

void testIsQualifiedSL(CuTest *tc){
    int expected = 0;
    int u1 = B, u2 = C, e1 = B, e2 = B;

    CuAssertIntEquals(tc, expected, baseIsQualified(u1, u2, e1, e2));
}

void testIsQualifiedSS(CuTest *tc){
    int expected = 1;
    int u1 = B, u2 = B, e1 = B, e2 = B;

    CuAssertIntEquals(tc, expected, baseIsQualified(u1, u2, e1, e2));
}

void testIsQualifiedSH(CuTest *tc){
    int expected = 1;
    int u1 = B, u2 = A, e1 = B, e2 = B;

    CuAssertIntEquals(tc, expected, baseIsQualified(u1, u2, e1, e2));
}

void testIsQualifiedHL(CuTest *tc){
    int expected = 0;
    int u1 = A, u2 = C, e1 = B, e2 = B;

    CuAssertIntEquals(tc, expected, baseIsQualified(u1, u2, e1, e2));
}

void testIsQualifiedHS(CuTest *tc){
    int expected = 1;
    int u1 = A, u2 = B, e1 = B, e2 = B;

    CuAssertIntEquals(tc, expected, baseIsQualified(u1, u2, e1, e2));
}

void testIsQualifiedHH(CuTest *tc){
    int expected = 1;
    int u1 = A, u2 = A, e1 = B, e2 = B;

    CuAssertIntEquals(tc, expected, baseIsQualified(u1, u2, e1, e2));
}

CuSuite *testSuiteIsQualified(void){
    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testIsQualifiedLL);
    SUITE_ADD_TEST(suite, testIsQualifiedLS);
    SUITE_ADD_TEST(suite, testIsQualifiedLH);

    SUITE_ADD_TEST(suite, testIsQualifiedSL);
    SUITE_ADD_TEST(suite, testIsQualifiedSS);
    SUITE_ADD_TEST(suite, testIsQualifiedSH);

    SUITE_ADD_TEST(suite, testIsQualifiedHL);
    SUITE_ADD_TEST(suite, testIsQualifiedHS);
    SUITE_ADD_TEST(suite, testIsQualifiedHH);

    return suite;
}
/* ------------------ END OF isQualified(struct profile user, struct education edu) ------------------- */


/* ----------------- TEST OF parseNumOfEdu(FILE *filereader) ---------------- */
void testParseNumOfEdu(CuTest *tc){
    int expected = 12;
    FILE *file = fopen(DATABASE_PATH, "r");

    CuAssertIntEquals(tc, expected, parseNumOfEdu(file));
}

void testParseNumOfInterests(CuTest *tc){
    int expected = 13;
    FILE *file = fopen(DATABASE_PATH, "r");

    CuAssertIntEquals(tc, expected, parseNumOfInterests(file));
}

CuSuite *testSuiteDatabase(void){
    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testParseNumOfEdu);
    SUITE_ADD_TEST(suite, testParseNumOfInterests);

    return suite;
}
/* ----------------- END  OF parseNumOfEdu(FILE *filereader) ----------------- */

/* ---------------- TEST OF saveProf and loadProf ---------------- */
void testSameName(CuTest *tc){
    struct profile user1, user2;
    user1 = createBobo(13);
    user2 = loadProfile("Bobo", 13);

    CuAssertStrEquals(tc, user1.name, user2.name);
}

void testSameAverageGrade(CuTest *tc){
    struct profile user1, user2;
    user1 = createBobo(13);
    user2 = loadProfile("Bobo", 13);

    CuAssertDblEquals(tc, user1.average, user2.average, 0.01);
}

void testSameLastRecommended(CuTest *tc){
    struct profile user1, user2;
    user1 = createBobo(13);
    user2 = loadProfile("Bobo", 13);

    CuAssertIntEquals(tc, user1.last_recommended, user2.last_recommended);
}

void testSameRegion(CuTest *tc){
    struct profile user1, user2;
    user1 = createBobo(13);
    user2 = loadProfile("Bobo", 13);

    CuAssertIntEquals(tc, user1.location.region, user2.location.region);
}

void testSameRegionImportance(CuTest *tc){
    struct profile user1, user2;
    user1 = createBobo(13);
    user2 = loadProfile("Bobo", 13);

    CuAssertDblEquals(tc, user1.location.region_importance, user2.location.region_importance, 0.01);
}

void testSameSavedList(CuTest *tc){
    int actual = 1, expected = 1, i;
    struct profile user1, user2;
    user1 = createBobo(13);
    user2 = loadProfile("Bobo", 13);
    
    for(i = 0; i < EDUCATION_LIST_LENGTH; i++){
        if(strcmp(user1.saved_educations[i], user2.saved_educations[i]) != 0)
            actual = 0;
    }

    CuAssertIntEquals(tc, expected, actual);
}

void testSameRecommendedList(CuTest *tc){
    int actual = 1, expected = 1, i;
    struct profile user1, user2;
    user1 = createBobo(13);
    user2 = loadProfile("Bobo", 13);
    
    for(i = 0; i < EDUCATION_LIST_LENGTH; i++){
        if(strcmp(user1.recommended_educations[i], user2.recommended_educations[i]) != 0)
            actual = 0;
    }

    CuAssertIntEquals(tc, expected, actual);
}

void testSameInterests(CuTest *tc){
    int actual = 1, expected = 1, i;
    struct profile user1, user2;
    user1 = createBobo(13);
    saveProfile(user1);
    user2 = loadProfile("Bobo", 13);
    
    for(i = 0; i < user1.interests.size; i++){
        if(user1.interests.array[i] != user2.interests.array[i])
            actual = 0;
    }

    CuAssertIntEquals(tc, expected, actual);
}

void testSameAdjustment(CuTest *tc){
    int actual = 1, expected = 1, i;
    struct profile user1, user2;
    user1 = createBobo(13);
    user2 = loadProfile("Bobo", 13);
    
    for(i = 0; i < user1.adjustment_vector.size; i++){
        if(user1.adjustment_vector.array[i] != user2.adjustment_vector.array[i])
            actual = 0;
    }

    CuAssertIntEquals(tc, expected, actual);
}

CuSuite *testSuiteProfile(void){
    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testSameName);
    SUITE_ADD_TEST(suite, testSameAverageGrade);
    SUITE_ADD_TEST(suite, testSameLastRecommended);
    SUITE_ADD_TEST(suite, testSameRegion);
    SUITE_ADD_TEST(suite, testSameRegionImportance);
    SUITE_ADD_TEST(suite, testSameSavedList);
    SUITE_ADD_TEST(suite, testSameRecommendedList);
    SUITE_ADD_TEST(suite, testSameInterests);
    SUITE_ADD_TEST(suite, testSameAdjustment);

    return suite;
}


/* ---------------- END OF saveProf and loadProf ----------------- */
