//
// Created by Павел on 20.03.2017.
//

#pragma once

#include "../fwd.h"
#include "to-string.h"
#include "../collections/list.h"
#include "../collections/vector.h" //included here to have fields of String_s defined

#define $class String

#define $String_fields $Vector_fields

$declareFields();

#define $String_static(_var, _fn) \
_fn(String_t, new, size_t capacity) \
_fn(String_t, format, CString format, ...) \
_fn(String_t, concat, String_t str1, String_t str2)

$declareStatic();

#define $String_methods(_fn) \
$Vector_methods(_fn) \
_fn(void, appendCStr, CString cstr) \
_fn(void, prependCStr, CString cstr)

$declareMethods();
