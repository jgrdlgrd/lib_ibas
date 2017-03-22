#include "d-matrix.h"

DMatrix_t __DMatrix_create(int rows, int cols) {
  DMatrix_t matrix;
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

void __DMatrix_destroy(DMatrix_t *matrix) {
  if (matrix != NULL) {
    free(matrix->ptr);
  }
}

void __DMatrix_input(DMatrix_t *matrix, CString prompt) {
  int rows = matrix->rows, cols = matrix->cols;
  double *ptr = matrix->ptr;
  printf(prompt, rows, cols);
  putchar('\n');
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      printf("matrix[%d][%d] = ", i, j);
      *(ptr++) = Console.inputDouble(NULL, "Ошибка! Пожалуйста, введите рациональное число: ");
    }
  }
}

void __DMatrix_print(DMatrix_t *matrix) {
  int rows = matrix->rows, cols = matrix->cols;
  double *ptr = matrix->ptr;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      printf("%.4f\t", *(ptr++));
    }
    putchar('\n');
  }
}

double __DMatrix_get(DMatrix_t *matrix, int i, int j) {
  return *(matrix->ptr + i * matrix->cols + j);
}

void __DMatrix_set(DMatrix_t *matrix, int i, int j, double val) {
  *(matrix->ptr + i * matrix->cols + j) = val;
}

double __DMatrix_mean(DMatrix_t *matrix) {
  int rows = matrix->rows, cols = matrix->cols;
  double *ptr = matrix->ptr;
  double sum = 0;
  int i = 0;
  for (; i < rows * cols; i++, ptr++) {
    sum += *ptr;
  }
  return sum / i;
}

__DMatrix DMatrix = {
    __DMatrix_create,
    __DMatrix_destroy,
    __DMatrix_input,
    __DMatrix_print,
    __DMatrix_get,
    __DMatrix_set,
    __DMatrix_mean
};
