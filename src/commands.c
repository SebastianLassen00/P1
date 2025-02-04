#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "profile.h"
#include "education.h"
#include "subjects.h"
#include "vector.h" 
#include "commands.h"
#include "constants.h"


/** @fn void menuCmd(void)
 *  @brief Prints all the possible commands the user can use
 */
void menuCmd(void){
    printf("Usable commands: \n");
    printf("    find |arg|   -  finds the education passed through the argument |arg| \n"
           "    search |arg| -  lists the educations similar to the argument |arg| \n"
           "    load |arg|   -  loads a saved profile from a file matching the pattern |arg|_profile.txt \n"
           "    save         -  saves the current education to a seperate list \n"
           "    save_prof    -  saves the current user profile to a .txt-file \n"
           "    recommend    -  recommend an education using the current profile \n");
    printf("    list         -  lists all the saved educations \n"
           "    eval |arg|   -  evaluates the current education using an integer value between 0 and 10 \n"
           "    survey       -  surveys the users interests and qualifications \n"
           "    menu         -  shows this menu \n"
           "    delete |arg| -  deletes the entry in the list given as an integer by the user \n"
           "    quit         -  quits the program \n\n");
}


/** @fn void surveyCmd(struct profile *user, const struct database *db)
 *  @brief Tests the current user for name, location, interests, qualifications and average grade
 *  @param user The profile struct where all survey results are saved 
 *  @param db The database where information of interests and subjects are as a pointer
 */
void surveyCmd(struct profile *user, const struct database *db){
    char name[MAX_NAME_LENGTH];
    int continue_survey = 0;

    /*  Introduction  */
    printf("This survey will ask you several questions about interests, qualifications and grades\n"
           "The survey requires answers in numbers (integers), and where scale is part, a value between 1 and 10\n\n");

    /*  Scan for profile name  */
    continue_survey = getProfileName(user, name);
    if(continue_survey == 0)
        return;

    /*  Get location and assesment  */
    setProfileLocation(user);

    /*  Get all interests  */
    setProfileInterests(user, db);

    /*  Get all qualifications  */
    setProfileQualifications(user);
    
    /*  Get average grade  */
    printf("What is your average grade? ");
    user->average = getValidDouble();

    /*  Ending the survey  */
    printf("The survey has now concluded. Returning to menu...\n\n");
}

/* **************** SurveyCmd() functions **************** */

/** int getProfileName(struct profile *user, char *name)
 *  @brief prompts for name, scans/checks name and has return value indicating whether or not the survet should be stopped.
 *  @param user Assigning a name to the user: user->name
 *  @param name The name of the user
 */
int getProfileName(struct profile *user, char *name){
    char choice;
    
    printf("Profile name: ");
    scanf("%s", name);
    if(checkProfile(name) == 1){
        printf("Profile name is in use. Stop survey? (Y/N)\n");
        scanf(" %c", &choice);
        if(choice == 'Y' || choice == 'y'){
            printf("Survey stopped\n\n");
            return 0;
        }
    }
    strcpy(user->name, name);

    clearBuffer();

    return 1;
}

/** @fn void setProfileLocation(struct profile *user)
 *  @brief Sets the region of choice in user. Saves the interest in studying in this location
 *  @param user The profile struct where the information about location should be saved
 */
void setProfileLocation(struct profile *user){
    int i;

    printf("Where do you want to study?\n");
    for(i = 0; i < NUMBER_OF_REGIONS; i++)
        printf("%d: %s   ", i, getRegionName(i));
    printf("\n");
    user->location.region = validScaleValue(getValidInteger(), 0, NUMBER_OF_REGIONS - 1);

    printf("How important is this region to you\n");
    user->location.region_importance = (convertScale(validScaleValue(getValidInteger(), 0, 10)) + 1.0) / 2.0;
}

/** @fn double convertScale(int v)
 *  @brief Returns the converted value
 *  @param v The value to be converted
 *  @return A double value between -1 and 1 given that the input is between 0 and 10
 */
double convertScale(int v){
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

    clearBuffer();

    return valid_int;
}

/** @fn void setProfileInterests(struct profile *user, const struct database *db)
 *  @brief Saves all interests to user as a converted value (see convertScale)
 *  @param user The profile struct where the interests are saved to
 *  @param db The database struct where information about all interests are saved as a pointer
 */
