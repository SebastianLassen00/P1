#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "profile.h"
#include "education.h"
#include "subjects.h"
#include "vector.h" 
#include "commands.h"

#define NOT_IN_LIST -1

void menuCmd(void){
    printf("Usable commands: \n");
    printf("  find |arg| -  finds the education passed through the argument |arg|                    \n"
           "  save       -  saves the current education to a seperate list                           \n"
           "  save_prof  -  saves the current user profile to a .txt-file                            \n"
           "  recommend  -  recommend an education using the current profile                         \n"
           "  list       -  lists all the saved educations                                           \n"
           "  eval |arg| -  evaluates the current education using an integer value between 0 and 100 \n"
           "  test       -  tests the users interests and qualifications                             \n"
           "  menu       -  shows a this menu                                                        \n"
           "  quit       -  quits the program                                                        \n");
}


/** @fn void testCmd(struct profile user, struct database db)
 *  @brief Tests the current user for name, location, interests, qualifications and average grade
 *  @param user The profile struct where all test results should be saved 
 *  @param db The database where information of interests and subjects are
 */
void testCmd(struct profile user, struct database db){
    int scan_res;
    int initial_value;
    char temp_char;
    char name[MAX_NAME_LENGTH];
    char *names[10] = {"christian", "karl", "sebastian", "simon", "magnus", "steven", "johannes", "nikolai", "børge", "kurt"};

    /*  Introduction  */
    printf("This test will ask you several questions about interests, qualifications and grades\n"
           "The test requires answers in numbers (integers), and where scale is part, a value between 1 and 100\n\n");

    /*  Scan for profile name  */
    setProfileName(user, name, names);

    /*  Get location and assesment  */
    setProfileLocation(user);

    /*  Get all interests  */
    setProfileInterests(user, db);

    /*  Get all qualifications  */
    setProfileQualifications(user);
    
    /*  Get average grade  */
    printf("What is your average grade? ");
    user.average = getValidDouble();

    /*  Ending the test  */
    printf("The test is now concluded. Returning to menu...\n\n");
}

/* **************** TestCmd() functions **************** */

/** @fn void setProfileName(struct profile user, char *name, char **names)
 *  @brief Sets the profile name of the user to the name given to the function
 *  @param user The profile struct where the name should be saved to
 *  @param name The name string given to the function to be saved in user
 *  @param names The list of all names already used
 */
void setProfileName(struct profile user, char *name, char **names){
    printf("Profile name (only one word): ");

    getValidName(name, names);
    strcpy(user.name, name);
}

/** @fn void getValidName(char *name, char **name_array)
 *  @brief Determines whether a name has already been used, and prompts for another if that is the case
 *  @param name The name string to be determined if it is valid
 *  @param names The list of names already used
 */
void getValidName(char *name, char **names){
    int scan_res;

    do{
        printf("Enter correct name\n");
        scan_res = scanf(" %s", name);
    } while(scan_res == 1 && isUsed(name, names, 10));
}

/** @fn int isUsed(char *name, char **names, int number_of_names)
 *  @brief Returns 1 if the name is used. Otherwise, it returns 0
 *  @param name The name string to be determined if has been used
 *  @param names The list of names already used
 *  @param number_of_names The number of names in the name list
 */
int isUsed(char *name, char **names, int number_of_names){
    int i;

    for(i = 0; i < number_of_names; i++){
        if(strcmp(name, names[i]) == 0)
            return 1;
    }
    return 0;
}

/** @fn void setProfileLocation(struct profile user)
 *  @brief Sets the region of choice in user. Saves the interest in studying in this location
 *  @param user The profile struct where the information about location should be saved
 */
void setProfileLocation(struct profile user){
    int i;

    printf("Where do you want to study?\n");
    for(i = 0; i < NUMBER_OF_REGIONS; i++)
        printf("%d: %s   ", i, regionName(i));
    printf("\n");
    user.location.region = validScaleValue(getValidInteger(), 0, NUMBER_OF_REGIONS - 1);

    printf("How important is this region to you\n");
    user.location.region_importance = convertScale(validScaleValue(getValidInteger(), 0, 10));
}

