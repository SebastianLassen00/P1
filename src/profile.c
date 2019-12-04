#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "profile.h"
#include "education.h"
#include "subjects.h"
#include "vector.h" 
#include "commands.h"

struct profile createProfile(int number_of_interests){
    struct profile profile;
    int i;

    profile.interests = createVector(number_of_interests);
    profile.adjustment_vector = createVector(number_of_interests);
    profile.qualifications = createQualifications(TOTAL_SUBJECTS);
    profile.average = 0.0;
    profile.location.region = 0;
    profile.location.region_importance = 0;
    profile.last_recommended = 0;

    profile.adjustment_vector.array[0] = 0.0001;

    for(i = 0; i < EDUCATION_LIST_LENGTH; i++){
        strcpy(profile.saved_educations[i], "");
        strcpy(profile.recommended_educations[i], "");
    }

    return profile;
}

struct qualification createQualifications(int number_of_qualifications){
    struct qualification qualifications;

    qualifications.amount_of_subjects = number_of_qualifications;
    qualifications.subjects = (struct subject*) calloc(number_of_qualifications, sizeof(struct subject));

    return qualifications;
}

void freeQualifications(struct qualification q){
    free(q.subjects);
}

void freeProfile(struct profile p){
    freeQualifications(p.qualifications);
    freeVector(p.interests);
}

void printProfile(struct profile p){
    int i;

    printf("Name: %s\n", p.name);
    printVector(p.interests);

    for(i = 0; i < p.qualifications.amount_of_subjects; i++){
        printf("%s %d\n", classNameStr(p.qualifications.subjects[i].name),
                          p.qualifications.subjects[i].level);
    }

}