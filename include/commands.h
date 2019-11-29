#include "profile.h"
#include "education.h"
#include "subjects.h"
#include "vector.h" 
#include "database.h"

#ifndef COMMANDS_H
#define COMMANDS_H
#define NOT_IN_LIST -1
#define NO_EMPTY_INDEX -1
#define MAX_COMMAND_LENGTH 10
#define MAX_INPUT_LENGTH (MAX_COMMAND_LENGTH + 100)

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

void saveCmd(struct education *current_education, struct profile *user);
int getIndex(struct education edu_array[], struct education target);
int getEmptyIndex(struct education edu_array[]);
int listIsFull(int i);


#endif