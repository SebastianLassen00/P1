#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "region.h"
#include "subjects.h"
#include "education.h"
#include "vector.h"
#include "profile.h"

/** @fn struct education createDefaultEducation(int amount_of_interests, int amount_of_subjects)
 *  @brief Assigns default values to the fields of the education struct
 *  @param amount_of_interests The number of interests the education should hold
 *  @param amount_of_subjects The number of subjects the education should hold
 */
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

    return education;
}

/** @fn void freeEducation(strict edication *education)
 *  @brief Frees the memory allocated to the fields of the education struct
 *  @param education The education struct which is freed
 */
void freeEducation(struct education *education){
    free(education->name);
    free(education->description);
    free(education->link);
    freeVectorM(1, education->interests);
    
    freeQualifications(&(education->required_qualifications));
}

/** @fn struct education* createArrayOfEducations(int amount_of_educations)
 *  @brief Allocate memory for an array of educations and return a pointer to it
 *  @param amount_of_educations The amount of educations to be stored in the array
 */
struct education* createArrayOfEducations(int amount_of_educations){
    struct education* educations;
    educations = (struct education*) calloc(amount_of_educations, sizeof(struct education));

    if(educations == NULL){
        printf("Failed to allocate memory for educations.\n");
        exit(EXIT_FAILURE);
    }
    
    return educations;
}
