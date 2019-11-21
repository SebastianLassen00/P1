#include "database.h"
#include <stdio.h>
#include <stdlib.h>


/**
 * @brief Create a Database object
 * 
 * @param database_file is the databasefile, which will be read into a database object
 * 
 * @return struct database* 
 */
struct database *createDatabase(char *database_file ) {
    struct database *database;
    FILE *data;

    database = malloc(sizeof(struct database));
    data = fopen(database_file, "r");

    

    return database;
}

/**
 * @brief Finds an education in a database and returns a pointer to the education
 * 
 * @param database is the database, which will be searched
 * 
 * @return struct education* 
 */
struct education *findEducation(struct database *database) {

}