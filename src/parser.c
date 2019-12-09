#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
#include "parser.h"
#include "region.h"
#include "vector.h"
#include "constants.h"

/* DOKUMENTATION TIL FUNKTIONERNE SKAL LAVES/LAVES OM 
   90% ER BLEVET SKREVET OM */

/**
 * @brief 
 * 
 * @param database 
 * @param filereader 
 */
void parseDatabase(struct database *database, FILE *filereader){
    /* This will contain the first line where the type of database and encoding is read. */
    char database_format[STRING_MAX_LENGTH];
    char lines_to_read[][STRING_MAX_LENGTH] = {"NAME", "DESC", "LINK",
                                               "LOCATION", "REQUIREMENTS",
                                               "REQUIRED GRADE", "INTERESTS"};
    
    char amount_of_lines_to_read = sizeof(lines_to_read) / sizeof(lines_to_read[0]);
    int i;
    
    /* This line holds the type of database and its character encoding. */
    /* At the moment, it is not used. */
    fgets(database_format, STRING_MAX_LENGTH, filereader);
    
    database->amount_of_educations = parseNumOfEdu(filereader);
    database->educations = (struct education*) calloc(database->amount_of_educations, sizeof(struct education));
    
    database->amount_of_interests = parseNumOfInterests(filereader);
    database->interest_string = (char **) calloc(database->amount_of_interests, sizeof(char*));
    
    /* Allocate interest vectors in all educations */
    for(i = 0; i < database->amount_of_educations; i++){
        database->educations[i].interests = createVector(database->amount_of_interests);
    }
    
    /* Parse all lines from lines_to_read */
    for(i = 0; i < amount_of_lines_to_read; i++){
        parseDatabaseLine(lines_to_read[i], database, filereader);
    }
}

void findDatabaseLine(const char key[], FILE* filereader, char* current_line){
    int found = 0;
    char temp_string[STRING_MAX_LENGTH];

    while(!found && fgets(current_line, STRING_MAX_LENGTH, filereader) != NULL){
        sscanf(current_line, "%[^\n	]s", temp_string);
        if(strcmp(temp_string, key) == 0){
            /*printf("%s WAS FOUND.........\n", key);*/
            found = 1;
        }
    }

    /* Return default string if a line with key does not exist */
    if(found == 0){
        strcpy(current_line, NOT_FOUND_STRING);
    }
}

void parseDatabaseLine(const char key[], struct database* database, FILE* filereader){
    char current_line[STRING_MAX_LENGTH];
    
    findDatabaseLine(key, filereader, current_line);

    /* Guard to make sure a line with key exists. Return if it does not and reset file pointer. */
    if(strcmp(current_line, NOT_FOUND_STRING) == 0){
        printf("An error has occured: Tried to parse line with %s, but entry does not exist in database.\n\n", key);
        rewind(filereader);
        return;
    }

    if(strcmp(key, "NAME") == 0){
        parseEduNames(database, current_line);
    } else if(strcmp(key, "DESC") == 0){
        parseEduDesc(database, current_line);
    } else if(strcmp(key, "LINK") == 0){
        parseEduLink(database, current_line);
    } else if(strcmp(key, "LOCATION") == 0){
        parseEduRegion(database, current_line);
    } else if(strcmp(key, "REQUIREMENTS") == 0){
        parseSubReq(database->educations, database->amount_of_educations, filereader, current_line);
    } else if(strcmp(key, "REQUIRED GRADE") == 0){
        parseReqGrade(database, current_line);
    } else if(strcmp(key, "INTERESTS") == 0){
        /* First parse all the names of the interests */
        parseInterestNames(database, filereader);

        /* Rewind the file pointer and find the correct line again */
        rewind(filereader);
        findDatabaseLine(key, filereader, current_line);

        parseInterestValues(database, filereader);
    } else{
        printf("An error has occured. Attempting to parse %s, but no parsing functions exist.\n\n", key);
    }

    rewind(filereader);
}

void parseInterestNames(struct database* database, FILE* filereader){
    int i;
    char current_line[STRING_MAX_LENGTH];
    char temp_string[STRING_MAX_LENGTH];

    for(i = 0; i < database->amount_of_interests; i++){
        fgets(current_line, STRING_MAX_LENGTH, filereader);
        sscanf(current_line, "%[^\n	]s", temp_string);
        database->interest_string[i] = calloc(strlen(temp_string) + 1, sizeof(char));
        strcpy(database->interest_string[i], temp_string);
    }
}

int parseNumOfInterests(FILE *filereader){
    char current_line[STRING_MAX_LENGTH];
    int number_of_interests = 0;

    findDatabaseLine("INTERESTS", filereader, current_line);

    while (fgets(current_line, STRING_MAX_LENGTH, filereader) != NULL){
        number_of_interests++;
    }

    rewind(filereader);
    return number_of_interests;
}

