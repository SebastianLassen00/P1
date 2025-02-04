/** @file commands.h
 *  @brief Contains functions related to command handling
 * 
 *  Contains all of the functions used for handling commands, such as those relating to verifying input and the functions that act on receiving a command.
*/ 

#ifndef COMMANDS_H
#define COMMANDS_H

#include "profile.h"
#include "education.h"
#include "subjects.h"
#include "vector.h" 
#include "database.h"


void menuCmd(void);

/*  SurveyCmd()  */
void surveyCmd(struct profile *user, const struct database *db);
int getProfileName(struct profile *user, char *name);
void setProfileLocation(struct profile *user);
double convertScale(int initial_value);
int validScaleValue(int value, int interval_start, int interval_end);
int getValidInteger(void);
void setProfileInterests(struct profile *user, const struct database *db);
void setProfileQualifications(struct profile *user);
void setSubjects(struct profile *user);
void setImportantSubjects(struct profile *user);
const char* classNameStr(enum class class);
enum level levelAsValue(char c);
void setOtherSubjects(struct profile *user, int start, int end);
void chooseFromList(struct profile *user, int interval_start, int interval_end);
double getValidDouble(void);

void evalCmd(struct profile *user, struct education *current_education, int arg);
struct education findCmd(char *arg, const struct database *db);
void searchCmd(char *arg, const struct database *db);
struct education recommendCmd(struct profile *user, const struct database *database);
int isQualified(struct profile user, struct education education);
void toUppercase(char *string);

const char *getRegionName(enum region r);
void printEducation(struct education education);
void saveCmd(struct profile *user, struct education *current_education);
int getIndex(char edu_array[EDUCATION_LIST_LENGTH][MAX_EDU_NAME_LENGTH], struct education target);
int getEmptyIndex(char edu_array[EDUCATION_LIST_LENGTH][MAX_EDU_NAME_LENGTH]);
int listIsFull(int i);

void clearBuffer(void);

void listCmd(const struct profile *user);
void deleteCmd(struct profile *user, int deleted_entry);

void saveProfile(struct profile user);
int checkProfile(const char name[]);
struct profile loadProfile(char *name, int number_of_interests);

#endif