#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "region.h"
#include "subjects.h"
#include "education.h"
#include "vector.h"
#include "profile.h"



struct vector interests;
struct qualification required_qualifications;


struct education createDefaultEducation(int amount_of_interests, int amount_of_subjects){
    struct education education;
    char *temp_name = "Nothing";
    char *temp_desc = "No education selected";
    char *temp_link = "No education link";

    education.name = (char *) calloc(strlen(temp_name) + 1, sizeof(char));
    education.description = (char *) calloc(strlen(temp_desc) + 1, sizeof(char));
    education.link = (char *) calloc(strlen(temp_link) + 1, sizeof(char));
    education.region = NORTH_JUTLAND;
    education.required_grade = 0.0;
    education.interests = createVector(amount_of_interests);
    education.required_qualifications = createQualifications(amount_of_subjects);

    strcpy(education.name, temp_name);
    strcpy(education.description, temp_desc);
    strcpy(education.link, temp_link);
}

/**
 * @brief 
 * 
 * @param education 
 */
void freeEducation(struct education *education){
    free(education->name);
    free(education->description);
    free(education->link);
    freeVectorM(1, education->interests);
    
    freeQualification(&education->required_qualifications);
}
