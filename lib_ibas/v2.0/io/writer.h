//
// Created by Павел on 21.05.2017.
//

#pragma once

#include "../fwd.h"

$defineType(Writer) {
  Class_t class;
  CString_t lineSeparator;
  String_t str;
  Pointer_t iter;
  FILE *stream;
  bool destroySource;
};

$declareNamespace(Writer) {
  Class_t class;

  Writer_t (*fromStream)(FILE *stream);
  Writer_t (*fromString)(String_t str, Pointer_t iter);

  $ObjectMethods(Writer);

  void (*newLine)(Writer_t self);
  void (*print)(Writer_t self, String_t str);
  void (*println)(Writer_t self, String_t str);
  void (*CPrint)(Writer_t self, CString_t str);
  void (*CPrintln)(Writer_t self, CString_t str);
  void (*printObj)(Writer_t self, Object_t obj);
  void (*format)(Writer_t self, CString_t format, ...);
};
