//
// Created by Павел on 20.03.2017.
//

#pragma once

#include "base.h"
#include "../containers/vector.h"
#include "../containers/generic-vector.h"

typedef Vector_s String_s;
typedef String_s* String_t;

#include "to-string.h"

declareClass(String, {
  String_t (*create)(size_t capacity);
  void (*destroy)(String_t str);
  String_t (*toString)(String_t str);

  void (*ensureCapacity)(String_t str, size_t capacity);

  char (*get)(String_t str, int i);
  void (*set)(String_t str, int i, char val);

  void (*add)(String_t str, char val);
  void (*insert)(String_t str, int i, char val);
  void (*addAll)(String_t str1, String_t str2);
  void (*insertAll)(String_t str1, int i, String_t str2);

  void (*remove)(String_t str, int i);
  void (*clear)(String_t str);

  int (*indexOf)(String_t str, char val);

  Object (*iter)(String_t str, int i);
  Object (*begin)(String_t str);
  Object (*end)(String_t str);
  Object (*find)(String_t str, char obj);

  Object (*iterNext)(String_t str, Object iter);
  Object (*iterPrev)(String_t str, Object iter);
  Object (*iterJump)(String_t str, Object iter, int length);

  char (*iterGet)(String_t str, Object iter);
  void (*iterSet)(String_t str, Object iter, char val);

  void (*iterInsert)(String_t str, Object iter, char val);
  void (*iterInsertAll)(String_t str1, Object iter, String_t str2);

  void (*iterRemove)(String_t str, Object iter);

  String_t (*format)(CString format, ...);
  String_t (*concat)(String_t str1, String_t str2);

  void (*appendCStr)(String_t str, CString cstr);
  void (*prependCStr)(String_t str, CString cstr);
});
