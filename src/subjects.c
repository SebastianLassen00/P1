#include "subjects.h"

/**
 * @brief free a subject and its members
 * 
 * @param subject the subject to be freed
 */
void freeSubject(struct subject *subject){
    free(subject);
}

/**
 * @brief free a qualification and its members
 * 
 * @param qualification the qualification to be freed
 */
void freeQualification(struct qualification *qualification){
    free(qualification->subjects);
    free(qualification);
}