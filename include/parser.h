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

void parseEduNames(struct database* database, char current_line[]);
void parseEduDesc(struct database* database, char current_line[]);
void parseEduLink(struct database* database, char current_line[]);
void parseEduRegion(struct database* database, char current_line[]);
void parseSubReq(struct education *education, int number_of_educations, FILE *filereader, char current_line[]);
void parseReqGrade(struct database* database, char current_line[]);
void parseInterestValues(struct database* database, FILE* filereader);
void parseInterestNames(struct database* database, FILE* filereader);

char *parseEduString(char* current_line, int amount_of_educations, int offset);

int sseek(char *, char);
void readReqString(struct qualification *, char *, int);

enum region strToReg(char* region_string);



#endif