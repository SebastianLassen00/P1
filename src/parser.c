#include <stdio.h>
#include "database.h"
#include "parser.h"

#define STRING_MAX_LENGTH 50000
#define TABS '	'

/**
 * @brief 
 * 
 * @param database 
 * @param filereader 
 */
void parseDatabase(struct database *database, FILE *filereader){
    database->amount_of_educations = parseNumOfEdu(filereader);
    database->educations = (struct education*) malloc(database->amount_of_educations * sizeof(struct education));
    parseEduNames(database->educations, database->amount_of_educations, filereader);
}

int parseNumOfEdu(FILE *filereader){
    int number_of_educations = 0;
    char current_line[STRING_MAX_LENGTH];
    int line_length;
    int i;

    fgets(current_line, STRING_MAX_LENGTH, filereader);
    line_length = strlen(current_line);

    for(i = 0; i < line_length; i++){
        if(current_line[i] == TABS) {
            number_of_educations++;
        }
    }

    /* set file pointer to previous line */
    fseek(filereader, -line_length - 1, SEEK_CUR);

    return number_of_educations;
}

void parseEduNames(struct education *education, int amount_of_educations, FILE *filereader){
    char current_line[STRING_MAX_LENGTH];
    int i;
    int offset = 0;
    
    fgets(current_line, STRING_MAX_LENGTH, filereader);

    for (i = 0; i < amount_of_educations; i++){
        education[i].name = parseEduString(current_line, amount_of_educations, education[i].name, offset);
        offset += strlen(education[i].name) + 1;
    }
}

char *parseEduString(char* current_line, int amount_of_educations, char* education_string, int offset){
    char tmp_education_string[STRING_MAX_LENGTH];
    int tmp_education_string_length;
    int i;

    i = strchr(current_line, TABS) - current_line + sizeof(char) + offset;
    
    sscanf(current_line + i, "%[^\n	]s", tmp_education_string);
    tmp_education_string_length = strlen(tmp_education_string);
    education_string = (char *) malloc((tmp_education_string_length + 1) * sizeof(char));

    strcpy(education_string, tmp_education_string);

    return education_string;
}
