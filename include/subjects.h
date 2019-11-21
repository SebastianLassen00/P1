#ifndef SUBJECTS_H
#define SUBJECTS_H

/**
 * @brief A subject on different levels
 * 
 * Are used to represent a subject and its level. The enum is flagablle, 
 * which simply means that bitwise operators are applyable.
 */
enum subject {
    MATH_A      = 1 << 0,
    MATH_B      = 1 << 1,
    DANISH_A    = 1 << 2,
    DANISH_B    = 1 << 3,
    ENGLISH_A   = 1 << 4,
    ENGLISH_B   = 1 << 5,
    /** TODO: Add a shit ton more*/

};

#endif