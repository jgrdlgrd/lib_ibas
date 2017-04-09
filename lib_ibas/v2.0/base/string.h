//
// Created by Павел on 20.03.2017.
//

#pragma once

#include "../fwd.h"
#include "to-string.h"
#include "../collections/list.h"
#include "../collections/vector.h" //included here to have fields of String_s defined

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
