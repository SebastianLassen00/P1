#include "profile.h"
#include "education.h"
#include "subjects.h"
#include "vector.h" 
#include "database.h"

#ifndef COMMANDS_H
#define COMMANDS_H

void menuCmd(void);

/*  TestCmd()  */
void testCmd(struct profile *user, struct database db);
void setProfileName(struct profile *user, char *name, char **names);
void getValidName(char *name, char **names);
int isUsed(char *name, char **names, int number_of_names);
void setProfileLocation(struct profile *user);
const char *regionName(enum region region);
double convertScale(int initial_value);
int validScaleValue(int value, int interval_start, int interval_end);
int getValidInteger(void);
void setProfileInterests(struct profile *user, struct database db);
void setProfileQualifications(struct profile *user);
void setSubjects(struct profile *user);
void setImportantSubjects(struct profile *user);
const char* classNameStr(enum class class);
enum level levelAsValue(char c);
void setOtherSubjects(struct profile *user, int start, int end);
void chooseFromList(struct profile *user, int interval_start, int interval_end);
double getValidDouble(void);

struct education recommendCmd(struct database database, struct profile *user);
int isQualified(struct profile user, struct education education);

void printEducation(struct education education);

void saveCmd(struct education *current_education, struct profile *user);
int getIndex(char edu_array[EDUCATION_LIST_LENGTH][MAX_EDU_NAME_LENGTH], struct education target);
int getEmptyIndex(char edu_array[EDUCATION_LIST_LENGTH][MAX_EDU_NAME_LENGTH]);
int listIsFull(int i);

void clearBuffer(void);


#endif