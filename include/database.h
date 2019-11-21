#ifndef DATABASE_H
#define DATABASE_H

#include "education.h"

/**
 * @struct
 * @brief A structure to store a database
 * 
 */
struct database {
    int database_size;
    struct education *educations;
};


struct database *createDatabase(char *);
struct education *findEducation(struct database *);


#endif