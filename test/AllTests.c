#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "profile.h"
#include "education.h"
#include "subjects.h"
#include "vector.h" 
#include "CuTest.h"
#include "commands.h"

CuSuite *testTestCmd(void);

void RunAllTests(void){
    CuString *output = CuStringNew();
    CuSuite* suite = CuSuiteNew();
    
    /*
    CuSuiteAddSuite(suite, CuGetSuite());
    CuSuiteAddSuite(suite, CuStringGetSuite());
    */

    CuSuiteAddSuite(suite, testTestCmd());

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer); 
}

struct profile createBobo(int amount_of_interests){
    struct profile bobo = createProfile(amount_of_interests);
    int i;
    bobo.average = 15.7;
    strcpy(bobo.name, "Bobo");
    bobo.location.region = 0;
    bobo.location.region_importance = 0.1;

    for(i = 0; i < amount_of_interests; i++){
        bobo.interests.array[i] = 0.0;
    }

    for(i = 0; i < amount_of_interests; i++){
        bobo.qualifications.subjects[i].level = 3;
    }

    setSubjects(&bobo);

    return bobo;
}

int main(void){
    RunAllTests();

    struct database *db = createDatabase("./bin/data/database.txt");

    struct education *current_education = NULL;

    struct profile user = createProfile(db->amount_of_interests);

    testCmd(&user, *db);

    recommendCmd(*db, &user, current_education);

    printProfile(user); 

    printEducation(db->educations[0]);

    freeDatabase(db);
    return 0;
}

