//
// Created by Павел on 20.03.2017.
//

#pragma once

#include "../fwd.h"
#include "../collections/list.h"
#include "../collections/vector.h" //included here to have fields of String_s defined

$declareNamespace(String) {
  Class_t class;
  String_t (*create)(size_t capacity);
  String_t (*format)(CString_t format, ...);
  String_t (*concat)(String_t str1, String_t str2);

  $ObjectMethods(String);

  $ListMethods(String, char);

  void (*ensureCapacity)(String_t self, size_t capacity);

  CString_t (*CStr)(String_t self);
  void (*appendCStr)(String_t str, CString_t cstr);
  void (*prependCStr)(String_t str, CString_t cstr);
};
