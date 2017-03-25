//
// Created by Павел on 20.03.2017.
//

#pragma once

#include "../lib_ibas.h"
#include "../containers/vector.h"

typedef Vector_s String_s;
typedef Vector_t String_t;

declareClass(String, {
  String_t (*create)(size_t size);
  void (*destroy)(String_t str);

  char (*get)(String_t str, int i);
  void (*set)(String_t str, int i, char val);

  void (*add)(String_t str, char val);
  void (*insert)(String_t str, int i, char val);
  void (*remove)(String_t str, int i);

  void (*forEach)(String_t str, bool (*func)(String_t str, char ch, Object ctx), Object ctx);
  int (*find)(String_t str, char val);

  void (*clear)(String_t str);

  void (*concat)(String_t str1, String_t str2);
  void (*appendCStr)(String_t str1, CString str2);
  void (*prependCStr)(String_t str2, CString str1);
})
