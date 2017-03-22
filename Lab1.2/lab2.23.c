//
// Created by Павел on 10.10.2016.
//

#include <limits.h>
#include <errno.h>
#include "lib_ibas/v1.0/io.h"
#include "lib_ibas/v1.0/doubleMatrix.h"

typedef struct DoubleMatrix InterpolationTable;

double lagrangeInterpolation(InterpolationTable *t, double x) {
  double sum = 0, product = 1;
  for (int i = 0; i < t->cols; i++) {
    double xi = get(t, 0, i), yi = get(t, 1, i), wi = get(t, 2, i);
    if (xi == x) {
      return yi;
    }
    //printf("%f %f %f\n", xi, yi, wi);
    sum += wi * yi / (x - xi);
    product *= x - xi;
    //printf("%f %f\n", sum, product);
  }
  return sum * product;
}

int inputTable(InterpolationTable *t, char *prompt) {
  int k = t->cols;
  double tmp;
  printf(prompt);
  putchar('\n');
  for (int i = 0; i < k; i++) {
    loop: {
      printf("x[%d] = ", i);
      errno = 0;
      tmp = readDouble(NULL, "Failure! Please enter a valid real number: ");
      if (errno) {
        return errno;
      }
      for (int j = 0; j < i; j++) {
        if (get(t, 0, j) == tmp) {
          printf("Duplicate point! Please enter another one:\n");
          goto loop;
        }
      }
    }
    set(t, 0, i, tmp);
    printf("y[%d] = ", i);
    set(t, 1, i, readDouble(NULL, "Failure! Please enter a valid real number: "));
    if (errno) {
      return errno;
    }
  }
  for (int i = 0; i < k; i++) {
    double w = 1, x = get(t, 0, i);
    for (int j = 0; j < k; j++) {
      if (j == i) {
        continue;
      }
      w *= x - get(t, 0, j);
    }
    set(t, 2, i, 1 / w);
  }
  return 0;
}

int main() {
  setRusLocale();
  printf("This program computes the Lagrange interpolation polynomial L(x).\n"
         "Author: Pavel Andreev\n\n");
  int k = readIntFromInterval("Enter the number of known points: ",
                              "Failure! Please enter a valid natural number: ", 1, INT_MAX);
  InterpolationTable t = createMatrix(3, k);
  if (t.error) {
    printf("Could not allocate the memory.\n");
    getchar();
    return EXIT_FAILURE;
  }
  inputTable(&t, "Enter the points:");
  putchar('\n');
  while (1) {
    double x = readDouble("Enter the argument of the polynomial:\n x = ",
                          "Failure! Please enter a valid real number: ");
    printf("L(%f) = %f\n", x, lagrangeInterpolation(&t, x));
    if (!prompt("Do you want to calculate the polynomial for another x? (Y/N): ")) {
      break;
    }
    putchar('\n');
  }
  destroyMatrix(&t);
  return EXIT_SUCCESS;
}
