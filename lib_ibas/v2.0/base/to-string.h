//
// Created by Павел on 07.04.2017.
//

#pragma once

#include "string.h"

typedef String_t (*ToString_t)(Object);

declareClass(ToString, {
  String_t (*Object)(Object obj);
  String_t (*CStr)(CString cstr);

  String_t (*Int)(int val);
  String_t (*IntPtr)(int *val);
  String_t (*Double)(double val);
  String_t (*DoublePtr)(double *val);
});