void setProfileInterests(struct profile *user, const struct database *db){
    int i;

    printf("Next, a series of interests will be shown\n"
            "You are to give a value between 0 and 10, "
            "where 0 is negative and 10 is positive towards the interest\n");

    for(i = 0; i < db->amount_of_interests; i++){
        printf("%s:%*s ", db->interest_string[i], (int) (FIELD_SIZE - strlen(db->interest_string[i])), "");
        user->interests.array[i] = convertScale(validScaleValue(getValidInteger(), 0, 10));
    }
    printf("\n\n\n");
}

/** @fn void setProfileQualifications(struct profile *user)
 *  @brief Saves all the users qualifications as given by the terminal
 *  @param user The profile struct where the qualifications are saved to
 */
void setProfileQualifications(struct profile *user){
    setSubjects(user);
    
    printf("Your qualifications regarding subjects from high school will now be tested\n"
           "Give a level from A, B, C or Z if you have not had the subject\n");

    setImportantSubjects(user); 
    
    printf("Now some less relevant subjects will be \n");
    printf("Press 'enter' to skip this part. This will set all subject levels to default (zero)\n");
    printf("Set some or all subejcts, choose subject (a number) and write level (a, b, c or z)\n");
    printf("for the given subject. It has to have the form: number+level, e.g. '0z 4c' will set \n");
    printf("BIOTECHNOLOGY to level=z and INFORMATICS to level=4 and all other subjects will have \nlevel=z\n");

    setOtherSubjects(user, IMPORTANT_SUBJECTS, IMPORTANT_SUBJECTS + OTHER_SUBJECTS);
    setOtherSubjects(user, IMPORTANT_SUBJECTS + OTHER_SUBJECTS, TOTAL_SUBJECTS);
}

/** @fn void setSubjects(struct profile *user)
 *  @brief Sets all qualifications in user to match the enum class
 *  @param user The profile struct where the subjects are saved to
 */
void setSubjects(struct profile *user){
    int i;

    for(i = 0; i < TOTAL_SUBJECTS; i++)
        user->qualifications.subjects[i].name = i;
}

/** @fn void setImportantSubjects(struct profile *user)
 *  @brief Saves all the qualifications for the important subjects
 *  @param user The profile struct where the subjects are saved to
 */
void setImportantSubjects(struct profile *user){
    char temp_char;
    int i;

    for(i = 0; i < IMPORTANT_SUBJECTS; i++){
        printf("%s:%*s ", classNameStr(i), (int) (FIELD_SIZE - strlen(classNameStr(i))), "");
        do{
            scanf(" %c", &temp_char);
        } while(levelAsValue(temp_char) == -1);
        user->qualifications.subjects[i].level = levelAsValue(temp_char);
        clearBuffer();
    }
}

/** @fn const char* classNameStr(enum class class)
 *  @brief Returns the name as a string of a class given as an enum class
 *  @param class The enum value the name should return for
 */
