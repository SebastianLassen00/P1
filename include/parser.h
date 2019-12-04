#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include "database.h"
#include "region.h"

void parseDatabase(struct database *database, FILE *filereader);
int parseNumOfEdu(FILE *filereader);
void parseEduNames(struct education *education, int amount_of_educations, FILE *filereader);
void parseEduDesc(struct education *education, int amount_of_educations, FILE *filereader);
void parseEduLink(struct education *education, int amount_of_educations, FILE *filereader);
void parseRegion(struct education *education, int number_of_educations, FILE *filereader);
void parseSubReq(struct education *education, int number_of_educations, FILE *filereader);
void parseGradeReq(struct education *education, int number_of_educations, FILE *filereader);
enum region strToReg(char* region_string);
char *parseEduString(char* current_line, int amount_of_educations, int offset);
void parseInterestValues(struct education *education, int number_of_educations, int number_of_interests, FILE *filereader);
int parseNumOfInterests(FILE *filereader);
int sseek(char *, char);
void readReqString(struct qualification *, char *, int);
void parseInterestNames(struct database* database, FILE* filereader);

#endif