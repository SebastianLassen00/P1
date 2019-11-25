#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "profile.h"
#include "education.h"
#include "subjects.h"
#include "vector.h" 

#define MAX_COMMAND_LENGTH 10
#define MAX_INPUT_LENGTH (MAX_COMMAND_LENGTH + 100)

enum command{find, save, save_prof, recommend, list, eval, test, menu, exit};
typedef enum command command;


struct profile createProfile(int number_of_interests);
struct qualifications createQualifications(int number_of_qualifications);
void freeQualifications(struct qualification q);
void freeProfile(struct profile p);

int main(void){
    struct profile user;

    user = createProfile(5);

    user.name = "christian";

    printf("%s\n", user.name);


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


