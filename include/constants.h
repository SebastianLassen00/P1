/** @file constants.h
 *  @brief Contains symbolic constants used throughout the program
 * 
 *  This header-file contains all of the symbolic constants used throughout the entire program,
 *  such as those relating to the number of regions, the max lenght of strings or constants used for string formatting.
*/  

#ifndef CONSTANTS_H
#define CONSTANTS_H

/* Program version */
#define VERSION "1.0.1"

#define NUMBER_OF_REGIONS 5

/* Subjects related */
#define IMPORTANT_SUBJECTS 5
#define OTHER_SUBJECTS 11
#define LANGUAGE_SUBJECTS 11
#define USELESS_SUBJECTS 2
#define TOTAL_SUBJECTS (IMPORTANT_SUBJECTS + OTHER_SUBJECTS + LANGUAGE_SUBJECTS)

#define MAX_NAME_LENGTH 20
#define MAX_FILE_NAME_LENGTH MAX_NAME_LENGTH + 12
#define EDUCATION_LIST_LENGTH 10
#define MAX_EDU_NAME_LENGTH 40

/* Input */
#define MAX_COMMAND_LENGTH 10
#define MAX_INPUT_LENGTH (MAX_COMMAND_LENGTH + 100)

#define NOT_IN_LIST -1
#define NO_EMPTY_INDEX -1

#define FIELD_SIZE 25

#define ADJUSTMENT_CONSTANT 0.1

#define STRING_MAX_LENGTH 10000
#define TABS '	'
#define NOT_FOUND_STRING " "
#define EDU_MAX_SUBJECTS 10

#define DATABASE_PATH "./bin/data/database.txt"

#endif