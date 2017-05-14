//
// Created by Павел on 21.12.2016.
//

#pragma once

#include "../fwd.h"

//TODO rewrite a few methods

struct Scanner {
  CString delimiters;
  String_t str;
  Object_t iter;
  FILE *stream;
  char last;
  bool multiline;
};

$declareClass(Scanner, {
  Scanner_t (*fromStream)(FILE *stream);
  Scanner_t (*fromString)(String_t str, Object_t iter);

  void (*destroy)(Scanner_t scan);
  String_t (*toString)(Scanner_t scan);

  String_t (*nextToken)(Scanner_t scan);
  void (*nextFormat)(Scanner_t scan, CString format, Pointer dest);

  char (*nextChar)(Scanner_t scan);
  int (*nextInt)(Scanner_t scan);
  double (*nextDouble)(Scanner_t scan);

  String_t (*nextLine)(Scanner_t scan);
  String_t (*nextText)(Scanner_t scan);

  void (*skipLine)(Scanner_t scan);
});
