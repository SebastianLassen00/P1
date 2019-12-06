#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
#include "parser.h"
#include "region.h"
#include "vector.h"

#define STRING_MAX_LENGTH 50000
#define TABS '	'



/**
 * @brief 
 * 
 * @param database 
 * @param filereader 
 */
void parseDatabase(struct database *database, FILE *filereader){
    /* This will contain the first line where the type of database and encoding is read. */
    char database_format[STRING_MAX_LENGTH];
    
    /* This line holds the type of database and its character encoding. */
    /* At the moment, it is not used. */
    fgets(database_format, STRING_MAX_LENGTH, filereader);

    /* Read how many educations the file contains. */
    database->amount_of_educations = parseNumOfEdu(filereader);
    database->educations = (struct education*) calloc(database->amount_of_educations, sizeof(struct education));
    
    parseEduNames(database->educations, database->amount_of_educations, filereader);
    parseEduDesc(database->educations, database->amount_of_educations, filereader);
    parseEduLink(database->educations, database->amount_of_educations, filereader);
    parseRegion(database->educations, database->amount_of_educations, filereader);
    parseSubReq(database->educations, database->amount_of_educations, filereader);
    parseGradeReq(database->educations, database->amount_of_educations, filereader);

    database->amount_of_interests = parseNumOfInterests(filereader);
    database->interest_string = (char **) calloc(database->amount_of_interests, sizeof(char*));
    parseInterestNames(database, filereader);

    parseInterestValues(database->educations, database->amount_of_educations, database->amount_of_interests, filereader);
}

int countTotalLines(FILE* filereader){
    int total_lines = 0;
    char placeholder_string[STRING_MAX_LENGTH];

    while(fgets(placeholder_string, STRING_MAX_LENGTH, filereader))
        total_lines++;
    
    fseek(filereader, 0, SEEK_SET);

    return total_lines;
}

void parseInterestNames(struct database* database, FILE* filereader){
    int i;
    char current_line[STRING_MAX_LENGTH];
    char temp_string[STRING_MAX_LENGTH];
    int done = 0;
    char line_to_look_for[STRING_MAX_LENGTH] = "INTERESTS";

    while(!done && fgets(current_line, STRING_MAX_LENGTH, filereader) != NULL){
        sscanf(current_line, "%[^\n	]s", temp_string);
        if(strcmp(temp_string, line_to_look_for) == 0)
            done = 1;
    }

    for(i = 0; i < database->amount_of_interests; i++){
        fgets(current_line, STRING_MAX_LENGTH, filereader);
        sscanf(current_line, "%[^\n	]s", temp_string);
        database->interest_string[i] = calloc(strlen(temp_string) + 1, sizeof(char));
        strcpy(database->interest_string[i], temp_string);
    }

    rewind(filereader);
}

int parseNumOfInterests(FILE *filereader){
    char current_line[STRING_MAX_LENGTH];
    char temp_string[STRING_MAX_LENGTH];
    char line_to_look_for[STRING_MAX_LENGTH] = "INTERESTS";
    int number_of_interests = 0;
    int all_lines_length = 0;
    int done = 0;

    while(!done && fgets(current_line, STRING_MAX_LENGTH, filereader) != NULL){
        sscanf(current_line, "%[^\n	]s", temp_string);
        if(strcmp(temp_string, line_to_look_for) == 0)
            done = 1;
    }

    while (fgets(current_line, STRING_MAX_LENGTH, filereader) != NULL){
        all_lines_length += strlen(current_line);
        number_of_interests++;
    }

    rewind(filereader);

    return number_of_interests;
}

void parseInterestValues(struct education *education, int number_of_educations, int number_of_interests, FILE *filereader){
    char current_line[STRING_MAX_LENGTH];
    char *interest_value_string;
    char temp_string[STRING_MAX_LENGTH];
    int offset;
    int i;
    int j;
    struct vector temp_vector;
    int done = 0;
    char line_to_look_for[STRING_MAX_LENGTH] = "INTERESTS";
    

    while(!done && fgets(current_line, STRING_MAX_LENGTH, filereader) != NULL){
        sscanf(current_line, "%[^\n	]s", temp_string);
        if(strcmp(temp_string, line_to_look_for) == 0){
            done = 1;
        }
    }

    /*allocate interests - lav dette til en funktion senere*/
    for(i = 0; i < number_of_educations; i++){
        education[i].interests = createVector(number_of_interests);
    }

    for(i = 0; i < number_of_interests; i++){
        offset = 0;
        fgets(current_line, STRING_MAX_LENGTH, filereader);

        for(j = 0; j < number_of_educations; j++){
            interest_value_string = parseEduString(current_line, number_of_educations, offset);
            education[j].interests.array[i] = strtod(interest_value_string, NULL);
            offset += strlen(interest_value_string) + 1;
            free(interest_value_string);
        }
    }

    for(i = 0; i < number_of_educations; i++){
        temp_vector = normalizeVector(education[i].interests);
        freeVector(education[i].interests);
        education[i].interests = temp_vector;
    }

    rewind(filereader);
}

