#include <stdlib.h>
#include <stdio.h>
#include "education.h"
#include "vector.h"


struct education *createEducationBasics(char* name, char*description, char* link, enum region region){
    struct education *education = malloc(sizeof(struct education));

    if (education == NULL)
    {
        printf("Malloc failed and the program aborted");
        exit(EXIT_FAILURE);
    }
    
    education->name = name;
    education->description = description;
    education->link_to_read_further = link;
    education->region = region;

    return education;    
}


/**
 * @brief 
 * 
 * @param education 
 */
void freeEducation(struct education *education){
    free(education->name);
    free(education->description);
    free(education->link_to_read_further);
    freeVector(education->interests);
    freeQualification(&education->required_qualifications);
}
