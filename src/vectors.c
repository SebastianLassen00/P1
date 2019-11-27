#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "vector.h"

/** @fn struct vector createVector(int size)
 *  @brief creates a vector on the heap and outputs it. 
 *  @param size The number of elements in the vector.
 */
struct vector createVector(int size){
    struct vector vector;
    vector.array = (double*)calloc(size, sizeof(double));

    if(vector.array == NULL){
        printf("Failed to allocate memory. Bye bye.\n");
        exit(EXIT_FAILURE);
    }
    vector.size = size;
    
    return vector;
}

/** @fn void freeVector(struct vector v)
 *  @brief frees the dynamically allocated array on the heap.
 *  @param v The vector struct containing the array on the heap.
 */
void freeVector(struct vector v){
    free(v.array);
}

/** @fn struct vector copyVector(struct vector v1, struct vector v2)
 *  @brief Copies the the inputted vector into vector copy and returns this.
 *  @param v1 The input vector that is copied
 */
struct vector copyVector(struct vector v){
    struct vector copy = createVector(v.size);
    int i;

    for(i = 0; i < v.size; i++)
        copy.array[i] = v.array[i];
    
    return copy;
}


/** @fn void printVector(struct vector v)
 *  @brief Prints a vector
 *  @param v The vector that is printed
 */
void printVector(struct vector v){
    int i;

    for(i = 0; i < v.size; i++)
        printf("%f\n", v.array[i]);
}

/** @fn struct vector addVector(struct vector v1, struct vector v2)
 *  @brief Adds two vectors together and outputs the sum as a vector
 *  @param v1 The first vector struct: v1.array[] is a vector, v1.size number of elements in the vector
 *  @param v2 The second vector struct: v2.array[] is a vector
 */
struct vector addVector(struct vector v1, struct vector v2){
    struct vector sum = createVector(v1.size); 
    int i;

    for(i = 0; i < v1.size; i++)
        sum.array[i] = v1.array[i] + v2.array[i];

    return sum;
}

/** @fn struct vector subtractVector(struct vector v1, struct vector v2)
 *  @brief Subtracts the second vector from the first vector and returns the result as a vector
 *  @param v1 The vector that should be subtracted from
 *  @param v2 The vector that is used for subtraction
 */
struct vector subtractVector(struct vector v1, struct vector v2){
    struct vector sum = createVector(v1.size);
    int i;

    for(i = 0; i < v1.size; i++)
        sum.array[i] = v1.array[i] - v2.array[i];
    
    return sum;
}

/** @fn struct vector scaleVector(struct vector v, double scale)
 *  @brief Multiplies the given vector's array values by the value inputted as scale, then outputs the result as a vector
 *  @param v The vector that should be up- or downscaled
 *  @param scale The value that the vector should be scaled by
 */
struct vector scaleVector(struct vector v, double scale){
    struct vector result = createVector(v.size);
    int i;

    for(i = 0; i < v.size; i++)
        result.array[i] = v.array[i] * scale;

    return result;
}

/** @fn double lengthOfVector(struct vector v)
 *  @brief Calculates and returns the length of the given vector
 *  @param v The vector whose length is found
 */
double lengthOfVector(struct vector v){
    double sum = 0.0;
    int i; 

    for(i = 0; i < v.size; i++)
        sum += pow(v.array[i], 2);

    return sqrt(sum);
}

/** @fn struct vector normalizeVector(struct vector v)
 *  @brief Normalises a vector via scaling it by one over it's length, then returns the normalized vector
 *  @param v The vector which is to be normalized 
 */
struct vector normalizeVector(struct vector v){
    return scaleVector(v, 1 / lengthOfVector(v));
}

/** @fn double dotProduct(struct vector v1, struct vector v2)
 *  @brief Calculates and returns the dot product of two vectors
 *  @param v1 The first vector to be used for dot product calculation
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