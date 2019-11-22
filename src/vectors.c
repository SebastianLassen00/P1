#include <stdio.h>
#include <math.h>
#include "vectors.h"

int main(void){
    double vector[3] = {1, 0.5, 0.1};
    double vector_test[3] = {0.2, 0.3, 0.0};
    double vector_dot_test[3] = {0.0 , 0.0, 1.1};
    double sum[3] = {0, 0, 0};

    double vector3[3] = {0.1, 0.3, -0.3};
    double length_of_vector3, length;
    double output_vector[3];

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

    return 0;
}

/** @fn void copyVector(const double in[], int size, double out[])
 *  @brief Copies a vector into another vector
 *  @param v The input vector that is copied
 *  @param size The size of the vectors
 *  @param out The output vector that is copied into
 */
void copyVector(const double v[], int size, double out[]){
    int i;

    for(i = 0; i < size; i++)
        out[i] = v[i];
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
 *  @brief Returns length of vector
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
    scaleVector(v, 1/lengthOfVector(v, size), size, out);
}