/** @fn const char *regionName(enum region region)
 *  @brief Return the name of the region as a string
 *  @param region The enum region value of the region to be returned as a string
 */
const char *regionName(enum region region){
    char *regions[NUMBER_OF_REGIONS] = {"NORTH JUTLAND", "CENTRAL JUTLAND", "SOUTHERN DENMARK", 
                                        "ZEALAND", "CAPITAL REGION"};
    return regions[region];
}

/** @fn double convertScale(int initial_value)
 *  @brief Returns the converted value
 *  @param initial_value The value to be converted
 */
double convertScale(int initial_value){
    return (((double) v - 5.0) / 5.0);
}

/** @fn int validScaleValue(int value, int interval_start, int interval_end)
 *  @brief Returns a value between interval_start and interval_end. 
 *         If the given value outside the interval it will return the value inside the interval closest the value.
 *         The interval_start must be less than the interval_end
 *  @param value The value to check within the scale
 *  @param interval_start The start value of the scale
 *  @param interval_end The end value the scale
 */
int validScaleValue(int value, int interval_start, int interval_end){
    return (value > interval_end ? interval_end : (value < interval_start ? interval_start : value));
}

/** @fn int getValidInteger(void)
 *  @brief Returns a valid integer given through the terminal
 */
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

/** @fn void setProfileInterests(struct profile user, struct database db)
 *  @brief Saves all interests to user as a converted value (see convertScale)
 *  @param user The profile struct where the interests are saved to
 *  @param db The database struct where information about all interests are saved
 */
void setProfileInterests(struct profile user, struct database db){
    int i;

    printf("Next, a series of interests will be shown\n"
            "You are to give a value between 0 and 10, "
            "where 0 is negative and 10 is positive towards the interest\n");

    for(i = 0; i < interests.size; i++){
        printf("%s:  ", db.interests_string[i]);
        user.interests[i] = convertScale(validScaleValue(getValidInteger(), 0, 10));
    }
}

/** @fn void setProfileQualifications(struct profile user)
 *  @brief Saves all the users qualifications as given by the terminal
 *  @param user The profile struct where the qualifications are saved to
 */
void setProfileQualifications(struct profile user){
    setSubjects(user);
    
    setImportantSubjects(user); 
    
    setOtherSubjects(user, IMPORTANT_SUBJECTS, IMPORTANT_SUBJECTS + OTHER_SUBJECTS);
    setOtherSubjects(user, IMPORTANT_SUBJECTS + OTHER_SUBJECTS, TOTAL_SUBJECTS);
}

/** @fn void setSubjects(struct profile user)
 *  @brief Sets all qualifications in user to match the enum class
 *  @param user The profile struct where the subjects are saved to
 */
void setSubjects(struct profile user){
    int i;

    for(i = 0; i < TOTAL_SUBJECTS; i++)
        user.qualifications.subjects[i].name = i;
}

/** @fn void setImportantSubjects(struct profile user)
 *  @brief Saves all the qualifications for the important subjects
 *  @param user The profile struct where the subjects are saved to
 */
void setImportantSubjects(struct profile user){
    char temp_char;
    int i;

    for(i = 0; i < IMPORTANT_SUBJECTS; i++){
        printf("%s: ", classNameStr(i));
        do{
            scanf(" %c", &temp_char);
        } while(levelAsValue(temp_char) == -1);
        user.qualifications.subjects[i].level = levelAsValue(temp_char);
        clearBuffer();
        printf("\n");
    }
}

/** @fn const char* classNameStr(enum class class)
 *  @brief Returns the name as a string of a class given as an enum class
 *  @param class The enum value the name should return for
 */