/** @fn void parseGradeReq(struct education *education, int number_of_educations, FILE *filereader)
 *  @brief Parses the subjects required for each education
 *  @param education The education to modify
 *  @param amount_of_educations The amount of educations in database
 *  @param filereader The file to read from 
 */
void parseSubReq(struct education *education, int number_of_educations, FILE *filereader){
    int i;
    int done = 0;
    char temp_string[STRING_MAX_LENGTH];
    char line_to_look_for[STRING_MAX_LENGTH] = "REQUIREMENTS";
    char current_line[STRING_MAX_LENGTH];

    /* Check whether the needed line to read exists */
    while(!done && fgets(current_line, STRING_MAX_LENGTH, filereader) != NULL){
        sscanf(current_line, "%[^\n	]s", temp_string);
        if(strcmp(temp_string, line_to_look_for) == 0)
            done = 1;
    }

    for ( i = 0; i < number_of_educations; i++){
        education[i].required_qualifications.subjects = (struct subject *) calloc(10, sizeof(struct subject));  
        education[i].required_qualifications.amount_of_subjects = 0;
        readReqString(&(education[i].required_qualifications), current_line, i + 1);
    }

    rewind(filereader);
}

/** @fn void parseGradeReq(struct education *education, int number_of_educations, FILE *filereader)
 *  @brief Parses the grade requirement for each education
 *  @param education The education to modify
 *  @param amount_of_educations The amount of educations in database
 *  @param filereader The file to read from 
 */
void parseGradeReq(struct education *education, int number_of_educations, FILE *filereader){
    char current_line[STRING_MAX_LENGTH];
    char temp_string[STRING_MAX_LENGTH];
    char line_to_look_for[STRING_MAX_LENGTH] = "REQUIRED GRADE";
    char *grade_string;
    int i; 
    int done = 0;
    int offset = 0;

    /* Check whether the needed line to read exists */
    while(!done && fgets(current_line, STRING_MAX_LENGTH, filereader) != NULL){
        sscanf(current_line, "%[^\n	]s", temp_string);
        if(strcmp(temp_string, line_to_look_for) == 0)
            done = 1;
    }

    /* Iterate through all educations */
    for(i = 0; i < number_of_educations; i++){
        grade_string = parseEduString(current_line, number_of_educations, offset);
        offset = strlen(grade_string) + 1;
        education[i].required_grade = strtod(grade_string, NULL);
        free(grade_string);
    }

    rewind(filereader);
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
    char temp_string[STRING_MAX_LENGTH];
    char line_to_look_for[STRING_MAX_LENGTH] = "LOCATION";
    int i;
    int offset = 0;
    int done = 0;

    /* Check whether the needed line to read exists */
    while(!done && fgets(current_line, STRING_MAX_LENGTH, filereader) != NULL){
        sscanf(current_line, "%[^\n	]s", temp_string);
        if(strcmp(temp_string, line_to_look_for) == 0)
            done = 1;
    }

    /* Iterate through all educations */
    for(i = 0; i < number_of_educations; i++){
        region_string = parseEduString(current_line, number_of_educations, offset);
        offset += strlen(region_string) + 1;
        education[i].region = strToReg(region_string);
        free(region_string);
    }

    rewind(filereader);
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

    /* Reset file pointer */
    rewind(filereader);
    fgets(current_line, STRING_MAX_LENGTH, filereader);
    

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
    char temp_string[STRING_MAX_LENGTH];
    char line_to_look_for[STRING_MAX_LENGTH] = "NAME";
    int i;
    int offset = 0;
    int done = 0;

    /* Check whether the needed line to read exists */
    while(!done && fgets(current_line, STRING_MAX_LENGTH, filereader) != NULL){
        sscanf(current_line, "%[^\n	]s", temp_string);
        if(strcmp(temp_string, line_to_look_for) == 0)
            done = 1;
    }

    /* Iterate through all educations and assign names */
    for(i = 0; i < amount_of_educations; i++){
        education[i].name = parseEduString(current_line, amount_of_educations, offset);
        offset += strlen(education[i].name) + 1;
    }

    rewind(filereader);
}