const char* classNameStr(enum class class){
    char *classes[TOTAL_SUBJECTS + USELESS_SUBJECTS] = {"MATHEMATICS", "CHEMISTRY", "BIOLOGY", "PHYSICS", "ENGLISH",
                                     "BIOTECHNOLOGY", "GEOSCIENCE", "HISTORY", "IDEA_HISTORY",
                                     "INFORMATICS", "INTERNATIONAL_ECONOMICS", "COMMUNICATION_AND_IT",
                                     "RELIGION", "SOCIALSTUDIES", "BUSINESS_ECONOMICS", "CONTEMPORAY_HISTORY",
                                     "FRENCH", "SPANISH", "GERMAN", "CHINESE", "ARABIC", "GREEK", "ITALIAN",
                                     "JAPANESE", "LATIN", "PORTUGESE", "RUSSIAN", "NONE", "DANISH"};
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

/** @fn void setOtherSubjects(struct profile *user, int start, int end)
 *  @brief Saves all the levels of the other subjects (not the important ones)
 *  @param user The profile struct where the qualifications are to be saved
 *  @param start The start of the subjects to be asked for
 *  @param end The ens of the subjects to be asked for
 */
void setOtherSubjects(struct profile *user, int start, int end){
    int i;

    for(i = 0; i < end - start; i++)
        printf("%d: %s\n", i, classNameStr(i + start));
    chooseFromList(user, start, end);
}

/** @fn void chooseFromList(struct profile *user, int interval_start, int interval_end)
 *  @brief Saves the levels of chosen subjects to user
 *  @param user The profile struct where the qualifications should be saved
 *  @param interval_start The start of the interval for the qualifications in the list
 *  @param interval_end The end of the interval for the qualifications in the list
 */
void chooseFromList(struct profile *user, int interval_start, int interval_end){
    int temp_subject, i = 0, scan_res, length_string;
    char temp_char;
    char temp_string[MAX_INPUT_LENGTH];

    fgets(temp_string, MAX_INPUT_LENGTH - 1, stdin);
    length_string = strlen(temp_string);

    if(length_string < 2)
        return;

    do{
        scan_res = sscanf(temp_string + i, " %d%c", &temp_subject, &temp_char);
        if(temp_subject >= 0 && temp_subject < (interval_end - interval_start + 1) && levelAsValue(temp_char) != -1  && scan_res == 2){
            user->qualifications.subjects[temp_subject + interval_start].level = levelAsValue(temp_char);
            i += 1;
            while(i < length_string && isalnum(*(temp_string + ++i)) == 0);
        }
    } while(i < length_string && scan_res != 0);
}

/** @fn double getValidDouble(void)
 *  @brief Returns a valid double entered in the terminal
 */
double getValidDouble(void){
    double valid_double = 0.0;
    int scan_res = 0;
    char test_char = 0;

    do{
        scan_res = scanf(" %lf", &valid_double);
        if(scan_res == 0)
            scanf(" %c", &test_char);
    } while(scan_res == 0 && test_char != '\n');

    clearBuffer();

    return valid_double;
}

/** @fn struct education findCmd(char *arg, const struct database *db)
 *  @brief Finds and prints out the education with the exact name given
 *         as and argument
 *  @param arg The argument string which should be the name of an education
 *  @param database The database in which all educations are stored
 *  @return A struct for the education found
 */
struct education findCmd(char *arg, const struct database *db){
    int i, edu_found = 0;
    struct education edu;
    toUppercase(arg);
    for(i = 0; i < db->amount_of_educations; i++){
        if(strcmp(arg, db->educations[i].name) == 0){
            edu = db->educations[i];
            edu_found = 1;
        }
    }
    if(edu_found) 
        printEducation(edu);
    else{
        printf("No education exists by that name\n");
        edu = createDefaultEducation(db->amount_of_interests, db->amount_of_educations);
    }

    return edu;
}

/** @fn void searchCmd(char *arg, const struct database *db)
 *  @brief Finds and prints out the educations whose name contains the
 *         given argument.
 *  @param arg The argument string which should be contained in the name of an education
 *  @param database The database in which all educations are stored.
 */
void searchCmd(char *arg, const struct database *db){
    int i, edu_found = 0;
    toUppercase(arg);
    for(i = 0; i < db->amount_of_educations; i++){
        if(strstr(db->educations[i].name, arg) != NULL) {
            printf("    %s\n", db->educations[i].name);
            edu_found = 1;
        }
    }
    if(edu_found) 
        printf("Use the \"find\" command to look up your desired education\n");
    else
        printf("No education exists by that name\n");
}

/** @fn void toUppercase(char *string)
 *  @brief Converts a string to uppercase
 *  @param string The string to be converted
 */
void toUppercase(char *string){
    int i;

    for(i = 0; i < strlen(string); i++)
        string[i] = toupper(string[i]);
}

/** @fn void evalCmd(struct profile *user, struct education *current_education, int arg)
 *  @brief Changes the adjustment vector for the user to approach the current education. 
 *         The distance of the change is determined by the argument
 *  @param current_education The education currently being displayed
 *  @param user The profile struct whose adjustment vector is changed
 *  @param arg The user input argument for how much to change the adjustment vector
 */
void evalCmd(struct profile *user, struct education *current_education, int arg){
    struct vector user_vector = addVector(user->interests, user->adjustment_vector);
    struct vector distance_vector = subtractVector(current_education->interests, user_vector);
    struct vector scale_vector = scaleVector(distance_vector, ADJUSTMENT_CONSTANT * convertScale(arg));
    
    user->adjustment_vector = addVector(user->adjustment_vector, scale_vector);

    freeVectorM(3, user_vector, distance_vector, scale_vector);
}

/** @fn struct education recommendCmd(struct profile *user, const struct database *database)
 *  @brief Goes trough the available educations and compares them to the user:
 *         Both their interests, qualifications and location are considered.
 *  @param user The profile struct which is compared
 *  @param database The database containing the educations
 *  @return A struct for the recommended education.
 */
struct education recommendCmd(struct profile *user, const struct database *database){
    int i;
    struct vector normalized_vector;
    double highest_result = -3.0, result = 0.0;
    struct education best_fit;
    struct vector add_vector = addVector(user->interests, user->adjustment_vector);
    normalized_vector = normalizeVector(add_vector);

    for(i = 0; i < database->amount_of_educations; i++){
        result = dotProduct(database->educations[i].interests, normalized_vector) + 
                 (1.0 - (double) abs(user->location.region - database->educations[i].region)) * 
                  user->location.region_importance;
        if(result > highest_result && user->average >= database->educations[i].required_grade &&
           isQualified(*user, database->educations[i]) && 
           getIndex(user->recommended_educations, database->educations[i]) == NOT_IN_LIST){
            highest_result = result;
            best_fit = database->educations[i];
        }
    }

    freeVectorM(2, add_vector, normalized_vector);
    
    if(highest_result == -3.0){
        best_fit = createDefaultEducation(database->amount_of_interests, TOTAL_SUBJECTS);
        printf("Unfortunately, you are not qualified for anything.\n");
    } else {
        strcpy(user->recommended_educations[user->last_recommended], best_fit.name);
        user->last_recommended = (user->last_recommended + 1) % EDUCATION_LIST_LENGTH;

        printf("\nThe recommended education is:");
        printEducation(best_fit);
    }
    
    return best_fit;
}

/** @fn int isQualified(struct profile user, struct education education)
 *  @brief Checks if the user has the subject levels required by the education
 *  @param user The profile struct whose quailification is checked
 *  @param education The education struct with the requirements
 *  @return 0 if the user does not have the required levels and 1 if the user does
 */
int isQualified(struct profile user, struct education education){
    int i;
    struct subject subject;
    for(i = 0; i < education.required_qualifications.amount_of_subjects; i++){
        subject = education.required_qualifications.subjects[i];
        if(user.qualifications.subjects[subject.name].level < subject.level) 
            return 0;
    }
    return 1;
}

/** @fn void printEducation(struct education education)
 *  @brief Prints the relavant information about the given education
 *  @param education The education struct which whose information is printed
 */
void printEducation(struct education education){
    int i;
    
    printf("\n    Name of education:         %s\n", education.name);
    printf("    Description:               %s\n", education.description);
    printf("    Read more:                 %s\n", education.link);
    printf("    Region:                    %s\n", getRegionName(education.region));
    printf("    Required average grade:    %.1f\n", education.required_grade);

    printf("    Required Subjects: \n");
    for(i = 0; i < education.required_qualifications.amount_of_subjects; i++){
        printf("        %s:%*s %c\n", classNameStr(education.required_qualifications.subjects[i].name), 
                              (int) (FIELD_SIZE - 4 - strlen(classNameStr(education.required_qualifications.subjects[i].name))), "",
                              levelToChar(education.required_qualifications.subjects[i].level));
    }

    printf("\n");
}

/** @fn const char *getRegionName(enum region r)
 *  @brief Returns the name of the region as a string
 *  @param r The enum region value of the region to be returned as a string
 */
const char *getRegionName(enum region r){
    switch(r){
        case NORTH_JUTLAND:
            return "North Jutland";
        case CENTRAL_JUTLAND:
            return "Central Jutland";
        case SOUTHERN_DENMARK:
            return "Southern Denmark";
        case ZEALAND:
            return "Zealand";
        case CAPITAL_REGION:
            return "Capital Region";
        default:
            return "Region Not Found";
    }
}

/** @fn void saveCmd(struct profile *user, struct education *current_education)
 *  @brief Saves the given education to a list in the profile struct
 *  @param current_education A pointer to an education
 *  @param user The profile struct of the user in which the education is saved
 */
void saveCmd(struct profile *user, struct education *current_education){
    int i;

    i = getEmptyIndex(user->saved_educations);

    if(getIndex(user->saved_educations, *current_education) != -1)
        printf("Already in list\n");
    else if(listIsFull(i))
        printf("List empty. Use delete to delete entries\n");
    else
        strcpy(user->saved_educations[i], current_education->name); 
}

/** @fn int getIndex(char edu_array[EDUCATION_LIST_LENGTH][MAX_EDU_NAME_LENGTH], struct education target)
 *  @brief Returns the index of the given target in the array
 *  @param edu_array An array of strings
 *  @param target An education whose name is to be found in the array
 */
int getIndex(char edu_array[EDUCATION_LIST_LENGTH][MAX_EDU_NAME_LENGTH], struct education target){
    int i = 0;
    int index = NOT_IN_LIST;

    for(i = 0; index == NOT_IN_LIST && i < EDUCATION_LIST_LENGTH; i++){
        if(strcmp(edu_array[i], target.name) == 0){
            index = i;
        }
    }

    return index;
}

/** @fn int getEmptyIndex(char edu_array[EDUCATION_LIST_LENGTH][MAX_EDU_NAME_LENGTH])
 *  @brief Returns an index with an empty string in the given array
 *  @param edu_array An array of strings in which the empty string should be found
 */
int getEmptyIndex(char edu_array[EDUCATION_LIST_LENGTH][MAX_EDU_NAME_LENGTH]){
    int i = 0;
    int index = NO_EMPTY_INDEX;

    for(i = 0; index == NO_EMPTY_INDEX && i < EDUCATION_LIST_LENGTH; i++){
        if(strcmp(edu_array[i], "") == 0){
            index = i;
        }
    }

    return index;
}

/** @fn int listIsFull(int i)
 *  @brief A logical statement that returns a boolean value
 *  @param i The index of an array of education structs
 *  @Return 1 if the index is -1 and 0 otherwise
 */
int listIsFull(int i){
    return i == NO_EMPTY_INDEX;
}

/** @fn void clearBuffer(void)
 *  @brief Empties the buffer for standard input
 */
void clearBuffer(void){
    char buffer = ' ';

    while(!feof(stdin) && buffer != EOF && buffer != '\n')
        buffer = getchar();
}

/** @fn void listCmd(const struct profile *user)
 *  @brief Prints out the names of all the saved educations
 *  @param user The profile struct for the user
 */
void listCmd(const struct profile *user){
    int i, counter = 0;

    printf("\nList of saved educations:\n");
    for(i = 0; i < EDUCATION_LIST_LENGTH; i++){
        if(strcmp(user->saved_educations[i], "") != 0){
            printf("%2d: %s\n", i, user->saved_educations[i]);
            counter++;
        }
    }

    if(counter == 0)
        printf("No entries yet\n\n");
}

/** @fn void deleteCmd(struct profile *user, int deleted_entry)
 *  @brief Removes the name of the education at the given index
 *  @param user The profile struct for the user
 */
void deleteCmd(struct profile *user, int deleted_entry){
    strcpy(user->saved_educations[validScaleValue(deleted_entry, 0, EDUCATION_LIST_LENGTH)], "");
}

/** @fn void saveProfile(struct profile user)
 *  @brief Saves a file with the information collected about the user
 *  @param user The profile struct for the user
 */
void saveProfile(struct profile user){
    FILE *file_pointer;
    int i;
    char path_to_profile[MAX_PATH_LENGTH + MAX_FILE_NAME_LENGTH];

    sprintf(path_to_profile, "%s/%s_profil.txt", PROFILE_PATH, user.name);

    file_pointer = fopen(path_to_profile, "w");

    if(file_pointer != NULL){                     /* Checks if file could be opened */
        fprintf(file_pointer, "%s %s %f %d %f %d\n", VERSION, user.name, user.average, 
                user.location.region, user.location.region_importance, user.last_recommended);

        fprintf(file_pointer, "Saved\n");
        for (i = 0; i < EDUCATION_LIST_LENGTH; i++)
            fprintf(file_pointer, "%s\n", user.saved_educations[i]);

        fprintf(file_pointer, "Recommend\n");
        for (i = 0; i < EDUCATION_LIST_LENGTH; i++)
            fprintf(file_pointer, "%s\n", user.recommended_educations[i]);

        fprintf(file_pointer, "Interests\n");
        for (i = 0; i < user.interests.size; i++)
            fprintf(file_pointer, "%f\n", user.interests.array[i]);
        
        fprintf(file_pointer, "Adjustment\n");
        for (i = 0; i < user.adjustment_vector.size; i++)
            fprintf(file_pointer, "%f\n", user.adjustment_vector.array[i]);

        fprintf(file_pointer, "Qualifications\n");
        for(i = 0; i < TOTAL_SUBJECTS; i++)
            fprintf(file_pointer, "%d\n", user.qualifications.subjects[i].level);       
    } else{
        printf("File could not be opened");
        exit(EXIT_FAILURE);
    }
    fclose(file_pointer);

    printf("File saved successfully\n\n");
}

/** @fn int checkProfile(const char name[]) 
 *  @brief Check whether a profile exists
 *  @param char *name The name of the user
 *  @return int A boolean value, 1 if the profile exist, otherwise 0
 */
int checkProfile(const char name[]){
    FILE* fp;
    char file_name[MAX_FILE_NAME_LENGTH];
    char path_to_profile[MAX_FILE_NAME_LENGTH + MAX_PATH_LENGTH];

    sprintf(file_name, "%s_profil.txt", name);
    sprintf(path_to_profile, "%s/%s", PROFILE_PATH, file_name);

    fp = fopen(path_to_profile, "r");

    if(fp == NULL){
        return 0;
    }

    fclose(fp);

    return 1;
}

/** @fn struct profile loadProfile(char *name, int number_of_interests) 
 *  @brief Loads a user profile from a generated <name>_profile.txt file
 *  @param char *name The name of the user
 *  @param int number_of_interests The number of interests which is a member of the database struct
 *  @return struct profile Returns a user profile
 */
struct profile loadProfile(char *name, int number_of_interests){
    int i;
    FILE *file_pointer; 
    struct profile user;
    char path_to_profile[MAX_PATH_LENGTH + MAX_FILE_NAME_LENGTH];
    char version[MAX_FILE_NAME_LENGTH];
    char buffer[MAX_INPUT_LENGTH] = "Ingenting";

    sprintf(path_to_profile, "%s/%s_profil.txt", PROFILE_PATH, name);

    file_pointer = fopen(path_to_profile, "r");

    if(file_pointer == NULL){
        printf("File could not be opened");
        exit(EXIT_FAILURE);
    } 

    user = createProfile(number_of_interests);

    fscanf(file_pointer, "%s %s %lf %d %lf %d\n", version, user.name, &user.average, 
           (int*)&user.location.region, &user.location.region_importance, &user.last_recommended);

    fgets(buffer, MAX_INPUT_LENGTH, file_pointer);
    for (i = 0; i < EDUCATION_LIST_LENGTH; i++){
        fgets(buffer, MAX_INPUT_LENGTH, file_pointer);
        sscanf(buffer, "%[^\n]s", user.saved_educations[i]);
    }

    fgets(buffer, MAX_INPUT_LENGTH, file_pointer);
    for (i = 0; i < EDUCATION_LIST_LENGTH; i++){
        fgets(buffer, MAX_INPUT_LENGTH, file_pointer);
        sscanf(buffer, "%[^\n]s", user.recommended_educations[i]);
    }

    fgets(buffer, MAX_INPUT_LENGTH, file_pointer);
    for (i = 0; i < user.interests.size; i++){
        fgets(buffer, MAX_INPUT_LENGTH, file_pointer);
        sscanf(buffer, "%lf", &user.interests.array[i]);
    }

    fgets(buffer, MAX_INPUT_LENGTH, file_pointer);  
    for (i = 0; i < user.adjustment_vector.size; i++){
        fgets(buffer, MAX_INPUT_LENGTH, file_pointer);
        sscanf(buffer, "%lf", &user.adjustment_vector.array[i]);
    }

    fgets(buffer, MAX_INPUT_LENGTH, file_pointer);   
    for (i = 0; i < user.qualifications.amount_of_subjects; i++){
        fgets(buffer, MAX_INPUT_LENGTH, file_pointer);
        sscanf(buffer, "%d", (int*)&user.qualifications.subjects[i].level);
    }

    fclose(file_pointer);

    printf("Profile successfully loaded.\n\n");

    return user;
}
