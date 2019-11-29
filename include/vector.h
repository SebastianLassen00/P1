#ifndef VECTOR_H
#define VECTOR_H

struct vector{
    double *array;
    int size;
};


struct vector createVector(int size);
struct vector copyVector(struct vector v1, struct vector v2);
struct vector addVector(struct vector v1, struct vector v2);
struct vector subtractVector(struct vector v1, struct vector v2);
struct vector scaleVector(struct vector v, double scale);
double lengthOfVector(struct vector v);
struct vector normalizeVector(struct vector v);
double dotProduct(struct vector v1, struct vector v2);

void freeVector(struct vector v);

/* Test */

void printVector(struct vector v);
void freeVectorM(struct vector num, ...);

#endif