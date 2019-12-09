/** @file education.h
 *  @brief Contains elements relating to educations
 * 
 *  This file contains the education struct and the function that creates educations.
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
 * @var name The name of an education
 * @var description The description of an education
 * @var link A link to the educations website
 * @var region The region where the education is found
 * @var required_grade The minimum grade required for entry
 * @var interests The amount each interest is associated with this education
 * @var required_qualifications The required qualifications for this education
 */
struct education {
    char *name;                 
    char *description;          
    char *link; 
    enum region region;         
    double required_grade;      
    struct vector interests;    
    struct qualification required_qualifications;   
};

/**
 * @struct education
 * @brief A structure, which contains amount_of_educations educations
 */
struct education createDefaultEducation(int amount_of_interests, int amount_of_subjects);
void freeEducation(struct education *);


#endif