#include <stdio.h>

#define MAX_COMMAND_LENGTH 10
#define MAX_INPUT_LENGTH (MAX_COMMAND_LENGTH + 100)

enum command{find, save, save_prof, recommend, list, eval, test};

int main(void){
  printf("Hello World!");
  return 0;
}

void menu(void){

	printf("This is a menu for the program.\nTo use command simple write the command written as shown in command: help");
	scanCommand();


}

int scanCommand(char arg[MAX_INPUT_LENGTH], int *arg_num){
	char input[MAX_INPUT_LENGTH] = "", command_string[MAX_COMMAND_LENGTH] = "", arg_string[MAX_INPUT_LENGTH] = "";
	int command_index, scan_res;

	scan_res = scanf(" %s", input);
	sscanf(input, "%[^ ] %s", command_string, arg_string);

	command_index = convertCommand(command_string);
	if(scan_res == 0 || command_index == -1){
		return -1;
	}

	switch(argType(command)){
		case 1:
			strcpy(arg_string, arg) 
	}

	return command_index;
}

/*  Outputs enum value if command, else -1 */
int convertCommand(char s[MAX_COMMAND_LENGTH]){
	int command;

	if(strcmp(s, "find") == 0){
		command = find;
	} else if(strcmp(s, "save") == 0){
		command = save;
	} else if(strcmp(s, "save_prof") == 0){
		command = save_prof;
	} else if(strcmp(s, "recommend") == 0){
		command = recommend;
	} else if(strcmp(s, "list") == 0){
		command = list;
	} else if(strcmp(s, "eval") == 0){
		command = eval;
	} else if(strcmp(s, "test") == 0){
		command = test;
	} else if(strcmp(s, "help") == 0){
		command = help;
	} else{
		command = -1;
	}

	return command;
}

/* 1 is string, -1 is int, 0 is no arg */
int argType(command c){
	return (c == find || c == eval) ? ((c == find) ? 1 : -1) : 0;
}




/* Commands:
		find (1 arg, uddannelse)
		save (0 arg)
		save_prof (0 arg)
		recommend (0 arg) 
		list (0 arg)
		eval (1 arg, grade)
		test (0 arg)
		help (0 arg)

		Low-prio
		load (1 arg)