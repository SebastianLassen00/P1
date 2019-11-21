#ifndef VECTORS_H
#define VECTORS_H

void copyVector(const double in[], int size, double out[]);
void addVector(const double v1[], const double v2[], int size, double sum[]);
void scaleVector(const double v[], double scale, double out[]);
double lengthOfVector(const double v[]);
void normalizeVector(const double v[], double out[]);
double dotProduct(const double v1[], const double v2[]);

/* Test */

void printVector(const double v[], int size);

#endif