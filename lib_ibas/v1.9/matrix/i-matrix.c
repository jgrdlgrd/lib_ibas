#include "i-matrix.h"
#include "lib_ibas/v1.9/io/console.h"

IMatrix_t __IMatrix_create(int rows, int cols) {
  IMatrix_t matrix;
  if (rows <= 0 || cols <= 0) {
    matrix.error = 1;
    return matrix;
  }
  matrix.error = 0;
  matrix.rows = rows;
  matrix.cols = cols;
  matrix.ptr = (int *) malloc(rows * cols * sizeof(int));
  if (matrix.ptr == NULL) {
    matrix.error = 2;
  }
  return matrix;
}

void __IMatrix_destroy(IMatrix_t *matrix) {
  if (matrix != NULL) {
    free(matrix->ptr);
  }
}

void __IMatrix_input(IMatrix_t *matrix, String prompt) {
  int rows = matrix->rows, cols = matrix->cols;
  int *ptr = matrix->ptr;
  printf(prompt, rows, cols);
  putchar('\n');
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      printf("matrix[%d][%d] = ", i, j);
      *(ptr++) = Console.inputInt(NULL, "Ошибка! Пожалуйста, введите целое число: ");
    }
  }
}

void __IMatrix_print(IMatrix_t *matrix) {
  int rows = matrix->rows, cols = matrix->cols;
  int *ptr = matrix->ptr;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      printf("%8d\t", *(ptr++));
    }
    Console.newLine();
  }
}

int __IMatrix_get(IMatrix_t *matrix, int i, int j) {
  return *(matrix->ptr + i * matrix->cols + j);
}

void __IMatrix_set(IMatrix_t *matrix, int i, int j, int val) {
  *(matrix->ptr + i * matrix->cols + j) = val;
}

int __IMatrix_mean(IMatrix_t *matrix) {
  int rows = matrix->rows, cols = matrix->cols;
  int *ptr = matrix->ptr;
  int sum = 0;
  int i = 0;
  for (; i < rows * cols; i++, ptr++) {
    sum += *ptr;
  }
  return sum / i;
}

__IMatrix IMatrix = {
    __IMatrix_create,
    __IMatrix_destroy,
    __IMatrix_input,
    __IMatrix_print,
    __IMatrix_get,
    __IMatrix_set,
    __IMatrix_mean
};
