#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "vector.h"

struct vector createVector(int size){
    struct vector vector;
    vector.array = (double*)calloc(size, sizeof(double));
    /*vector.array = (double*)malloc(size * sizeof(double)); */
    if(vector.array == NULL){
        printf("Failed to allocate memory. Bye bye.\n");
        exit(EXIT_FAILURE);
    }
    vector.size = size;
    
    return vector;
}


void freeVector(struct vector v){
    free(v.array);
}

/** @fn void copyVector(const double in[], int size, double out[])
 *  @brief Copies a v1 to v2
 *  @param v The input vector that is copied
 *  @param size The size of the vectors
 *  @param out The output vector that is copied into
 */
struct vector copyVector(struct vector v1, struct vector v2){
    v2 = v1;
    return v2;
}


/** @fn void printVector(const double v[], int size)
 *  @brief Prints a vector
 *  @param v The vector that is printed
 *  @param size The size of the vector
 */
void printVector(struct vector v){
    int i;

    for(i = 0; i < v.size; i++)
        printf("%f\n", v.array[i]);
}

/** @fn struct vector addVector(struct vector v1, struct vector v2)
 *  @brief Adds two vectors together and outputs the sum as a vector
 *  @param v1 The first vector struct: v1.array[] is a vector, v1.size number of elements in the vector.
 *  @param v2 The second vector struct: v2.array[] is a vector.
 *  @param sum The sum is a vector struct which is returned.
 */
struct vector addVector(struct vector v1, struct vector v2){
    struct vector sum = createVector(v1.size); 
    int i;

    for(i = 0; i < v1.size; i++)
        sum.array[i] = v1.array[i] + v2.array[i];

    /*sum.size = v1.size;*/ 

    return sum;
}

/** @fn void addVector(const double v1[], const double v2[], int size, double sum[])
 *  @brief Adds two vectors together and outputs the sum as a vector
 *  @param v1 The vector that should be subtracted from
 *  @param v2 The vector that is used for subtraction
 *  @param size The size of the vectors
 *  @param sum The sum of the subtracted vectors that is output
 */
struct vector subtractVector(struct vector v1, struct vector v2){
    struct vector sum = createVector(v1.size);
    int i;

    for(i = 0; i < v1.size; i++)
        sum.array[i] = v1.array[i] - v2.array[i];
    
    return sum;
}

/** @fn void scaleVector(const double v[], double scale, double size, double out[])
 *  @brief Adds two vectors together and outputs the sum as a vector
 *  @param v The vector that should be up- or downscaled
 *  @param scale The value that the vector should be scaled by
 *  @param size The size of the vectors
 *  @param out The up- or downscaled vector that is output
 */
struct vector scaleVector(struct vector v, double scale){
    struct vector result = createVector(v.size);
    int i;

    for(i = 0; i < v.size; i++)
        result.array[i] = v.array[i] * scale;

    return result;
}

/** @fn double lengthOfVector(const double v[], int size)
 *  @brief Returns the length of a vector
 *  @param v The vector which length is found
 *  @param size The size of the vector
 */
double lengthOfVector(struct vector v){
    double sum = 0.0;
    int i; 

    for(i = 0; i < v.size; i++)
        sum += pow(v.array[i], 2);

    return sqrt(sum);
}

/** @fn void normalizeVector(const double v[], int size, double out[])
 *  @brief Returns the normalized vector
 *  @param v The vector which is to be normalized
 *  @param size The size of the vector
 *  @param out The normalized vector that is output 
 */
struct vector normalizeVector(struct vector v){
    return scaleVector(v, 1 / lengthOfVector(v));
}

/** @fn double dotProduct(const double v1[], int size, const double v2[])
 *  @brief Calculates and returns the dot product of two vectors of any, though equal, size
 *  @param v1 The first vector to be used for dot product calculation
 *  @param size The size of the vectors
 *  @param v2 The second vector to be used for dot product calculation
 */
double dotProduct(struct vector v1, struct vector v2){
    double dot_product = 0;
    int i;

    for(i = 0; i < v1.size; i++){
        dot_product += v1.array[i] * v2.array[i];
    }

    return dot_product;
}