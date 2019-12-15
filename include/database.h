/** @file database.h
 *  @brief Contains elements relating to the database
 * 
 *  Contains the database struct and functions for creating, freeing and finding educations.
*/  

#ifndef DATABASE_H
#define DATABASE_H

#include "education.h"

/**
 * @struct database
 * @brief A structure to store a database
 * @var database::amount_of_educations 
 * The amount of educations in the database
 * @var database::educations 
 * An array of educations delimited by amount_of_educations
 * @var database::amount_of_interests 
 * The amount of interests in the database
 * @var database::interest_string 
 * An array of interests in the order parsed
 */
struct database{
    int amount_of_educations;           
    struct education *educations;       
    int amount_of_interests;            
    char **interest_string;   
};

void freeDatabase(struct database *);
struct database *createDatabase(char *);

#endif  