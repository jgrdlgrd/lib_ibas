/*
 * File:   lab1.c
 * Author: Pavel Andreev
 * Created on 19 September 2016, 23:09
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "lib_ibas/v1.0/io.h"
#include "lib_ibas/v1.0/doubleMatrix.h"

int transformMatrix(DoubleMatrix *matrix, double delta) {
  double mean = matrixMean(matrix);
  int rows = matrix->rows, cols = matrix->cols;
  double *ptr = matrix->ptr;
  for (int i = 0; i < rows * cols; i++, ptr++) {
    if (fabs(*ptr - mean) > delta) {
      *ptr = 0;
    }
  }
  return 0;
}

int main(int argc, char **argv) {
  printf("This program replaces with zeroes all elements in a matrix which differ from the arithmetic mean of that "
         "matrix more than by a given delta.\n"
         "Author: Pavel Andreev\n\n");
  int rows = readIntFromInterval("Please enter the number of rows in the matrix: ",
                                 "Failure! Please enter a valid natural number: ", 1, INT_MAX);
  int cols = readIntFromInterval("Please enter the number of columns in the matrix: ",
                                 "Failure! Please enter a valid natural number: ", 1, INT_MAX);
  DoubleMatrix matrix = createMatrix(rows, cols);
  if (matrix.error) {
    printf("Could not allocate the memory.\n");
    getchar();
    return EXIT_FAILURE;
  }
  putchar('\n');
  inputMatrix(&matrix, "Fill the matrix of %d rows and %d columns:");
  putchar('\n');
  outputMatrix(&matrix, "You have entered:");
  putchar('\n');
  printf("The arithmetic mean of the matrix equals %f\n", matrixMean(&matrix));
  putchar('\n');
  transformMatrix(&matrix, readDouble("Please enter the delta: ", "Failure! Please enter a valid real number: "));
  putchar('\n');
  outputMatrix(&matrix, "After transform:");
  destroyMatrix(&matrix);
  getchar();
  return EXIT_SUCCESS;
}


