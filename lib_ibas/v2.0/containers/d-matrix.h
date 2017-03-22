#ifndef LABS_DMATRIX_H
#define LABS_DMATRIX_H

//TODO rewrite matrices

#include "lib_ibas/v2.0/base/base.h"
#include "lib_ibas/v2.0/io/console.h"

typedef struct {
  int rows, cols, error;
  double* ptr;
} DMatrix_t;

typedef struct {
  DMatrix_t (*create)(int rows, int cols);
  void (*destroy)(DMatrix_t* matrix);

  void (*input)(DMatrix_t* matrix, CString prompt);
  void (*print)(DMatrix_t* matrix);

  double (*get)(DMatrix_t* matrix, int i, int j);
  void (*set)(DMatrix_t* matrix, int i, int j, double val);

  double (*mean)(DMatrix_t* matrix);
} __DMatrix;
extern __DMatrix DMatrix;

#endif