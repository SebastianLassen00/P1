#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "profile.h"
#include "education.h"
#include "subjects.h"
#include "vector.h" 
#include "CuTest.h"
#include "commands.h"
#include "database.h"
#include "parser.h"

CuSuite *testTestCmd(void);
CuSuite *testSuiteLevelAsValue(void);
CuSuite *testSuiteIsQualified(void);
CuSuite *testSuiteDatabase(void);
CuSuite *testSuiteProfile(void);
CuSuite *testSuiteConvertScale(void);

void RunAllTests(void){
    CuString *outputLAS = CuStringNew();
    CuString *outputIQ = CuStringNew();
    CuString *outputDB = CuStringNew();
    CuString *outputPR = CuStringNew();
    CuString *outputCS = CuStringNew();

    CuSuite* suiteLevelAsValue = CuSuiteNew();
    CuSuite* suiteIsQualified = CuSuiteNew();
    CuSuite* suiteDatabase = CuSuiteNew();
    CuSuite* suiteProfile = CuSuiteNew();
    CuSuite* suiteConvertScale = CuSuiteNew();

    CuSuite *suite = CuSuiteNew();
    /*
    CuSuiteAddSuite(suite, CuGetSuite());
    CuSuiteAddSuite(suite, CuStringGetSuite());
    */

    printf("----------------------------------------------------------------\n");
    printf("TEST OF:   convertScale()\n");
    CuSuiteAddSuite(suiteConvertScale, testSuiteConvertScale());
    CuSuiteRun(suiteConvertScale);
    CuSuiteSummary(suiteConvertScale, outputCS);
    CuSuiteDetails(suiteConvertScale, outputCS);
    printf("%s\n", outputCS->buffer);



    printf("----------------------------------------------------------------\n");
    printf("TEST OF:   levelAsValue()\n");
    CuSuiteAddSuite(suiteLevelAsValue, testSuiteLevelAsValue());
    CuSuiteRun(suiteLevelAsValue);
    CuSuiteSummary(suiteLevelAsValue, outputLAS);
    CuSuiteDetails(suiteLevelAsValue, outputLAS);
    printf("%s\n", outputLAS->buffer);

    printf("----------------------------------------------------------------\n");
    printf("TEST OF:   isQualified()\n");
    CuSuiteAddSuite(suiteIsQualified, testSuiteIsQualified());
    CuSuiteRun(suiteIsQualified);
    CuSuiteSummary(suiteIsQualified, outputIQ);
    CuSuiteDetails(suiteIsQualified, outputIQ);
    printf("%s\n", outputIQ->buffer);

    printf("----------------------------------------------------------------\n");
    printf("TEST OF:   DATABASE\n");
    CuSuiteAddSuite(suiteDatabase, testSuiteDatabase());
    CuSuiteRun(suiteDatabase);
    CuSuiteSummary(suiteDatabase, outputDB);
    CuSuiteDetails(suiteDatabase, outputDB);
    printf("%s\n", outputDB->buffer);

    printf("----------------------------------------------------------------\n");

    printf("----------------------------------------------------------------\n");
    printf("TEST OF:   PROFILE SAVE/LOAD\n");
    CuSuiteAddSuite(suiteProfile, testSuiteProfile());
    CuSuiteRun(suiteProfile);
    CuSuiteSummary(suiteProfile, outputPR);
    CuSuiteDetails(suiteProfile, outputPR);
    printf("%s\n", outputPR->buffer);

    printf("----------------------------------------------------------------\n");

    return;
}


struct profile createBobo(int amount_of_interests){
    struct profile bobo = createProfile(amount_of_interests);
    int i;
    bobo.average = 15.7;
    strcpy(bobo.name, "Bobo");
    bobo.location.region = 4;
    bobo.location.region_importance = 1.0;

    srand(time(NULL));

    for(i = 0; i < amount_of_interests; i++){
        bobo.interests.array[i] = (double) (i % 3 - 1);
    }

    setSubjects(&bobo);
    
    for(i = 0; i < TOTAL_SUBJECTS; i++){
        bobo.qualifications.subjects[i].level = 3;
    }

    

    return bobo;
}

int main(void){
    struct database *db;
    struct education current_education;
    struct profile bobo;
    struct profile user;  

    RunAllTests();


    db = createDatabase("./bin/data/database.txt");

    user = createProfile(db->amount_of_interests);

    //testCmd(&user, db); 

    bobo = createBobo(db->amount_of_interests);

    current_education = recommendCmd(&bobo, db);

    printEducation(current_education); 

    printProfile(bobo); 

    freeDatabase(db);
    freeProfile(bobo);
    freeProfile(user);
    return 0;
}



/* gcc -Iinclude  */


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
    int actual = 10;
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
