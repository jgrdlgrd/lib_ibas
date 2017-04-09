//
// Created by Павел on 21.12.2016.
//

#pragma once

#include "../fwd.h"

#define SCANNER_BUFFER_LENGTH 256;

//TODO rewrite a few methods

declareClass(Scanner, {
  FILE *stream;
  CString delimiters;

  int (*next)(CString, Object);
  CString (*nextToken)();

  int (*nextInt)();
  double (*nextDouble)();
  CString (*nextLine)();
  CString (*nextText)();
});
