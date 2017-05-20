//
// Created by Павел on 21.12.2016.
//

#pragma once

#include "../fwd.h"

//TODO rewrite a few methods

$defineType(Scanner) {
  Class_t class;
  CString_t delimiters;
  String_t str;
  Pointer_t iter;
  FILE *stream;
  char last;
  bool multiline;
};

$declareNamespace(Scanner) {
  Class_t class;
  
  Scanner_t (*fromStream)(FILE *stream);
  Scanner_t (*fromString)(String_t str, Pointer_t iter);

  $ObjectMethods(Scanner);

  String_t (*nextToken)(Scanner_t self);
  void (*nextFormat)(Scanner_t self, CString_t format, Pointer_t dest);

  char (*nextChar)(Scanner_t self);
  int (*nextInt)(Scanner_t self);
  double (*nextDouble)(Scanner_t self);

  String_t (*nextLine)(Scanner_t self);
  String_t (*nextText)(Scanner_t self);

  unsigned (*skip)(Scanner_t self);
  unsigned (*skipLine)(Scanner_t self);
};
