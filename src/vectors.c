#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "vectors.h"

int main(void){
    double vector[3] = {1, 0.5, 0.1};
    double vector_test[3] = {0.2, 0.3, 0.0};
    double vector_dot_test[3] = {0.0 , 0.0, 1.1};
    double sum[3] = {0, 0, 0};

    double vector3[3] = {0.1, 0.3, -0.3};
    double length_of_vector3, length;
    double output_vector[3];

    /*
    copyVector(vector, 3, vector_test);
    printVector(vector_test, 3);

    addVector(vector, vector_test, 3, sum);
    printVector(sum, 3);

    scaleVector(vector, 2, 3, vector_test);
    printVector(vector_test, 3);
    
    length_of_vector3 = lengthOfVector(vector3, 3);
    printf("Length of vector3: %f\n", length_of_vector3);

    normalizeVector(vector3, 3, output_vector);
    printVector(output_vector, 3);

    length = lengthOfVector(output_vector, 3);
    printf("Length of output_vector: %f\n", length);    
    */

    printf("%f", dotProduct(vector_test, 3, vector_dot_test));


    return 0;
}

struct vector createVector(int size){
    struct vector vector;
    vector.array = (double*)malloc(size * sizeof(double));
    if(vector.array == NULL){
        printf("Failed to allocate memory. Bye bye.\n");
        exit(EXIT_FAILURE);
    }
    vector.size = size;

    fill_array_with_zeros(vector->array, vector->size);

    return vector;
}

void fill_array_with_zeros(double array[], int size){
    int i;
    for(i = 0; i < size; i++)
        array[i] = 0.0;
}


void clear_heap(double *array){
    free(array);
}

/** @fn void copyVector(const double in[], int size, double out[])
 *  @brief Copies a vector into another vector
 *  @param v The input vector that is copied
 *  @param size The size of the vectors
 *  @param out The output vector that is copied into
 */
void copyVector(const double* v, double* out){
    int i;

    for(i = 0; i < v.size; i++)
        out.array[i] = v.array[i];
}


/** @fn void printVector(const double v[], int size)
 *  @brief Prints a vector
 *  @param v The vector that is printed
 *  @param size The size of the vector
 */
void printVector(const double v[], int size){
    int i;

    for(i = 0; i < size; i++)
        printf("%f\n", v[i]);
}

/** @fn void addVector(const double v1[], const double v2[], int size, double sum[])
 *  @brief Adds two vectors together and outputs the sum as a vector
 *  @param v1 The first vector that should be added
 *  @param v2 The second vector that should be added
 *  @param size The size of the vectors
 *  @param sum The sum of the added vectors that is output
 */
void addVector(const double v1[], const double v2[], int size, double sum[]){
    int i;

    for(i = 0; i < size; i++)
        sum[i] = v1[i] + v2[i];
}

/** @fn void addVector(const double v1[], const double v2[], int size, double sum[])
 *  @brief Adds two vectors together and outputs the sum as a vector
 *  @param v1 The vector that should be subtracted from
 *  @param v2 The vector that is used for subtraction
 *  @param size The size of the vectors
 *  @param sum The sum of the subtracted vectors that is output
 */
void subtractVector(const  double v1[], const double v2[], int size, double sum[]){
    int i;

    for(i = 0; i < size; i++)
        sum[i] = v1[i] - v2[i];
}

/** @fn void scaleVector(const double v[], double scale, double size, double out[])
 *  @brief Adds two vectors together and outputs the sum as a vector
 *  @param v The vector that should be up- or downscaled
 *  @param scale The value that the vector should be scaled by
 *  @param size The size of the vectors
 *  @param out The up- or downscaled vector that is output
 */
void scaleVector(const double v[], double scale, int size, double out[]){
    int i;

    for(i = 0; i < size; i++)
        out[i] = v[i] * scale;
}

/** @fn double lengthOfVector(const double v[], int size)
 *  @brief Returns the length of a vector
 *  @param v The vector which length is found
 *  @param size The size of the vector
 */
double lengthOfVector(const double v[], int size){
    int i; 
    double sum = 0.0;

    for(i = 0; i < size; i++)
        sum += pow(v[i], 2);

    return sqrt(sum);
}

/** @fn void normalizeVector(const double v[], int size, double out[])
 *  @brief Returns the normalized vector
 *  @param v The vector which is to be normalized
 *  @param size The size of the vector
 *  @param out The normalized vector that is output 
 */
void normalizeVector(const double v[], int size, double out[]){
    scaleVector(v, 1 / lengthOfVector(v, size), size, out);
}

/** @fn double dotProduct(const double v1[], int size, const double v2[])
 *  @brief Calculates and returns the dot product of two vectors of any, though equal, size
 *  @param v1 The first vector to be used for dot product calculation
 *  @param size The size of the vectors
 *  @param v2 The second vector to be used for dot product calculation
 */
double dotProduct(const double v1[], int size, const double v2[]){
    int i;
    double dot_product = 0;

    for(i = 0; i < size; i++){
        dot_product += v1[i] * v2[i];
    }

    return dot_product;
}