/** @file parser.h
 *  @brief Contains elements relating to parsing the database
 * 
 *  <Detailed esription here>
*/  

#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include "database.h"
#include "region.h"

void parseDatabase(struct database *database, FILE *filereader);
void parseDatabaseLine(const char key[], struct database* database, FILE* filereader);
void findDatabaseLine(const char key[], FILE* filereader, char* current_line);

int parseNumOfEdu(FILE *filereader);
int parseNumOfInterests(FILE *filereader);

void parseEduNames(int amount_of_educations, struct education* educations, char current_line[]);    
void parseEduDesc(int amount_of_educations, struct education* educations, char current_line[]);
void parseEduLink(int amount_of_educations, struct education* educations, char current_line[]);
void parseEduRegion(int amount_of_educations, struct education* educations, char current_line[]);
void parseSubReq(int amount_of_educations, struct education* educations, char current_line[]);
void parseReqGrade(int amount_of_educations, struct education* educations, char current_line[]);
void parseInterestNames(struct database* database, FILE* filereader);
void parseInterestValues(int amount_of_interests, int amount_of_educations, struct education* educations, FILE* filereader);

char *parseEduString(char* current_line, int amount_of_educations, int offset); 
char** createArrayOfStrings(int amount_of_strings);

int sseek(char *, char);
void readReqString(struct qualification *, char *, int);

enum region strToReg(char* region_string);

#endif