const char* classNameStr(enum class class){
    char *classes[TOTAL_SUBJECTS] = {"MATHEMATICS", "CHEMISTRY", "BIOLOGY", "PHYSICS", "ENGLISH",
                                     "BIOTECHNOLOGY", "GEOSCIENCE", "HISTORY", "IDEA_HISTORY",
                                     "INFORMATICS", "INTERNATIONAL_ECONOMICS", "COMMUNICATION_AND_IT",
                                     "RELIGION", "SOCIALSTUDIES", "BUSINESS_ECONOMICS", "CONTEMPORAY_HISTORY",
                                     "FRENCH", "SPANISH", "GERMAN", "CHINESE", "ARABIC", "GREEK", "ITALIAN",
                                     "JAPANESE", "LATIN", "PORTUGESE", "RUSSIAN"};
    return classes[class];
}

/** @fn enum level levelAsValue(char c)
 *  @brief Returns the enum value of a level given as a character
 *  @param c The level as a character to be converted to enum level
 */
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

/** @fn void setOtherSubjects(struct profile user, int start, int end)
 *  @brief Saves all the levels of the other subjects (not the important ones)
 *  @param user The profile struct where the qualifications are to be saved
 *  @param start The start of the subjects to be asked for
 *  @param end The ens of the subjects to be asked for
 */
void setOtherSubjects(struct profile user, int start, int end){
    int i;

    for(i = 0; i < end - start; i++)
        printf("%d: %s\n", i, classNameStr(i + start));
    chooseFromList(user, start, end);
}

/** @fn void chooseFromList(struct profile user, interval_start, interval_end)
 *  @brief Saves the levels of chosen subjects to user
 *  @param user The profile struct where the qualifications should be saved
 *  @param interval_start The start of the interval for the qualifications in the list
 *  @param interval_end The end of the interval for the qualifications in the list
 */
void chooseFromList(struct profile user, int interval_start, int interval_end){
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

/** @fn double getValidDouble(void)
 *  @brief Returns a valid double entered in the terminal
 */
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

/* **************** End of TestCmd() functions **************** */












/* Recommends an education to the user. */
void recommendCmd(struct database database, struct profile user, 
                  struct education *currentEducation){
    int i;
    struct vector results, normalized_vector;
    double highest_result, result;
    struct education best_fit;
    normalized_vector = normalizeVector(addVector(user.interests, user.adjustment_vector));
    
    for(i = 0; i < number_of_educations; i++){
        result = dotProduct(database.educations[i].interests, normalized_vector);
        if(result > highest_result && isQualified(user, database.educations[i])){
            highest_result = result;
            best_fit = educations[i];
        }
    }
    
    *currentEducation = best_fit;
    printEducation(*currentEducation);
}

/** @fn void isQualified(struct profile user, struct education education)
 *  @brief Checks if the user has the subject levels required by the education
 *  @param user The profile struct whose quailification is checked
 *  @param education The education struct with the requirements
 */
void isQualified(struct profile user, struct education education) {
    int i;
    struct subject subject;
    for(i = 0; i < education.required_qualifications.amount_of_subjects; i++) {
        subject = education.required_qualifications.subjects[i];
        if(user.qualifications.subjects[subject.name].level < subject.level) {
            return 0;
        }
    }
    return 1;
}

/* Prints the relavant information about the given education */
void printEducation(struct education education){
    printf("Name of education: %s\n", education.name);
    printf("Description: %s\n", education.description);
    printf("Education is located in: %s\n", );

}


/** @
 *  @
 */
void save(struct education *current_education, struct profile *user){
    int i;

    i = get_index((*user).saved_educations, *user);

    if(list_is_full(i))
        /* the list is full and there has to be deleted an education in order to save one. */
    else
        (*user).saved_educations[i] = *current_education; 
}

/* uses #define EDUCATION_LIST_LENGTH 10 from profile.h */
/** 
 *
 */
int getIndex(struct education edu_array, struct profile user){
    int i = 0, index;
    int index_found = 0;

    for(i = 0; index_found != 1 || i < EDUCATION_LIST_LENGTH; i++){
            if(edu_array[i].name == NULL || edu_array[i].name == ""){
                index_found = 1;
            }
    }

    if(index_found == 0)
        i = NOT_IN_LIST; /* NOT_IN_LIST -1 */

    return i;
}

/** 
 *
 */
int listIsFull(int i){
    return i == NOT_IN_LIST;
}