/** @file subjects.h
 *  @brief Contains code regarding subjects and qualifcations for educations
 * 
 *  Contains the enums for different classes and their levels. Also includes the subject and qualification structs and some related functions
*/  

#ifndef SUBJECTS_H
#define SUBJECTS_H

/**
 * @enum class
 * @brief A subject on different levels
 * 
 * Are used to represent a subject and its level. The enum is flagablle, 
 * which simply means that bitwise operators are applyable.
 */
enum class{
    MATHEMATICS,
    CHEMISTRY,
    BIOLOGY,
    PHYSICS,
    ENGLISH,

    BIOTECHNOLOGY,
    GEOSCIENCE,
    HISTORY,
    IDEA_HISTORY,
    INFORMATICS,
    INTERNATIONAL_ECONOMICS,
    COMMUNICATION_AND_IT,
    RELIGION,
    SOCIALSTUDIES,
    BUSINESS_ECONOMICS,
    CONTEMPORARY_HISTORY,
    
    FRENCH,
    SPANISH,
    GERMAN,
    CHINESE, 
    ARABIC,
    GREEK,
    ITALIAN,
    JAPANESE, 
    LATIN,
    PORTUGESE,
    RUSSIAN,
    NONE,
    DANISH
};

/**
 * @enum level
 * @brief Descripes a level of a subject
 */
enum level{
    Z,
    C,
    B,
    A
};

/**
 * @struct subject
 * @brief Descripes the name of a subject and the level
 * @var name The name of the subject
 * @var level T he level of the subject
 */
struct subject{
    enum class name;    
    enum level level;   
};

/**
 * @struct qualification
 * @brief Contains an array of subjects and the arrays length
 * @var amount_of_subjects The amount of subjects in qualifications
 * @var subjects The array of subjects in qualifications
 */
struct qualification{
    int amount_of_subjects;     
    struct subject *subjects;   
};

struct qualification createQualifications(int number_of_qualifications);
void freeQualifications(struct qualification *qualification);
enum class stringToClass(char *);
enum level charToLevel(char ch);
char levelToChar(enum level l);

#endif
