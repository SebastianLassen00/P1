#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <profile.h>
#include <education.h>
#include <subjects.h>
#include <vector.h> 

#define MAX_COMMAND_LENGTH 10
#define MAX_INPUT_LENGTH (MAX_COMMAND_LENGTH + 100)

enum command{find, save, save_prof, recommend, list, eval, test, menu, quit};
typedef enum command command;

int argType(command c);
void menuCmd(void);
command scanCommand(char arg[MAX_INPUT_LENGTH], int *arg_num);
command convertCommand(char s[MAX_COMMAND_LENGTH]);
void recommendCmd(struct educations *educations, struct profile user, 
                  struct education *currentEducation);

/*int main(void){
    char arg[MAX_INPUT_LENGTH], arg_type[MAX_INPUT_LENGTH];
    int arg_num = 0, number_of_educations;
    command c;
    struct education *educations, currentEducation;
    struct profile user;
    struct qualifications subjects;
    char **

    menuCmd();

    do{
        c = scanCommand(arg, &arg_num);
        handleCommand(c, arg, arg_num, user, subjects, educations, 
                      number_of_educations, &currentEducation);
    } while(c != quit);


    return 0;
}
*/
void handleCommand(command c, char arg[MAX_INPUT_LENGTH], int arg_num, 
                   struct profile user, struct qualifications subjects,
                   struct education *educations, int number_of_educations,
                   struct education *currentEducation){
    switch(c){
        case find:
            findCmd(arg);
            break;
        case save:
            saveCmd();
            break;
        case save_prof:
            saveProfCmd();
            break;
        case recommend:
            recommendCmd(educations, user, currentEducation);
            break;
        case list:
            listCmd();
            break;
        case eval:
            evalCmd(arg_num);
            break;
        case test:
            testCmd(user, subjects);
            break;
        case menu:
            menuCmd();
            break;
    }
}

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

/** @fn int scanCommand(char arg[MAX_INPUT_LENGTH], int *arg_num)
 *    @brief Finds valid command and argument
 *    @param arg Output parameter for argument string
 *    @param arg_num Output parameter for argument int
 */
command scanCommand(char arg[MAX_INPUT_LENGTH], int *arg_num){
    char command_string[MAX_COMMAND_LENGTH] = "";
    command command_index; 
    int scan_res;

    scan_res = scanf(" %s", command_string);
    
    command_index = convertCommand(command_string);
    if(scan_res == 0 || command_index == -1){
        return -1;
    }

    switch(argType(command_index)){
        case 1:
            scanf(" %s", arg);
            break;
        case -1:
            scanf(" %d", arg_num);
            break;
    }

    clearBuffer();

    return command_index;
}

/*    Outputs enum value if command, else -1 */
command convertCommand(char s[MAX_COMMAND_LENGTH]){
    command c;

    if(strcmp(s, "find") == 0){
        c = find;
    } else if(strcmp(s, "save") == 0){
        c = save;
    } else if(strcmp(s, "save_prof") == 0){
        c = save_prof;
    } else if(strcmp(s, "recommend") == 0){
        c = recommend;
    } else if(strcmp(s, "list") == 0){
        c = list;
    } else if(strcmp(s, "eval") == 0){
        c = eval;
    } else if(strcmp(s, "test") == 0){
        c = test;
    } else if(strcmp(s, "menu") == 0){
        c = menu;
    } else{
        c = -1;
    }

    return c;
}

/* 1 is string, -1 is int, 0 is no arg */
int argType(command c){
    return (c == find || c == eval) ? ((c == find) ? 1 : -1) : 0;
}

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
void setProfileName(struct profile user, char *name, char **names){
    printf("Profile name (only one word): ");

    getValidName(name, names);
    strcpy(user.name, name);
}

void getValidName(char *name, char **name_array){
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

const char* regionName(enum region region){
    char *regions[NUMBER_OF_REGIONS] = {"NORTH JUTLAND", "CENTRAL JUTLAND", "SOUTHERN DENMARK", 
                                        "ZEALAND", "CAPITAL REGION"};
    return regions[region];
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
    } while(scan_res == 0 && test_char != '\n');

    return valid_int;
}

void setProfileInterests(struct profile user, struct database db){
    int i;

    printf("Next, a series of interests will be shown\n"
            "You are to give a value between 0 and 10, "
            "where 0 is negative and 10 is positive towards the interest\n");

    for(i = 0; i < interests.size; i++){                              // How many interests?
        printf("%s:  ", db.interests_string[i]);                                          // Where are the interests saved? 
        user.interests[i] = convertScale(validScaleValue(getValidInteger(), 0, 10));
    }
}

void setProfileQualifications(struct profile user){
    setSubjects(user);
    
    setImportantSubjects(user); 
    
    setOtherSubjects(user, IMPORTANT_SUBJECTS, IMPORTANT_SUBJECTS + OTHER_SUBJECTS);
    setOtherSubjects(user, IMPORTANT_SUBJECTS + OTHER_SUBJECTS, TOTAL_SUBJECTS);
}

void setSubjects(struct profile user){
    int i;

    for(i = 0; i < TOTAL_SUBJECTS; i++)
        user.qualifications.subjects[i].name = i;
}

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

void setOtherSubjects(struct profile user, int start, int end){
    int i;

    for(i = 0; i < end - start; i++)
        printf("%d: %s\n", i, classNameStr(i + start));
    chooseFromList(user, start, end);
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
        if(result > highest_result){
            highest_result = result;
            best_fit = educations[i];
        }
    }
    
    *currentEducation = best_fit;
    printEducation(*currentEducation);
}

void isQualified(struct profile user, struct education education) {
    int i;
    enum class subject;
    for(i = 0; i < education.required_qualifications.amount_of_subjects; i++) {
        
        if(education.required_qualifications.subjects[i]
    }
}

/* Prints the relavant information about the given education */
void printEducation(struct education education){
    printf("Name of education: %s\n", education.name);
    printf("Description: %s\n", education.description);
    printf("Education is located in: %s\n", );

}

/* Commands:
    find (1 arg, uddannelse)
    save (0 arg)
    save_prof (0 arg)
    recommend (0 arg) 
    list (0 arg)
    eval (1 arg, grade)
    test (0 arg)
    menu (0 arg)

    Low-prio
    load (1 arg)
*/