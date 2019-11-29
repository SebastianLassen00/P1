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
    char *link_to_read_further; /**A link to the educations website*/
    enum region region;         /**The region where the education is found*/
    double required_grade;      /**The minimum grade required for entry*/
    struct vector interest;    /**The amount each interest is associated with this education*/
    struct qualification required_qualifications;   /**The required qualifications for this education*/
};

/**
 * @struct education
 * @brief A structure, which contains amount_of_educations educations
 */
struct educationArray{
    int amount_of_educations;       /**The amount of educations in educations*/
    struct education **educations; /**An array of pointers to educations*/
};

struct education *createEducationBasics(char *, char*, char*, enum region);
void freeEducation(struct education *);
void freeEducationArray(struct educationArray *);

#endif