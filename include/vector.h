/** @file vector.h
 *  @brief Contains elements relating to vectors
 * 
 *  This file contains the vector struct and various functions used to create, manipulate or free vectors.
*/  

#ifndef VECTOR_H
#define VECTOR_H

/** @brief This is a vector
 *  @var array The vector itself
 *  @var size The number of coordinates in the vector.
 */
struct vector{
    double *array;
    int size;
};

struct vector createVector(int size);
struct vector copyVector(struct vector v);
struct vector addVector(struct vector v1, struct vector v2);
struct vector subtractVector(struct vector v1, struct vector v2);
struct vector scaleVector(struct vector v, double scale);
struct vector normalizeVector(struct vector v);

double lengthOfVector(struct vector v);
double dotProduct(struct vector v1, struct vector v2);

void printVector(struct vector v);
void freeVector(struct vector v);
void freeVectorM(int num, ...);

#endif