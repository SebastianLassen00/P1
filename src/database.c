#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
#include "education.h"
#include "parser.h"


/**
 * @fn void freeDatabase(struct database *database)
 * @brief Free a database and all its elements
 * 
 * @param database A struct database that contains arrays allocated in the heap
 */
void freeDatabase(struct database *database){
    int i;

    for(i = 0; i < database->amount_of_educations; ++i){
        freeEducation(&database->educations[i]);
    }

    free(database->educations);
    
    for (i = 0; i < database->amount_of_interests; i++)
        free(database->interest_string[i]);
 
    free(database->interest_string);
    
    free(database);
}


/**
 * @fn struct database *createDatabase(char *database_file )
 * @brief Create a Database object in memory and create all its elements
 * 
 * @param database_file Is the databasefile, which will be read into a database object
 * 
 * @return struct database* 
 */
struct database *createDatabase(char *database_file ){
    struct database *database;
    FILE *data;

    database = malloc(sizeof(struct database));
    data = fopen(database_file, "r");

    if(data == NULL)
        printf("This is some lousy shit right here\n");

    parseDatabase(database, data);

    fclose(data);

    return database;
}