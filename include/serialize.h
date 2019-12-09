/** @file serialize.h
 *  @author 
 *  @brief Save and load profile data
 *  @version 0.1
 *  @date 2019-11-27
 * 
 *  @copyright Copyright (c) 2019
 */

#ifndef SERIALIZE_H
#define SERIALIZE_H

#include "profile.h"

#define SAVE_FILE "data/save.data"

int saveProfile(struct profile *);

struct profile *loadProfile();

#endif