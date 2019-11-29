#include <stdio.h>
#include <stdlib.h>

#include "profile.h"
#include "education.h"
#include "subjects.h"
#include "vector.h" 

struct profile createProfile(int number_of_interests){
    struct profile profile;
    char name[MAX_NAME_LENGTH];

    profile.interests = createVector(number_of_interests);
    profile.adjustment_vector = createVector(number_of_interests);
    profile.name = name;
    profile.qualifications = createQualifications(TOTAL_SUBJECTS);
    profile.average = 0.0;
    profile.location.region = 0;
    profile.location.region_importance = 0;
    profile.last_recommended = 0;

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