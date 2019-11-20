#ifndef SUBJECTS_H
#define SUBJECTS_H

/**
 * @brief A subject on different levels
 * 
 * Are used to represent a subject and its level. The enum is flagablle, 
 * which simply means that bitwise operators are applyable.
 */
enum subject {
    MATH_A      = 2,
    MATH_B      = 4,
    DANISH_A    = 8,
    DANISH_B    = 16,
    ENGLISH_A   = 32,
    ENGLISH_B   = 64,
    /** TODO: Add a shit ton more*/

};

#endif