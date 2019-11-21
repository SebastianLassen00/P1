#ifndef EDUCATION_H
#define EDUCATION_H

#include"region.h"

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
    double *interests;          /**The interests associated with the education*/ 

};

#endif