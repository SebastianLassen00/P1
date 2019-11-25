#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include "database.h"

void parseDatabase(struct database *database, FILE *filereader);
int parseNumOfEdu(FILE *filereader);
void parseEduNames(struct education *education, int amount_of_educations, FILE *filereader);
void parseEduDesc(struct education *education, int amount_of_educations, FILE *filereader);
void parseEduLink(struct education *education, int amount_of_educations, FILE *filereader);
char *parseEduString(char* current_line, int amount_of_educations, char* education_string, int offset);

#endif