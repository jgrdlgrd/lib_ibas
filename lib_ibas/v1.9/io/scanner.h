//
// Created by Павел on 21.12.2016.
//

#ifndef LABS_SCANNER_H
#define LABS_SCANNER_H

#include "lib_ibas/v1.9/base.h"

#define BUFFER_LENGTH 256;

typedef struct {
  FILE *stream;
  String delimiters;

  int (*next)(String, void*);
  String (*nextToken)();

  int (*nextInt)();
  double (*nextDouble)();
  String (*nextLine)();
  String (*nextText)();
} Scanner_t;
extern Scanner_t Scanner;

#endif //LABS_PRIMITIVE_H
