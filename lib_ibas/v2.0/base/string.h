//
// Created by Павел on 20.03.2017.
//

#pragma once

#include "base.h"
#include "../collections/list.h"
#include "../collections/vector.h"
#include "../collections/generic-vector.h"

typedef Vector_s String_s;
typedef String_s* String_t;

#include "to-string.h"

declareClass(String, {
  String_t (*create)(size_t capacity);
  void (*destroy)(String_t str);
  String_t (*toString)(String_t str);

  void (*ensureCapacity)(String_t str, size_t capacity);

  ListMethods(String, str, char);

  String_t (*format)(CString format, ...);
  String_t (*concat)(String_t str1, String_t str2);

  void (*appendCStr)(String_t str, CString cstr);
  void (*prependCStr)(String_t str, CString cstr);
});
