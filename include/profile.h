#include "vector.h"
#include "subjects.h"
#include "region.h"
#include "education.h"
#include "constants.h"

#ifndef PROFILE_H
#define PROFILE_H

struct profile{
    struct vector interests;
    struct vector adjustment_vector;
    char * name;
    struct qualification qualifications;
    double average;
    struct location location;
    struct education saved_educations[EDUCATION_LIST_LENGTH];
    int last_recommended;
    struct education recommended_educations[EDUCATION_LIST_LENGTH];
};



#endif 
