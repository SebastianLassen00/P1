#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
#include "parser.h"
#include "region.h"

#define STRING_MAX_LENGTH 50000
#define TABS '	'

int sseek(char *, char);
void readReqString(struct qualification *, char *, int);

/**
 * @brief 
 * 
 * @param database 
 * @param filereader 
 */
void parseDatabase(struct database *database, FILE *filereader){
    char database_format[STRING_MAX_LENGTH];
    
    /* not used atm */
    fgets(database_format, STRING_MAX_LENGTH, filereader);
    
    database->amount_of_educations = parseNumOfEdu(filereader);
    database->educations = (struct education*) malloc(database->amount_of_educations * sizeof(struct education));
    
    parseEduNames(database->educations, database->amount_of_educations, filereader);
    parseEduDesc(database->educations, database->amount_of_educations, filereader);
    parseEduLink(database->educations, database->amount_of_educations, filereader);
    parseRegion(database->educations, database->amount_of_educations, filereader);
    parseSubReq(database->educations, database->amount_of_educations, filereader);
    parseGradeReq(database->educations, database->amount_of_educations, filereader);
}

void parseSubReq(struct education *education, int number_of_educations, FILE *filereader){
    int i;
    char current_line[STRING_MAX_LENGTH];

    fgets(current_line, STRING_MAX_LENGTH, filereader);

    for ( i = 0; i < number_of_educations; i++)
    {
        readReqString(&education[i].required_qualifications, current_line, i + 1);
    }
    
}

void parseGradeReq(struct education *education, int number_of_educations, FILE *filereader){
    char current_line[STRING_MAX_LENGTH];
    char *grade_string;
    int i; 
    int offset = 0;

    fgets(current_line, STRING_MAX_LENGTH, filereader);

    for(i = 0; i < number_of_educations; i++){
        grade_string = parseEduString(current_line, number_of_educations, offset);
        offset = strlen(grade_string) + 1;
        education[i].required_grade = strtod(grade_string, NULL);
    }

    free(grade_string);
}

void parseRegion(struct education *education, int number_of_educations, FILE *filereader){
    char current_line[STRING_MAX_LENGTH];
    char *region_string;
    int i;
    int offset = 0;

    fgets(current_line, STRING_MAX_LENGTH, filereader);

    for(i = 0; i < number_of_educations; i++){
        region_string = parseEduString(current_line, number_of_educations, offset);
        offset += strlen(region_string) + 1;
        education[i].region = strToReg(region_string);
    }

    free(region_string);
}

int strToReg(char* region_string){
    enum region region;
    
    if(strcmp(region_string, "NORTH_JUTLAND") == 0){
        region = NORTH_JUTLAND;
    } else if(strcmp(region_string, "CENTRAL_JUTLAND") == 0){
        region = CENTRAL_JUTLAND;
    } else if(strcmp(region_string, "SOUTHERN_DENMARK") == 0){
        region = SOUTHERN_DENMARK;
    } else if(strcmp(region_string, "ZEALAND") == 0){
        region = ZEALAND;
    } else if(strcmp(region_string, "CAPITAL_REGION") == 0) {
        region = CAPITAL_REGION;
    }

    return region;
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

    for(i = 0; i < amount_of_educations; i++){
        education[i].name = parseEduString(current_line, amount_of_educations, offset);
        offset += strlen(education[i].name) + 1;
    }
}

void parseEduDesc(struct education *education, int amount_of_educations, FILE *filereader){
    char current_line[STRING_MAX_LENGTH];
    int i;
    int offset = 0;
    
    fgets(current_line, STRING_MAX_LENGTH, filereader);

    for(i = 0; i < amount_of_educations; i++){
        education[i].description = parseEduString(current_line, amount_of_educations, offset);
        offset += strlen(education[i].description) + 1;
    }
}

void parseEduLink(struct education *education, int amount_of_educations, FILE *filereader){
    char current_line[STRING_MAX_LENGTH];
    int i;
    int offset = 0;
    
    fgets(current_line, STRING_MAX_LENGTH, filereader);

    for(i = 0; i < amount_of_educations; i++){
        education[i].link_to_read_further = parseEduString(current_line, amount_of_educations, offset);

        offset += strlen(education[i].link_to_read_further) + 1;
    }
}

char *parseEduString(char* current_line, int amount_of_educations, int offset){
    char tmp_education_string[STRING_MAX_LENGTH];
    char *education_string;
    
    int tmp_education_string_length;
    int i;

    i = strchr(current_line, TABS) - current_line + sizeof(char) + offset;
    
    sscanf(current_line + i, "%[^\n	]s", tmp_education_string);
    tmp_education_string_length = strlen(tmp_education_string);
    education_string = (char *) malloc((tmp_education_string_length + 1) * sizeof(char));

    strcpy(education_string, tmp_education_string);

    return education_string;
}

int sseek(char *string, char ch){
    int i;

    for (i = 0; i < strlen(string); i++)
    {
        if (*(string + i) == ch) return i;
    }
}

void readReqString(struct qualification *qualification, char *string, int education_location) {
    int i, offset = 0, moreReqs = 1;
    char reqClass[20];
    enum class class;
    enum level level = Z;

    /*Find the offset for the current education*/
    for ( i = 0; i < education_location; i++) offset += sseek(string + offset, '\t');

    do
    {
        for(i = 0; i != ' ' && i != '\n' && i != '=' && i != '\t'; ++i) reqClass[i] = string[offset + i];
        reqClass[i] = '\0';

        if(string[offset + i] == '\t' || string[offset + i] == '\n') moreReqs = 0;
    } while (moreReqs);
    
    
    
    
}