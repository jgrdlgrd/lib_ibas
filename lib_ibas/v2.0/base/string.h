//
// Created by Павел on 20.03.2017.
//

#pragma once

#include "base.h"
#include "../containers/vector.h"
#include "../containers/generic-vector.h"

typedef Vector_s String_s;
typedef Vector_t String_t;

typedef String_t (*ToString_t)(Object);

declareClass(String, {
  String_t (*create)(size_t size);
  void (*destroy)(String_t str);
  String_t (*toString)(String_t str);

  char (*get)(String_t str, int i);
  void (*set)(String_t str, int i, char val);

  void (*add)(String_t str, char val);
  void (*insert)(String_t str, int i, char val);
  void (*addAll)(String_t str1, String_t str2);
  void (*insertAll)(String_t str1, int i, String_t str2);

  void (*remove)(String_t str, int i);
  void (*clear)(String_t str);

  void (*forEach)(String_t str, bool (*func)(String_t str, char ch, Object ctx), Object ctx);
  int (*find)(String_t str, char val);

  void (*ensureCapacity)(String_t str, size_t capacity);

  String_t (*fromCStr)(CString cstr);
  String_t (*fromInt)(int val);
  String_t (*fromDouble)(double val);
  String_t (*fromObject)(Object obj);

  String_t (*format)(CString format, ...);
  String_t (*concat)(String_t str1, String_t str2);

  void (*appendCStr)(String_t str, CString cstr);
  void (*prependCStr)(String_t str, CString cstr);
});
