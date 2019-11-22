#ifndef VECTORS_H
#define VECTORS_H

struct vector{
    double *array;
    int number_of_interests;
};


void copyVector(const double v[], int size, double out[]);
void addVector(const double v1[], const double v2[], int size, double sum[]);
void subtractVector(const  double v1[], const double v2[], int size, double sum[]);
void scaleVector(const double v[], double scale, int size, double out[]);
double lengthOfVector(const double v[], int size);
void normalizeVector(const double v[], int size, double out[]);
double dotProduct(const double v1[], int size, const double v2[]);

struct vector;

/* Test */

void printVector(const double v[], int size);

#endif