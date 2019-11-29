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
    /* This will contain the first line where the type of database and encoding is read. */
    char database_format[STRING_MAX_LENGTH];
    
    /* Not used atm. */
    fgets(database_format, STRING_MAX_LENGTH, filereader);
    
    database->amount_of_educations = parseNumOfEdu(filereader);
    database->educations = (struct education*) malloc(database->amount_of_educations * sizeof(struct education));
    
    /* Each of these functions assume that the program is ready to read the relevant line */
    parseEduNames(database->educations, database->amount_of_educations, filereader);
    parseEduDesc(database->educations, database->amount_of_educations, filereader);
    parseEduLink(database->educations, database->amount_of_educations, filereader);
    parseRegion(database->educations, database->amount_of_educations, filereader);
    parseSubReq(database->educations, database->amount_of_educations, filereader);
    parseGradeReq(database->educations, database->amount_of_educations, filereader);
}

/** @fn void parseGradeReq(struct education *education, int number_of_educations, FILE *filereader)
 *  @brief Parses the subjects required for each education
 *  @param education The education to modify
 *  @param amount_of_educations The amount of educations in database
 *  @param filereader The file to read from 
 */
void parseSubReq(struct education *education, int number_of_educations, FILE *filereader){
    int i;
    char current_line[STRING_MAX_LENGTH];

    fgets(current_line, STRING_MAX_LENGTH, filereader);

    for ( i = 0; i < number_of_educations; i++)
    {
        readReqString(&education[i].required_qualifications, current_line, i + 1);
    }
    
}

/** @fn void parseGradeReq(struct education *education, int number_of_educations, FILE *filereader)
 *  @brief Parses the grade requirement for each education
 *  @param education The education to modify
 *  @param amount_of_educations The amount of educations in database
 *  @param filereader The file to read from 
 */
void parseGradeReq(struct education *education, int number_of_educations, FILE *filereader){
    char current_line[STRING_MAX_LENGTH];
    char *grade_string;
    int i; 
    int offset = 0;

    fgets(current_line, STRING_MAX_LENGTH, filereader);

    /* Iterate through all educations */
    for(i = 0; i < number_of_educations; i++){
        grade_string = parseEduString(current_line, number_of_educations, offset);
        offset = strlen(grade_string) + 1;
        education[i].required_grade = strtod(grade_string, NULL);
    }

    free(grade_string);
}

/** @fn void parseRegion(struct education *education, int number_of_educations, FILE *filereader)
 *  @brief Parses the region for each education
 *  @param education The education to modify
 *  @param amount_of_educations The amount of educations in database
 *  @param filereader The file to read from 
 */
void parseRegion(struct education *education, int number_of_educations, FILE *filereader){
    char current_line[STRING_MAX_LENGTH];
    char *region_string;
    int i;
    int offset = 0;

    fgets(current_line, STRING_MAX_LENGTH, filereader);

    /* Iterate through all educations */
    for(i = 0; i < number_of_educations; i++){
        region_string = parseEduString(current_line, number_of_educations, offset);
        offset += strlen(region_string) + 1;
        education[i].region = strToReg(region_string);
    }

    free(region_string);
}

/** @fn int strToReg(char* region_string)
 *  @brief Converts a string into an enum region
 *  @param region_string The string to convert
 */
