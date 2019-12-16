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
 * @var education::name 
 * The name of an education
 * @var education::description 
 * The description of an education
 * @var education::link 
 * A link to the educations website
 * @var education::region 
 * The region where the education is found
 * @var education::required_grade 
 * The minimum grade required for entry
 * @var education::interests 
 * The amount each interest is associated with this education
 * @var education::required_qualifications 
 * The required qualifications for this education
 */
struct education{
    char *name;                 
    char *description;          
    char *link; 
    enum region region;         
    double required_grade;      
    struct vector interests;    
    struct qualification required_qualifications;   
};

struct education createDefaultEducation(int amount_of_interests, int amount_of_subjects);
struct education* createArrayOfEducations(int amount_of_educations);
void freeEducation(struct education *);


#endif