#ifndef SUBJECTS_H
#define SUBJECTS_H


#define FIRST_SUBJECT_IN_ENUM MATHEMATICS
#define LAST_SUBJECT_IN_ENUM RUSSIAN

#define FIRST_NATURAL_SCIENCE MATHEMATICS
#define LAST_NATURAL_SCIENCE GEOSCIENCE

#define FIRST_SOCIAL_SCIENCE DANISH
#define LAST_SOCIAL_SCIENCE CONTEMPORAY_HISTORY

#define FIRST_FOREIGN_LANGAUGE ENGLISH
#define LAST_FOREIGN_LANGAUGE RUSSIAN





/**
 * @enum
 * @brief A subject on different levels
 * 
 * Are used to represent a subject and its level. The enum is flagablle, 
 * which simply means that bitwise operators are applyable.
 */
enum class {
    MATHEMATICS,
    CHEMISTRY,
    BIOLOGY,
    PHYSICS,
    BIOTEKNOLOGY,
    GEOSCIENCE,
    DANISH,
    HISTORY,
    IDEAHISTORY,
    INFORMATICS,
    INTERNATIONAÆ_ECONOMICS,
    COMMUNICATION_AND_IT,
    RELIGION,
    SOCIALSTUDIES,
    BUSINESS_ECONOMICS,
    CONTEMPORAY_HISTORY,
    ENGLISH,
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
    RUSSIAN

    /** TODO: Add a shit ton more*/
};

/**
 * @enum
 * @brief Descripes a level of a subject
 */
enum level {
    C,
    B,
    A,
};

/**
 * @struct
 * @brief Descripes the name of a subject and the level
 */
struct subject {
    enum class name;    /**the name of the subject*/
    enum level level;   /**the level of the subject*/
};

/**
 * @struct
 * @brief Contains an array of subjects and the arrays length
 */
struct qualification {
    int amount_of_subjects;     /**the amount of subjects in qualifications*/
    struct subject *subjects;   /**the array of subjects in qualifications*/
};

void freeSubject(struct subject *);
void freeQualification(struct subject *);

#endif
