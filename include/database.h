#ifndef DATABASE_H
#define DATABASE_H

#include "education.h"

/**
 * @struct
 * @brief A structure to store a database
 * 
 */
struct database {
    int amount_of_educations;           /**the amount of educations in the database*/
    struct education *educations;       /**an array of educations delimited by amount_of_educations*/
    int amount_of_interests;            /**the amount of interests in the database*/
    char **insterest_as_read_in_database;   /**an array of interests in the order parsed*/
};


struct database *createDatabase(char *);
struct education *findEducation(char *, struct database *);


#endif