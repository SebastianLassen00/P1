/** @file subjects.h
 *  @brief Contains code regarding subjects and qualifcations for educations
 * 
 *  <Detailed esription here>
*/  

#ifndef SUBJECTS_H
#define SUBJECTS_H

/**
 * @enum
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
 * @enum
 * @brief Descripes a level of a subject
 */
enum level{
    Z,
    C,
    B,
    A
};

/**
 * @struct
 * @brief Descripes the name of a subject and the level
 */
struct subject{
    enum class name;    /**the name of the subject*/
    enum level level;   /**the level of the subject*/
};

/**
 * @struct
 * @brief Contains an array of subjects and the arrays length
 */
struct qualification{
    int amount_of_subjects;     /**the amount of subjects in qualifications*/
    struct subject *subjects;   /**the array of subjects in qualifications*/
};

struct qualification createQualifications(int number_of_ualifications);
void freeQualifications(struct qualification *);
enum class stringToClass(char *);
enum level charToLevel(char ch);
char levelToChar(enum level l);

#endif
