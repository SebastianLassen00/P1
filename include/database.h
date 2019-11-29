#ifndef DATABASE_H
#define DATABASE_H

#include "education.h"

/**
 * @struct
 * @brief A structure to store a database
 */
struct database {
    int amount_of_educations;           /**the amount of educations in the database*/
    struct education **educations;       /**an array of educations delimited by amount_of_educations*/
    int amount_of_interests;            /**the amount of interests in the database*/
    char *interest_string;   /**an array of interests in the order parsed*/
};

void freeDatabase(struct database *);
struct database *createDatabase(char *);
struct education *findEducation(char *, struct database *);
struct educationArray *searchDatabaseForEducation(char *, struct database *);

#endif  