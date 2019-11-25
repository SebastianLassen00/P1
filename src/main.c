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

int argType(command c);
void menuCmd(void);
command scanCommand(char arg[MAX_INPUT_LENGTH], int *arg_num);
command convertCommand(char s[MAX_COMMAND_LENGTH]);
void recommendCmd(struct educations *educations, struct profile user, 
                  struct education *currentEducation);

int main(void){
    char arg[MAX_INPUT_LENGTH], arg_type[MAX_INPUT_LENGTH];
    int arg_num = 0, number_of_educations;
    command c;
    struct education *educations, currentEducation;
    struct profile user;
    struct qualifications subjects;

    menuCmd();

    do{
        c = scanCommand(arg, &arg_num);
        handleCommand(c, arg, arg_num, user, subjects, educations, 
                      number_of_educations, &currentEducation);
    } while(c != exit);


    return 0;
}

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
           "  exit       -  exits the program                                                        \n");
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

    if()
    sscanf(str, "[^0123456789]")

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
	profile.location.region = validScaleValue(getValidInteger());

	printf("How important is this region to you\n");
	profile.location.region_importance = validScaleValue(getValidInteger());

	/*  Get all interests  */
	printf("Next, a series of interests will be shown\n"
		   "You are to give a value between 0 and 10, "
		   "where 0 is negative and 10 is positive towards the interest\n");

	for(i = 0; i < ; i++){								// How many interests?
		printf("%s:  ", );								// Where are the interests saved? 
		initial_value = validScaleValue(getValidInteger());
		if(initial_value != 0){
			user.interests.array[i] = convertScale(initial_value);
		} else{
			printf("Wrong input, try again\n");
			clearBuffer();
			i--;
		}
	}

	/*  Get important qualifications  */


	/*  Get less important qualifications  */


	/*  Get average grade  */
	printf("What is your average grade? ");
	user.average = getValidDouble();

	/*  Ending the test  */
	printf("The test is now concluded. Returning to menu...\n\n");
}

void chooseFromList(){

}

double convertScale(int initial_value){
	return (((double) v - 5.0) / 5.0);
}

int validScaleValue(int value){
	return (value > 10 ? 10 : (value < 0 ? 0 : value));
}

int getValidInteger(void){
	int valid_int = 0, scan_res = 0;
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

/* Recommends an education to the user. */
void recommendCmd(struct educations *educations, int number_of_educations, struct profile user, 
                  struct education *currentEducation){
    int i;
    struct vector results, normalized_vector;
    double highest_result, result;
    struct education best_fit;
    normalized_vector = createVector(profile.interest.dimensions);
    
    for(i = 0; i < number_of_educations; i++){
        normalizeVector(educations[i].interests, normalized_vector);
        result = dotProduct(interests, normalized_vector);
        if(result > highest_result){
            highest_result = result;
            best_fit = educations[i];
        }
    }
    
    *currentEducation = best_fit;
    printEducation(*currentEducation);
}

/* Prints the relavant information about the given education */
void printEducation(struct education education){

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