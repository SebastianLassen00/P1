#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include "database.h"

void parseDatabase(struct database *database, FILE *filereader);
int parseNumOfEdu(FILE *filereader);
void parseEduNames(struct education *education, int amount_of_educations, FILE *filereader);
void parseEduDesc(struct education *education, int amount_of_educations, FILE *filereader);
void parseEduLink(struct education *education, int amount_of_educations, FILE *filereader);
void parseRegion(struct education *education, int number_of_educations, FILE *filereader);
void parseSubReq(struct education *education, int number_of_educations, FILE *filereader);
void parseGradeReq(struct education *education, int number_of_educations, FILE *filereader);
int strToReg(char* region_string);
char *parseEduString(char* current_line, int amount_of_educations, char* education_string, int offset);

#endif