//
// Created by Павел on 20.03.2017.
//

#pragma once

#include "lib_ibas/v2.0/lib_ibas.h"
#include "lib_ibas/v2.0/containers/vector.h"
#include "lib_ibas/v2.0/containers/generic-list.h"

typedef Vector_s String_s;
typedef Vector_t String_t;

declareClass(String, {
  String_t (*create)(size_t size);

  genericListMethodsDeclStripped(String_t, str, char);

  String_t (*toString)(String_t str);
  void (*concat)(String_t str1, String_t str2);
  void (*appendCStr)(String_t str1, CString str2);
  void (*prependCStr)(String_t str2, CString str1);
})
