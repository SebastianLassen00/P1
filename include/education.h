/** @file education.h
 *  @brief The file containing the education structs
*/  

#ifndef EDUCATION_H
#define EDUCATION_H

#include"region.h"
#include"subjects.h"
#include "vector.h"

/**
 * @struct education
 * @brief Describes an education and all it requirements.
 * 
 * This structure defines an education and all the details about the education.
 */
struct education {
    char *name;                 /**The name of an education*/
    char *description;          /**The description of an education*/
    char *link; /**A link to the educations website*/
    enum region region;         /**The region where the education is found*/
    double required_grade;      /**The minimum grade required for entry*/
    struct vector interests;    /**The amount each interest is associated with this education*/
    struct qualification required_qualifications;   /**The required qualifications for this education*/
};

/**
 * @struct education
 * @brief A structure, which contains amount_of_educations educations
 */

struct education createDefaultEducation(int amount_of_interests, int amount_of_subjects);
void freeEducation(struct education *);


#endif