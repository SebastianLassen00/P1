#include "vector.h"
#include "subjects.h"
#include "region.h"

#ifndef PROFILE_H
#define PROFILE_H

#define MAX_NAME_LENGTH 20
#define EDUCATION_LIST_LENGTH 10

struct profile{
    struct vector interests;
    struct vector adjustment_vector;
    char * name;
    struct qualification qualifications;
    double average;
    struct location location;
    struct education saved_educations[EDUCATION_LIST_LENGTH];
    struct education recommended_educations[EDUCATION_LIST_LENGTH];
};



#endif 
