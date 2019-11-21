#include <stdio.h>
#include "vectors.h"

int main(void){
    double vector[3] = {1, 0.5, 0.1};
    double vectorTest[3] = {0.2, 0.3, 0.0};
    
    copyVector(vector, 3, vectorTest);
    printVector(vectorTest, 3);

    return 0;
}

/** @fn void copyVector(const double in[], int size, double out[])
 *  @brief Copies a vector into another vector
 *  @param in The input vector that is copied
 *  @param size The size of the vectors
 *  @param out The output vector that is copied into
 */
void copyVector(const double in[], int size, double out[]){
    int i;

    for(i = 0; i < size; i++)
        out[i] = in[i];
}

/** @fn printVector(const double v[], int size)
 *  @brief Prints a vector
 *  @param v The vector that is printed
 *  @param size The size of the vector
 */
void printVector(const double v[], int size){
    int i;

    for(i = 0; i < size; i++)
        printf("%f\n", v[i]);
}