void parseInterestValues(struct database* database, FILE* filereader){
    char *temp_interest_value_string;
    char current_line[STRING_MAX_LENGTH];
    int offset;
    int i;
    int j;
    struct vector temp_vector;
    
    /* Iterate through all interests */
    for(i = 0; i < database->amount_of_interests; i++){
        offset = 0;
        fgets(current_line, STRING_MAX_LENGTH, filereader);

        /* Assign the interest values to each education */
        for(j = 0; j < database->amount_of_educations; j++){
            temp_interest_value_string = parseEduString(current_line, database->amount_of_educations, offset);
            database->educations[j].interests.array[i] = strtod(temp_interest_value_string, NULL);
            offset += strlen(temp_interest_value_string) + 1;
            free(temp_interest_value_string);
        }
    }

    /* Normalize Values */
    for(i = 0; i < database->amount_of_educations; i++){
        temp_vector = normalizeVector(database->educations[i].interests);
        freeVector(database->educations[i].interests);
        database->educations[i].interests = temp_vector;
    }

    rewind(filereader);
}

/** @fn void parseGradeReq(struct education *education, int number_of_educations, FILE *filereader)
 *  @brief Parses the subjects required for each education
 *  @param education The education to modify
 *  @param amount_of_educations The amount of educations in database
 *  @param filereader The file to read from 
 */
void parseSubReq(struct education *education, int number_of_educations, FILE *filereader, char current_line[]){
    int i;

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
void parseReqGrade(struct database* database, char current_line[]){
    char *temp_grade_string;
    int i;
    int offset = 0;


    /* Iterate through all educations */
    for(i = 0; i < database->amount_of_educations; i++){
        temp_grade_string = parseEduString(current_line, database->amount_of_educations, offset);
        offset += strlen(temp_grade_string) + 1;
        database->educations[i].required_grade = strtod(temp_grade_string, NULL);
        free(temp_grade_string);
    }
}

/** @fn void parseRegion(struct education *education, int number_of_educations, FILE *filereader)
 *  @brief Parses the region for each education
 *  @param education The education to modify
 *  @param amount_of_educations The amount of educations in database
 *  @param filereader The file to read from 
 */
void parseEduRegion(struct database* database, char current_line[]){
    char *temp_region_string;
    int i;
    int offset = 0;

    /* Iterate through all educations */
    for(i = 0; i < database->amount_of_educations; i++){
        temp_region_string = parseEduString(current_line, database->amount_of_educations, offset);
        offset += strlen(temp_region_string) + 1;
        database->educations[i].region = strToReg(temp_region_string);
        free(temp_region_string);
    }
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

    findDatabaseLine("NAME", filereader, current_line);
    line_length = strlen(current_line);

    /* Iterate through all educations */
    for(i = 0; i < line_length; i++){
        if(current_line[i] == TABS) {
            number_of_educations++;
        }
    }

    /* Reset file pointer */
    rewind(filereader);
    
    return number_of_educations;
}

/** @fn void parseEduNames(struct education *education, int amount_of_educations, FILE *filereader)
 *  @brief Parses the name for each education
 *  @param education The education to modify
 *  @param amount_of_educations The amount of educations in database
 *  @param filereader The file to read from 
 */
void parseEduNames(struct database* database, char current_line[]){
    int i;
    int offset = 0;

    /* Iterate through all educations and assign names */
    for(i = 0; i < database->amount_of_educations; i++){
        database->educations[i].name = parseEduString(current_line, database->amount_of_educations, offset);
        offset += strlen(database->educations[i].name) + 1;
    }
}

/** @fn void parseEduDesc(struct education *education, int amount_of_educations, FILE *filereader)
 *  @brief Parses the description for each education
 *  @param education The education to modify
 *  @param amount_of_educations The amount of educations in database
 *  @param filereader The file to read from 
 */
void parseEduDesc(struct database* database, char current_line[]){
    int i;
    int offset = 0;

    /* Iterate through all educations */
    for(i = 0; i < database->amount_of_educations; i++){
        database->educations[i].description = parseEduString(current_line, database->amount_of_educations, offset);
        offset += strlen(database->educations[i].description) + 1;
    }
}

/** @fn void parseEduDesc(struct education *education, int amount_of_educations, FILE *filereader)
 *  @brief Parses the "read further" link for each education
 *  @param education The education to modify
 *  @param amount_of_educations The amount of educations in database
 *  @param filereader The file to read from 
 */
void parseEduLink(struct database* database, char current_line[]){
    int i;
    int offset = 0;

    /* Iterate through all educations */
    for(i = 0; i < database->amount_of_educations; i++){
        database->educations[i].link = parseEduString(current_line, database->amount_of_educations, offset);
        offset += strlen(database->educations[i].link) + 1;
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