/** @fn void parseEduDesc(struct education *education, int amount_of_educations, FILE *filereader)
 *  @brief Parses the description for each education
 *  @param education The education to modify
 *  @param amount_of_educations The amount of educations in database
 *  @param filereader The file to read from 
 */
void parseEduDesc(struct education *education, int amount_of_educations, FILE *filereader){
    char current_line[STRING_MAX_LENGTH];
    char temp_string[STRING_MAX_LENGTH];
    char line_to_look_for[STRING_MAX_LENGTH] = "DESC";
    int i;
    int offset = 0;
    int done = 0;
    
    /* Check whether the needed line to read exists */
    while(!done && fgets(current_line, STRING_MAX_LENGTH, filereader) != NULL){
        sscanf(current_line, "%[^\n	]s", temp_string);
        if(strcmp(temp_string, line_to_look_for) == 0)
            done = 1;
    }

    /* Iterate through all educations */
    for(i = 0; i < amount_of_educations; i++){
        education[i].description = parseEduString(current_line, amount_of_educations, offset);
        offset += strlen(education[i].description) + 1;
    }

    rewind(filereader);
}

/** @fn void parseEduDesc(struct education *education, int amount_of_educations, FILE *filereader)
 *  @brief Parses the "read further" link for each education
 *  @param education The education to modify
 *  @param amount_of_educations The amount of educations in database
 *  @param filereader The file to read from 
 */
void parseEduLink(struct education *education, int amount_of_educations, FILE *filereader){
    char current_line[STRING_MAX_LENGTH];
    char temp_string[STRING_MAX_LENGTH];
    char line_to_look_for[STRING_MAX_LENGTH] = "LINK";
    int done = 0;
    int i;
    int offset = 0;
    
    /* Check whether the needed line to read exists */
    while(!done && fgets(current_line, STRING_MAX_LENGTH, filereader) != NULL){
        sscanf(current_line, "%[^\n	]s", temp_string);
        if(strcmp(temp_string, line_to_look_for) == 0)
            done = 1;
    }

    /* Iterate through all educations */
    for(i = 0; i < amount_of_educations; i++){
        education[i].link = parseEduString(current_line, amount_of_educations, offset);

        offset += strlen(education[i].link) + 1;
    }

    rewind(filereader);
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
    int i;

    for (i = 0; i < strlen(string); i++){
        if (*(string + i) == ch) 
            return i;
        /*printf("%d: %c   %d\n", i, ch, offset);*/
    }

    return -1;
}

void readReqString(struct qualification *qualification, char *string, int education_location) {
    int i, subject_index=0, offset = 0, moreReqs = 1;
    char reqClass[30];

    /*Find the offset for the current education*/
    for(i = 0; i < education_location; i++)
        offset += sseek(string + offset, '\t') + 1;
    
    do{
        fflush(stdout);
        qualification->amount_of_subjects += 1;
        
        /*read the first requirement name*/
        for(i = 0; string[offset + i] != ' ' && string[offset + i] != '\n' && string[offset + i] != '=' && string[offset + i] != '\t' && string[offset + i] != '_'; ++i) 
            reqClass[i] = string[offset + i];
        
        reqClass[i] = '\0';
       
        qualification->subjects[subject_index].name = stringToClass(reqClass);
        if(qualification->subjects[subject_index].name == NONE){
            qualification->subjects[subject_index].name = DANISH; 
            qualification->subjects[subject_index].level = Z;
        }
        

        if(string[offset + i] == '_'){
            ++i;
            qualification->subjects[subject_index].level = charToLevel(string[offset + i]);
            ++i;
        } else{
            qualification->subjects[subject_index].level = Z;
        }

        /*Check if there is more req to read*/
        if(string[offset + i] == '\t' || string[offset + i] == '\n'){
            moreReqs = 0;
        }

        ++subject_index; 
        offset += sseek(&string[offset], ' ') + 1;
    } while(moreReqs);
}