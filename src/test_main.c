#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "profile.h"
#include "education.h"
#include "subjects.h"
#include "vector.h" 

#define MAX_COMMAND_LENGTH 10
#define MAX_INPUT_LENGTH (MAX_COMMAND_LENGTH + 100)

enum command{find, save, save_prof, recommend, list, eval, test, menu, quit};
typedef enum command command;


struct profile createProfile(int number_of_interests);
struct qualification createQualifications(int number_of_qualifications);
void freeQualifications(struct qualification q);
void freeProfile(struct profile p);
const char* classNameStr(enum class class);
enum level levelAsValue(char c);
void clearBuffer(void);
void chooseFromList(struct profile user, int interval_start, int interval_end);
double convertScale(int initial_value);
int validScaleValue(int value, int interval_start, int interval_end);

void getValidName(char *name, char *name_array[]);
int isUsed(char name[MAX_NAME_LENGTH], char *name_array[], int number_of_names);
const char* regionName(enum region region);
int getValidInteger(void);




void getValidName(char *name, char *name_array[]){
    int scan_res;

    do{
        printf("Enter correct name\n");
        scan_res = scanf(" %s", name);
    } while(scan_res == 1 && isUsed(name, name_array, 10));
}

int isUsed(char name[MAX_NAME_LENGTH], char *name_array[], int number_of_names){
    int i;

    for(i = 0; i < number_of_names; i++){
        if(strcmp(name, name_array[i]) == 0)
            return 1;
    }

    print("%d", 1 || 0);
    return 0;
}
