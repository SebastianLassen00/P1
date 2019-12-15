/** @file profile.h
 *  @brief Contains elements relating to user profiles
 * 
 *  Contains the profile struct and the functions for creating, printing and deallocating user profiles.
*/  

#include "vector.h"
#include "subjects.h"
#include "region.h"
#include "education.h"
#include "constants.h"

#ifndef PROFILE_H
#define PROFILE_H

/**
 *  @struct profile
 *  @brief Describes a user
 * 
 *  This structure defines the profile of a user and all the details about the user
 *  @var profile::interests 
 *  The interest of a a user
 *  @var profile::adjustment_vector 
 *  This is a vector used to adjust the users vector 
 *  (the coordinates of this vector are determined in the evaluation of an education) 
 *  @var profile::name 
 *  The name of the user
 *  @var profile::qualifications 
 *  A struct containing an array of subjects where each subject has a name and and a level 
 *  @var profile::average 
 *  The average grade of the user
 *  @var profile::location 
 *  Contains the users desired location to study and the importance of this location
 *  @var profile::saved_educations 
 *  A list of the names of 10 educations which the user has saved
 *  @var profile::last_recommended 
 *  Contains the index of the last recommended education
 *  @var profile::recommended_educations 
 *  A list of the names of the 10 most recent educations recommended to the user
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
