#include <stdlib.h>
#include "education.h"

void freeEducation(struct education *education){
    free(education->name);
    free(education->description);
    free(education->link_to_read_further);
    free(education->interests);
    free(education);
}


void freeEducationArray(struct educationArray *educationArray){
    free(educationArray->educations);
    free(educationArray);
}