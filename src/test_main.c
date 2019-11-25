#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <profile.h>
#include <education.h>
#include <subjects.h>
#include <vector.h> 

#define MAX_COMMAND_LENGTH 10
#define MAX_INPUT_LENGTH (MAX_COMMAND_LENGTH + 100)

enum command{find, save, save_prof, recommend, list, eval, test, menu, exit};
typedef enum command command;


int main(void){
	struct profile user;

	user = createProfile();




	return 0;
}


struct profile createProfile(int number_of_interests){
	struct profile profile;
	char name[MAX_NAME_LENGTH];

	profile.interests = createVector(number_of_interests);
	profile.name = name;
	profile.qualifications = createQualifications(TOTAL_SUBJECTS);
	profile.averafe = 0.0;
	profile.location = {0, 0};

	return profile;
}

struct qualifications createQualifications(int number_of_qualifications){
	struct qualification qualifications;

	qualifications.amount_of_subjects = number_of_qualifications;
	qualifications.subjects = (subject *) calloc(number_of_qualifications, sizeof(subject));

	return qualifications;
}

void freeQualifications(struct qualification q){
	free(q.subjects);
}

void freeProfile(struct profile p){
	freeQualifications(p.qualifications);
	freeVector(p.interests);
}



















void testCmd(struct profile user, struct qualifications subjects){
    int scan_res;
    int initial_value;
    char test_char;

    /*  Introduction to test  */
    printf("This test will ask you several questions about interests, qualifications and grades\n"
           "The test requires answers in numbers (integers), and where scale is part, a value between 1 and 100");

    /*  Scan for profile name  */
    printf("Profile name (only one word): ");
    scan_res = scanf(" %s", profile.name);

    /*  Get location and assesment  */
    printf("Where do you want to study?\n");
    for(i = 0; i < NUMBER_OF_REGIONS; i++)
        printf("%d: %s   ", i, regionName(i));
    printf("\n");
    profile.location.region = validScaleValue(getValidInteger(), 0, NUMBER_OF_REGIONS - 1);

    printf("How important is this region to you\n");
    profile.location.region_importance = validScaleValue(getValidInteger(), 0, 10);

    /*  Get all interests  */
    printf("Next, a series of interests will be shown\n"
           "You are to give a value between 0 and 10, "
           "where 0 is negative and 10 is positive towards the interest\n");

    for(i = 0; i < ; i++){                              // How many interests?
        printf("%s:  ", );                              // Where are the interests saved? 
        initial_value = validScaleValue(getValidInteger(), 0, 10);
        if(initial_value != 0){
            user.interests.array[i] = convertScale(initial_value);
        } else{
            printf("Wrong input, try again\n");
            clearBuffer();
            i--;
        }
    }

    /*  Get important qualifications  */
    for(i = 0; i < IMPORTANT_SUBJECTS; i++){
        printf("%s: ", classNameStr(i));
        do{
            scanf(" %c", temp_char);
        } while(levelAsValue(test_char) == -1);
        user.qualifications.subjects[i].level = levelAsValue(temp_char);
    }

    /*  Get less important qualifications  */
    for(i = 0; i < OTHER_SUBJECTS)
        printf("%d: %s\n", i, classNameStr(i + IMPORTANT_SUBJECTS));
    chooseFromList(user, IMPORTANT_SUBJECTS, IMPORTANT_SUBJECTS + OTHER_SUBJECTS);

    for(i = 0; i < LANGUAGE_SUBJECTS)
        printf("%d: %s\n", i, classNameStr(i + IMPORTANT_SUBJECTS + OTHER_SUBJECTS));
    chooseFromList(user, IMPORTANT_SUBJECTS + OTHER_SUBJECTS, TOTAL_SUBJECTS);

    /*  Get average grade  */
    printf("What is your average grade? ");
    user.average = getValidDouble();

    /*  Ending the test  */
    printf("The test is now concluded. Returning to menu...\n\n");
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

void chooseFromList(struct profile user, interval_start, interval_end){
    int temp_subject, i = 0;
    char temp_char;
    char temp_string[MAX_INPUT_LENGTH];

    do{
        scanf(" %d%c", temp_subject, temp_char);
        if(temp_subject > 0 && temp_subject < (interval_end - interval_start + 1) && levelAsValue(temp_char) != -1) {
            user.qualifications.subjects[temp_subject + interval_start].level = levelAsValue(temp_char);
            i++;
        }
    } while(i < (interval_end - interval_start));
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

double convertScale(int initial_value){
    return (((double) v - 5.0) / 5.0);
}

int validScaleValue(int value, int interval_start, int interval_end){
    return (value > interval_end ? interval_end : (value < interval_start ? interval_start : value));
}

int getValidInteger(void){
    int valid_int = -1, scan_res = 0;
    char test_char = 0;

    do{
        scan_res = scanf(" %d", &valid_int);
        if(scan_res == 0)
            scanf(" %c", &test_char);
    } while(scan_res == 0 || test_char != '\n');

    return valid_int;
}

double getValidDouble(void){
    double valid_double = 0;
    int scan_res = 0;
    char test_char = 0;

    do{
        scan_res = scanf(" %lf", &valid_double);
        if(scan_res == 0)
            scanf(" %c", &test_char);
    } while(scan_res == 0 || test_char != '\n');

    return valid_double;
}