enum region strToReg(char* region_string){
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

/** @fn int parseNumOfEdu(FILE *filereader)
 *  @brief Returns the number of educations from database file
 *  @param filereader The file to read from
 */
int parseNumOfEdu(FILE *filereader){
    int number_of_educations = 0;
    char current_line[STRING_MAX_LENGTH];
    int line_length;
    int i;

    fgets(current_line, STRING_MAX_LENGTH, filereader);
    line_length = strlen(current_line);

    /* Iterate through all educations */
    for(i = 0; i < line_length; i++){
        if(current_line[i] == TABS) {
            number_of_educations++;
        }
    }

    /* set file pointer to previous line */
    fseek(filereader, -line_length - 1, SEEK_CUR);

    return number_of_educations;
}

/** @fn void parseEduNames(struct education *education, int amount_of_educations, FILE *filereader)
 *  @brief Parses the name for each education
 *  @param education The education to modify
 *  @param amount_of_educations The amount of educations in database
 *  @param filereader The file to read from 
 */
void parseEduNames(struct education *education, int amount_of_educations, FILE *filereader){
    char current_line[STRING_MAX_LENGTH];
    int i;
    int offset = 0;
    
    fgets(current_line, STRING_MAX_LENGTH, filereader);

    /* Iterate through all educations */
    for(i = 0; i < amount_of_educations; i++){
        education[i].name = parseEduString(current_line, amount_of_educations, offset);
        offset += strlen(education[i].name) + 1;
    }
}

/** @fn void parseEduDesc(struct education *education, int amount_of_educations, FILE *filereader)
 *  @brief Parses the description for each education
 *  @param education The education to modify
 *  @param amount_of_educations The amount of educations in database
 *  @param filereader The file to read from 
 */
void parseEduDesc(struct education *education, int amount_of_educations, FILE *filereader){
    char current_line[STRING_MAX_LENGTH];
    int i;
    int offset = 0;
    
    fgets(current_line, STRING_MAX_LENGTH, filereader);

    /* Iterate through all educations */
    for(i = 0; i < amount_of_educations; i++){
        education[i].description = parseEduString(current_line, amount_of_educations, offset);
        offset += strlen(education[i].description) + 1;
    }
}

/** @fn void parseEduDesc(struct education *education, int amount_of_educations, FILE *filereader)
 *  @brief Parses the "read further" link for each education
 *  @param education The education to modify
 *  @param amount_of_educations The amount of educations in database
 *  @param filereader The file to read from 
 */
void parseEduLink(struct education *education, int amount_of_educations, FILE *filereader){
    char current_line[STRING_MAX_LENGTH];
    int i;
    int offset = 0;
    
    fgets(current_line, STRING_MAX_LENGTH, filereader);

    /* Iterate through all educations */
    for(i = 0; i < amount_of_educations; i++){
        education[i].link_to_read_further = parseEduString(current_line, amount_of_educations, offset);

        offset += strlen(education[i].link_to_read_further) + 1;
    }
}

/** @fn char *parseEduString(char* current_line, int amount_of_educations, int offset)
 *  @brief Scans the current line + i until TABS or newline. Saves the scanned string and returns a pointer to it.
 *  @param current_line The line to scan
 *  @param amount_of_educations The amount of educations in database
 *  @param offset The offset to decide how many chars to skip in current_line
 */
char *parseEduString(char* current_line, int amount_of_educations, int offset){
    char tmp_education_string[STRING_MAX_LENGTH];
    char *education_string;
    
    int tmp_education_string_length;
    int i;

    /* Calculate how many chars to skip. Will always skip the first word*/
    i = strchr(current_line, TABS) - current_line + sizeof(char) + offset;
    
    sscanf(current_line + i, "%[^\n	]s", tmp_education_string);
    tmp_education_string_length = strlen(tmp_education_string);
    education_string = (char *) malloc((tmp_education_string_length + 1) * sizeof(char));

    strcpy(education_string, tmp_education_string);

    return education_string;
}

int sseek(char *string, char ch){
    int i, offset = -1;

    for (i = 0; i < strlen(string); i++)
    {
        if (*(string + i) == ch) offset = i;
    }

    return offset;
}

void readReqString(struct qualification *qualification, char *string, int education_location) {
    int     i, /**Used for indexing*/
            offset = 0 /**The offset of the current word*/, 
            moreReqs = 1;
    char    reqClass[30];

    /*Find the offset for the current education*/
    for ( i = 0; i < education_location; i++) offset += sseek(string + offset, '\t');

    do
    {
        /*read the first requirement name*/
        for(i = 0; i != ' ' && i != '\n' && i != '=' && i != '\t'; ++i) reqClass[i] = string[offset + i];
        reqClass[i] = '\0';

        qualification->subjects[education_location - 1].name = stringToClass(reqClass);
        if (qualification->subjects[education_location - 1].name == NONE) 
            qualification->subjects[education_location - 1].name = DANISH, 
            qualification->subjects[education_location - 1].level = Z;

        if (string[offset + i] == '_')
        {
            ++i;
            qualification->subjects[education_location - 1].level = string[offset + i];
            
            if (string[offset + ++i] == '=')
            {
                ++i;
                if(sscanf(string + offset + i, "%f", &qualification->subjects[education_location - 1].required_grade));
                else qualification->subjects[education_location - 1].required_grade = 2.0f;
                ++i;
            }else{
                qualification->subjects[education_location - 1].required_grade = 2.0f;
            } 
        }else{
            qualification->subjects[education_location - 1].level = Z;
            qualification->subjects[education_location - 1].required_grade = -3.0f;
        }

        /*Check if there is more req to read*/
        if(string[offset + i] == '\t' || string[offset + i] == '\n') moreReqs = 0;
    } while (moreReqs);
    
    
    
    
}