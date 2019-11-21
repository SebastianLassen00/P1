#include <stdio.h>
#include "vectors.h"

int main(void){
    double vector[3] = {1, 0.5, 0.1};
    double vectorTest[3] = {0.2, 0.3, 0.0};
<<<<<<< HEAD
    double vector_dot_test[3] = {0.0 , 0.0, 1.1};
=======
    double sum[3] = {0, 0, 0};
>>>>>>> d7008e385d8f3235cb11958906f296f142505e9e
    
    copyVector(vector, 3, vectorTest);
    printVector(vectorTest, 3);

    addVector(vector, vectorTest, 3, sum);
    printVector(sum, 3);

    scaleVector(vector, 2, 3, vectorTest);
    printVector(vectorTest, 3);
    

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