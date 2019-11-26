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

int main(void){
    struct profile user;
    int i;
    char temp_char;
    char name[MAX_NAME_LENGTH];
    char *names[10] = {"christian", "karl", "sebastian", "simon", "magnus", "steven", "johannes", "nikolai", "børge", "kurt"};

    user = createProfile(5);

    printf("This test will ask you several questions about interests, qualifications and grades\n"
           "The test requires answers in numbers (integers), and where scale is part, a value between 1 and 100");

    /*  Scan for profile name  */
    printf("Profile name (only one word): ");
    
    getValidName(name, names);
    printf("Name is: %s\n", name);

    user.name = name;
    
    /*  Get location and assesment  */
    printf("Where do you want to study?\n");
    for(i = 0; i < NUMBER_OF_REGIONS; i++)
        printf("%d: %s   ", i, regionName(i));
    printf("\n");
    user.location.region = validScaleValue(getValidInteger(), 0, NUMBER_OF_REGIONS - 1);

    printf("How important is this region to you\n");
    user.location.region_importance = convertScale(validScaleValue(getValidInteger(), 0, 10));



/*
    user.name = "christian";
    for(i = 0; i < user.interests.size; i++){
        user.interests.array[i] = 0.45 * i;
    }

    
    for(i = -5; i < 15; i++){
        printf("Case C%d: %lf\n", i, convertScale(validScaleValue(i, 0, 10)));
    }



    printf("%s\n", user.name);
    printVector(user.interests);
    for(i = 0; i < user.qualifications.amount_of_subjects; i++){
        printf("%s: %d\n", classNameStr(user.qualifications.subjects[i].name), user.qualifications.subjects[i].level);
    }
    */

    printf("Name: %s\n", user.name);
    printf("Region: %s\n", regionName(user.location.region));
    printf("Region Importance: %lf\n", user.location.region_importance);

    freeProfile(user);

    return 0;
}


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

    return 0;
}

const char* regionName(enum region region){
    char *regions[NUMBER_OF_REGIONS] = {"NORTH JUTLAND", "CENTRAL JUTLAND", "SOUTHERN DENMARK", 
                                        "ZEALAND", "CAPITAL REGION"};
    return regions[region];
}

int getValidInteger(void){
    int valid_int = -1, scan_res = 0;
    char test_char = 0;

    do{
        scan_res = scanf(" %d", &valid_int);
        if(scan_res == 0)
            scanf(" %c", &test_char);
    } while(scan_res == 0 && test_char != '\n');

    return valid_int;
}










double convertScale(int initial_value){
        return (((double) initial_value - 5.0) / 5.0);
    }

int validScaleValue(int value, int interval_start, int interval_end){
    return (value > interval_end ? interval_end : (value < interval_start ? interval_start : value));
}





void chooseFromList(struct profile user, int interval_start, int interval_end){
    int temp_subject, i = 0, scan_res;
    char temp_char;
    char temp_string[MAX_INPUT_LENGTH];
    
    gets(temp_string);

    do{
        scan_res = sscanf(temp_string + i, " %d%c", &temp_subject, &temp_char);
        if(temp_subject > 0 && temp_subject < (interval_end - interval_start + 1) && levelAsValue(temp_char) != -1  && scan_res == 2){
            user.qualifications.subjects[temp_subject + interval_start].level = levelAsValue(temp_char);
            i += 1;
            while(isalnum(*(temp_string + ++i)) == 0);
        }
    } while(scan_res > 0);
}


struct profile createProfile(int number_of_interests){
    struct profile profile;
    char name[MAX_NAME_LENGTH];

    profile.interests = createVector(number_of_interests);
    profile.name = name;
    profile.qualifications = createQualifications(TOTAL_SUBJECTS);
    profile.average = 0.0;
    profile.location.region = 0;
    profile.location.region_importance = 0;

    return profile;
}

struct qualification createQualifications(int number_of_qualifications){
    struct qualification qualifications;

    qualifications.amount_of_subjects = number_of_qualifications;
    qualifications.subjects = (struct subject*) calloc(number_of_qualifications, sizeof(struct subject));

    return qualifications;
}

void freeQualifications(struct qualification q){
    free(q.subjects);
}

void freeProfile(struct profile p){
    freeQualifications(p.qualifications);
    freeVector(p.interests);
}

const char* classNameStr(enum class class){
    char *classes[TOTAL_SUBJECTS] = {"MATHEMATICS", "CHEMISTRY", "BIOLOGY", "PHYSICS", "ENGLISH",
                                     "BIOTECHNOLOGY", "GEOSCIENCE", "HISTORY", "IDEA_HISTORY",
                                     "INFORMATICS", "INTERNATIONAL_ECONOMICS", "COMMUNICATION_AND_IT",
                                     "RELIGION", "SOCIALSTUDIES", "BUSINESS_ECONOMICS", "CONTEMPORAY_HISTORY",
                                     "FRENCH", "SPANISH", "GERMAN", "CHINESE", "ARABIC", "GREEK", "ITALIAN",
                                     "JAPANESE", "LATIN", "PORTUGESE", "RUSSIAN"};
    return classes[class];
}

enum level levelAsValue(char c){
    enum level return_value = -1;

    switch(c){
        case 'A': case 'a':
            return_value = A;
            break;
        case 'B': case 'b':
            return_value = B;
            break;
        case 'C': case 'c':
            return_value = C;
            break;
        case 'Z': case 'z':
            return_value = Z;
            break;
        default:
            return_value = -1;
    }
    return return_value;
}

void clearBuffer(void){
    char bin[MAX_INPUT_LENGTH];
    gets(bin);
}

/*


*/
