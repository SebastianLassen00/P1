#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "subjects.h"

/** @fn struct profile createProfile(int number_of_interests)
 *  @brief Allocates memory for each of the fields in the profile struct
 *  @param number_of_interests The number of interests allocated
 */
struct qualification createQualifications(int number_of_qualifications){
    struct qualification qualifications;

    qualifications.amount_of_subjects = number_of_qualifications;
    qualifications.subjects = (struct subject*) calloc(number_of_qualifications, sizeof(struct subject));

    return qualifications;
}

/** @fn void freeQualification(struct qualification *qualification)
 *  @brief free a qualification and its members
 *  @param qualification the qualification to be freed
 */
void freeQualifications(struct qualification *qualification){
    free(qualification->subjects);
}

/** @fn enum class stringToClass(char *string)
 *  @brief Returns the enum class associated with the given string
 *  @param string The string which is converted into an enum class
 */
enum class stringToClass(char *string){
    if (strcmp(string, "MATHEMATICS") == 0){
        return MATHEMATICS;
    }else if(strcmp(string, "CHEMISTRY") == 0){
        return CHEMISTRY;
    }else if(strcmp(string, "BIOLOGY") == 0){
        return BIOLOGY;
    }else if(strcmp(string, "PHYSICS") == 0){
        return PHYSICS;
    }else if(strcmp(string, "ENGLISH") == 0){
        return ENGLISH;
    }else if(strcmp(string, "DANISH") == 0){
        return DANISH;
    }else if(strcmp(string, "BIOTECHNOLOGY") == 0){
        return BIOTECHNOLOGY;
    }else if(strcmp(string, "GEOSCIENCE") == 0){
        return GEOSCIENCE;
    }else if(strcmp(string, "HISTORY") == 0){
        return HISTORY;
    }else if(strcmp(string, "IDEAHISTORY") == 0){
        return IDEA_HISTORY;
    }else if(strcmp(string, "INFORMATICS") == 0){
        return INFORMATICS;
    }else if(strcmp(string, "INTERNATIONALECONOMICS") == 0){
        return INTERNATIONAL_ECONOMICS;
    }else if(strcmp(string, "COMMUNICATIONANDIT") == 0){
        return COMMUNICATION_AND_IT;
    }else if(strcmp(string, "RELIGION") == 0){
        return RELIGION;
    }else if(strcmp(string, "SOCIALSTUDIES") == 0){
        return SOCIALSTUDIES;
    }else if(strcmp(string, "BUSINESSECONOMICS") == 0){
        return BUSINESS_ECONOMICS;
    }else if(strcmp(string, "CONTEMPORARYHISTORY") == 0){
        return CONTEMPORARY_HISTORY;
    }else if(strcmp(string, "FRENCH") == 0){
        return FRENCH;
    }else if(strcmp(string, "SPANISH") == 0){
        return SPANISH;
    }else if(strcmp(string, "GERMAN") == 0){
        return GERMAN;
    }else if(strcmp(string, "CHINESE") == 0){
        return CHINESE;
    }else if(strcmp(string, "ARABIC") == 0){
        return ARABIC;
    }else if(strcmp(string, "GREEK") == 0){
        return GREEK;
    }else if(strcmp(string, "ITALIAN") == 0){
        return ITALIAN;
    }else if(strcmp(string, "JAPANESE") == 0){
        return JAPANESE;
    }else if(strcmp(string, "LATIN") == 0){
        return LATIN;
    }else if(strcmp(string, "PORTUGESE") == 0){
        return PORTUGESE;
    }else if(strcmp(string, "RUSSIAN") == 0){
        return RUSSIAN;
    }
    
    /*default*/
    return NONE;
}

/** @fn enum level charToLevel(char ch)
 *  @brief Returns the enum level associated with the given char
 *  @param ch The character which is converted into an enum level
 */
enum level charToLevel(char ch){
    enum level level = Z;

    if(ch == 'A') 
        level = A;
    else if(ch == 'B') 
        level = B;
    else if(ch == 'C') 
        level = C;
    
    return level;
}

/** @fn enum char levelToChar(enum level l)
 *  @brief Returns the character associated with the given enum level
 *  @param l The enum level which is converted into a character
 */
char levelToChar(enum level l){
    switch(l){
        case 1:
            return 'C';
        case 2:
            return 'B';
        case 3:
            return 'A';
        default:
            return 'Z';
    }
}