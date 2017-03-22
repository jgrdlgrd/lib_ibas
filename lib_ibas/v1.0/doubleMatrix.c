#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "doubleMatrix.h"
#include "io.h"

DoubleMatrix createMatrix(int rows, int cols) {
  DoubleMatrix matrix;
  if (rows <= 0 || cols <= 0) {
    matrix.error = 1;
    return matrix;
  }
  matrix.error = 0;
  matrix.rows = rows;
  matrix.cols = cols;
  matrix.ptr = (double *) malloc(rows * cols * sizeof(double));
  if (matrix.ptr == NULL) {
    matrix.error = 2;
  }
  return matrix;
}

void destroyMatrix(DoubleMatrix *matrix) {
  if (matrix != NULL) {
    free(matrix->ptr);
  }
}

int inputMatrix(DoubleMatrix *matrix, char *prompt) {
  int rows = matrix->rows, cols = matrix->cols;
  double *ptr = matrix->ptr;
  printf(prompt, rows, cols);
  putchar('\n');
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      printf("matrix[%d][%d] = ", i, j);
      errno = 0;
      *(ptr++) = readDouble(NULL, "Failure! Please enter a valid real number: ");
      if (errno) {
        return errno;
      }
    }
  }
  return 0;
}

int outputMatrix(DoubleMatrix *matrix, char *message) {
  int rows = matrix->rows, cols = matrix->cols;
  double *ptr = matrix->ptr;
  printf(message);
  putchar('\n');
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      printf("%.4f\t", *(ptr++));
    }
    putchar('\n');
  }
  return 0;
}

double matrixMean(DoubleMatrix *matrix) {
  int rows = matrix->rows, cols = matrix->cols;
  double *ptr = matrix->ptr;
  double sum = 0;
  int i = 0;
  for (; i < rows * cols; i++, ptr++) {
    sum += *ptr;
  }
  return sum / i;
}

double get(DoubleMatrix *m, int i, int j) {
  return *(m->ptr + i * m->cols + j);
}

void set(DoubleMatrix* m, int i, int j, double val) {
  *(m->ptr + i * m->cols + j) = val;
}
