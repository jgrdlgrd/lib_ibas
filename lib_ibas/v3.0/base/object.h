//
// Created by Павел on 15.04.2017.
//

#pragma once

#include "../fwd.h"

#define $class Object

#define $Object_static(_var, _fn) \
_fn(Pointer, getClass, Object_t obj) \
_fn(Pointer, getImpl, Object_t obj, CString interface) \
_fn(void, destroy, Object_t obj)

$declareStatic();

#define $Object_fields()

$declareFields();

#define $Object_methods(_fn) \
_fn(void, destroy) \
_fn(String_t, toString)

$declareMethods();
