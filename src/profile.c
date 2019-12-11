#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "profile.h"
#include "education.h"
#include "subjects.h"
#include "vector.h" 
#include "commands.h"

/** @fn struct profile createProfile(int number_of_interests)
 *  @brief Allocates memory for each of the fields in the profile struct
 *  @param number_of_interests The number of interests allocated
 */
struct profile createProfile(int number_of_interests){
    struct profile profile;
    int i;

    profile.interests = createVector(number_of_interests);
    profile.adjustment_vector = createVector(number_of_interests);
    profile.qualifications = createQualifications(TOTAL_SUBJECTS);
    profile.average = 0.0;
    profile.location.region = 0;
    profile.location.region_importance = 0;
    profile.last_recommended = 0;

    profile.adjustment_vector.array[0] = 0.0001;

    for(i = 0; i < EDUCATION_LIST_LENGTH; i++){
        strcpy(profile.saved_educations[i], "");
        strcpy(profile.recommended_educations[i], "");
    }

    for(i = 0; i < profile.qualifications.amount_of_subjects; i++)
        profile.qualifications.subjects[i].name = i;

    return profile;
}

/** @fn void freeProfile(struct profile p)
 *  @brief Frees the allocated memory for the given profile
 *  @param p The profile struct which is freed
 */
void freeProfile(struct profile p){
    freeQualifications(&p.qualifications);
    freeVector(p.interests);
    freeVector(p.adjustment_vector);
}

/** @fn void printProfile(struct profile p)
 *  @brief Prints information stored in the given profil
 *  @param p The profile struct which is printed
 */
void printProfile(struct profile p){
    int i;

    printf("Name: %s\n", p.name);
    printVector(p.interests);

    for(i = 0; i < p.qualifications.amount_of_subjects; i++){
        printf("%s %d\n", classNameStr(p.qualifications.subjects[i].name),
                          p.qualifications.subjects[i].level);
    }
    printf("Everything is fine\n");

}
