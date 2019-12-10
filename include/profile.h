/** @file profile.h
 *  @brief Contains elements relating to profile
 * 
 *  <Detailed esription here>
*/  

#include "vector.h"
#include "subjects.h"
#include "region.h"
#include "education.h"
#include "constants.h"

#ifndef PROFILE_H
#define PROFILE_H

/**
 * @struct profile
 * @brief Describes a user.
 * 
 * This structure defines a user and all the details about the user.
 * @var interests 
 * @var adjustment_vector 
 * @var name 
 * @var qualifications
 * @var average 
 * @var location 
 * @var saved_educations 
 * @var last_recommended
 * @var recommended_educations
 */
struct profile{
    struct vector interests;
    struct vector adjustment_vector;
    char   name[MAX_NAME_LENGTH];
    struct qualification qualifications;
    double average;
    struct location location;
    char saved_educations[EDUCATION_LIST_LENGTH][MAX_EDU_NAME_LENGTH];
    int last_recommended;
    char recommended_educations[EDUCATION_LIST_LENGTH][MAX_EDU_NAME_LENGTH];
};

struct profile createProfile(int number_of_interests);
void freeProfile(struct profile p);
void printProfile(struct profile p);

#endif 
