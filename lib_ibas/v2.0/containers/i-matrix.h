#ifndef LABS_IMATRIX_H
#define LABS_IMATRIX_H

#include "lib_ibas/v2.0/base/base.h"
#include "lib_ibas/v2.0/io/console.h"

typedef struct {
  int rows, cols, error;
  int* ptr;
} IMatrix_t;

typedef struct {
  IMatrix_t (*create)(int rows, int cols);
  void (*destroy)(IMatrix_t* matrix);

  void (*input)(IMatrix_t* matrix, CString prompt);
  void (*print)(IMatrix_t* matrix);

  int (*get)(IMatrix_t* matrix, int i, int j);
  void (*set)(IMatrix_t* matrix, int i, int j, int val);

  int (*mean)(IMatrix_t* matrix);
} __IMatrix;
extern __IMatrix IMatrix;

#endif