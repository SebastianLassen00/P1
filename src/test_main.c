#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main(void){
    struct profile user;
    int i;
    char temp_char;

    user = createProfile(5);

    user.name = "christian";

    for(i = 0; i < user.interests.size; i++){
        user.interests.array[i] = 0.45 * i;
    }


    for(i = 0; i < IMPORTANT_SUBJECTS; i++){
        printf("%s: ", classNameStr(i));
        do{
            scanf(" %c", &temp_char);
        } while(levelAsValue(temp_char) == -1);
        user.qualifications.subjects[i].name = i;
        user.qualifications.subjects[i].level = levelAsValue(temp_char);
        clearBuffer();
        printf("\n");
    }

    /*  Get less important qualifications  */
    for(i = 0; i < OTHER_SUBJECTS; i++)
        printf("%d: %s\n", i, classNameStr(i + IMPORTANT_SUBJECTS));
    chooseFromList(user, IMPORTANT_SUBJECTS, IMPORTANT_SUBJECTS + OTHER_SUBJECTS);

    for(i = 0; i < LANGUAGE_SUBJECTS; i++)
        printf("%d: %s\n", i, classNameStr(i + IMPORTANT_SUBJECTS + OTHER_SUBJECTS));
    chooseFromList(user, IMPORTANT_SUBJECTS + OTHER_SUBJECTS, TOTAL_SUBJECTS);



    printf("%s\n", user.name);

    printVector(user.interests);

    for(i = 0; i < user.qualifications.amount_of_subjects; i++){
        printf("%s: %d\n", classNameStr(user.qualifications.subjects[i].name), user.qualifications.subjects[i].level);
    }

    freeProfile(user);

    return 0;
}

void chooseFromList(struct profile user, int interval_start, int interval_end){
    int temp_subject, i = 0, scan_res;
    char temp_char;
    char temp_string[MAX_INPUT_LENGTH];
    
    gets(temp_string);

    do{
        scan_res = sscanf(temp_string + i, " %d%c", &temp_subject, &temp_char);
        printf("Scanres: %d\n", scan_res);
        if(temp_subject > 0 && temp_subject < (interval_end - interval_start + 1) && levelAsValue(temp_char) != -1){
            user.qualifications.subjects[temp_subject + interval_start].level = levelAsValue(temp_char);
            i += 2;
        }
    } while(scan_res != EOF);

    printf("Im done\n");
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