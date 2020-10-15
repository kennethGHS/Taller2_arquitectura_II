//
// Created by kenneth on 14/10/20.
//
#include <stdio.h>
#include <stdlib.h>
#include "Practicos.h"
#include <omp.h>

void euler_serial(int iterations) {
    double start_time = omp_get_wtime();
    double e;
    double * a = malloc(sizeof(double )*iterations);
    a[0] = 1.0;
    for (int i = 1; i < iterations; i++)
    {
        a[i] = a[i-1] / i;
    }
    e = 1.;
    for (int i = iterations - 1; i > 0; i--)
        e += a[i];

    double finishtime = omp_get_wtime() - start_time;
    printf("Se tardo: %lf", finishtime);
    printf("Euler constant e = %.16lf\n", e);
    free(a);
}

void euler_parallel(int iterations) {
    double start_time = omp_get_wtime();
    double e;
    double * a = malloc(sizeof(double )*iterations);
    e = 1.;
    a[0] = 1.0;
#pragma omp parallel
    {
#pragma omp for
        for (int i = 1; i < iterations; i++)
        {
            a[i] = a[i-1] / i;
        }

#pragma omp for reduction(+:e)
        for (int i = iterations - 1; i > 0; i--)
            e += a[i];
    }
    double finishtime = omp_get_wtime() - start_time;
    printf("Se tardo: %lf", finishtime);
    printf("Euler constant e = %.16lf\n", e);
    free(a);
}

void SAXPY_serial(int sizeArray) {
    float a = 2.0;
    float *y = createFloatArray(sizeArray);
    float *x = createFloatArray(sizeArray);
    double start_time = omp_get_wtime();
    for (int i = 0; i < sizeArray; ++i) {
        y[i] = a * x[i] + y[i];
    }
    double finishtime = omp_get_wtime() - start_time;
    printf("Se tardo: %lf", finishtime);
    free(y);
    free(x);
}


void SAXPY_parallel(int sizeArray) {
    float a = 2.0;
    float *y = createFloatArray(sizeArray);
    float *x = createFloatArray(sizeArray);
    double start_time = omp_get_wtime();
#pragma omp parallel
    {
#pragma omp for private(a)
        for (int i = 0; i < sizeArray; ++i) {
            y[i] = a * x[i] + y[i];
        }
    }
    double finishtime = omp_get_wtime() - start_time;
    printf("Se tardo: %lf", finishtime);
    free(y);
    free(x);
}

float *createFloatArray(int size) {
    float *array = malloc(sizeof(float) * size);
    float a = 5.0;

    for (int i = 0; i < size; i++) {
        array[i] = (float) rand() / (float) (RAND_MAX) * a;
    }
    return array;
}
