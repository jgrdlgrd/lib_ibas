//
// Created by Павел on 07.04.2017.
//

#pragma once

#include "../fwd.h"

#define $class ToString

$declareStatic(
  String_t (*Object)(Object_t obj);
  String_t (*CStr)(CString cstr);

  String_t (*Int)(int val);
  String_t (*IntPtr)(int *val);
  String_t (*Double)(double val);
  String_t (*DoublePtr)(double *val);

  String_t (*IntPair)(IntPair val);
  String_t (*IntPairPtr)(IntPair *val);
  String_t (*DoublePair)(DoublePair val);
  String_t (*DoublePairPtr)(DoublePair *val);
);
