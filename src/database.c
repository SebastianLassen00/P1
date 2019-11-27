#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
#include "education.h"
#include "parser.h"

int compareEducations(const void *, const void *);



/**
 * @brief Free a databases memories
 * 
 * @param database 
 */
void freeDatabase(struct database *database){
    int i;

    for(i = 0; i < database->amount_of_educations; ++i){
        freeEducation(database->educations[i]);
    }

    for(i = 0; i < database->amount_of_interests; i++) 
        free(database->interest_as_read_in_database[i]);

    free(database->interest_as_read_in_database);

    free(database);
}


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

    fclose(data);

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
        if(strcmp(key, database->educations[i]->name)){
            education = database->educations[i];
        } 
    }

    return education;
}

/**
 * @brief Finds all educations with the matching search_word
 * 
 * @param search_word The name of the education you are searching for
 * @return struct educationArray* 
 */
struct educationArray *searchDatabaseForEducation(char *search_word, struct database *database){
    int i;  /**Used for indexing*/
    struct educationArray *educationArray; /**This functions return value*/
    char *temp_string;  /**A string used for temporay allocation*/

    /*Setup the necessary variables*/
    educationArray = calloc(1, sizeof(struct educationArray));
    temp_string = calloc(strlen(search_word) + 1, 1);
    educationArray->educations = malloc(sizeof(void *) * 10);
    
    /*Go through all educations in database*/
    for(i = 0; i < database->amount_of_educations + 1; i++){
        strncpy(temp_string, database->educations[i]->name, strlen(search_word));

        /*If the education has the search word in it*/
        if(strcmp(temp_string, search_word) 
            && educationArray->amount_of_educations < 10){
            educationArray->amount_of_educations += 1;
            educationArray->educations[i] = database->educations[i];
        }
    }

    return educationArray;
}