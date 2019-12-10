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

CuSuite *testTestCmd(void);
CuSuite *testSuiteLevelAsValue(void);
CuSuite *testSuiteIsQualified(void);
CuSuite *testSuiteDatabase(void);
CuSuite *testSuiteProfile(void);

void RunAllTests(void){
    CuString *outputLAS = CuStringNew();
    CuString *outputIQ = CuStringNew();
    CuString *outputDB = CuStringNew();
    CuString *outputPR = CuStringNew();

    CuSuite* suiteLevelAsValue = CuSuiteNew();
    CuSuite* suiteIsQualified = CuSuiteNew();
    CuSuite* suiteDatabase = CuSuiteNew();
    CuSuite* suiteProfile = CuSuiteNew();

    CuSuite *suite = CuSuiteNew();
    /*
    CuSuiteAddSuite(suite, CuGetSuite());
    CuSuiteAddSuite(suite, CuStringGetSuite());
    */

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

/*int main(void){
    struct database *db;
    struct education current_education;
    struct profile bobo;
    struct profile user;  

    RunAllTests();


    db = createDatabase("./bin/data/database.txt");

    user = createProfile(db->amount_of_interests);

    testCmd(&user, db); 

    bobo = createBobo(db->amount_of_interests);

    current_education = recommendCmd(&bobo, db);

    printEducation(current_education); 

    printProfile(bobo); 

    freeDatabase(db);
    freeProfile(bobo);
    freeProfile(user);
    return 0;
}*/

