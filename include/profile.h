#ifndef PROFILE_H
#define PROFILE_H

#define MAX_NAME_LENGTH 20

struct profile{
	struct vector interests;
	char * name;
	struct qualifications qualifications;
	double average;
	struct location location;

};



#endif