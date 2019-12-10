#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
#include "education.h"
#include "parser.h"

int compareEducations(const void *, const void *);



/**
 * @fn freeDatabase
 * @brief Free a database and all its elements
 * 
 * @param database 
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
 * @fn createDatabase
 * @brief Create a Database object in memory and create all its elements
 * 
 * @param database_file is the databasefile, which will be read into a database object
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

/**
 * @brief Finds an education in a database and returns a pointer to the education
 * 
 * @param database is the database, which will be searched
 * 
 * @return struct education* An education which name matches key or NULL if nothing was found
 */
struct education *findEducation(char *key, struct database *database){
    int i;
    struct education *education = NULL;

    for( i = 0; i < database->amount_of_educations; i++){
        if(strcmp(key, database->educations[i].name) == 0 ){
              education = &database->educations[i];
        } 
    }

    return education;
}
