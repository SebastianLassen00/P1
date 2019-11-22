#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
#include "education.h"

int compareEducations(const void *, const void *);

/**
 * @brief Create a Database object
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

    parseDatabase(database, data);

    return database;
}

/**
 * @brief Finds an education in a database and returns a pointer to the education
 * 
 * @param database is the database, which will be searched
 * 
 * @return struct education* 
 */
struct education *findEducation(char *key, struct database *database){
    int i;
    struct education *education = NULL;

    for( i = 0; i < database->amount_of_educations; i++){
        if(strcmp(key, database->educations[i].name)){
            education = &(database->educations[i]);
        } 
    }  
}

/**
 * @brief compares educations based on their name
 * 
 * @param edu1 
 * @param edu2 
 * @return int 
 */
int compareEducations(const void * edu1, const void *edu2){
    return strcmp(((struct education *)edu1)->name, ((struct education *)edu2)->name);
}