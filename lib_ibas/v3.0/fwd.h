//
// Created by Павел on 09.04.2017.
//

#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#include "e4c/e4c.h"
#include "base/macros.h"
#include "base/oop-macros.h"

E4C_DECLARE_EXCEPTION(EOFException);
E4C_DECLARE_EXCEPTION(FormatException);
E4C_DECLARE_EXCEPTION(ClassCastException);
E4C_DECLARE_EXCEPTION(EmptyTokenException);

typedef char *CString;
typedef void *Pointer;

$declareClass(Object);

typedef int (*Validator)(Object_t, Object_t);

typedef struct {
  Object_t first, second;
} Pair;

typedef struct {
  int first, second;
} IntPair;

typedef struct {
  double first, second;
} DoublePair;

typedef struct {
  Object_t first, second, third;
} Triple;

$declareClass(String);

typedef String_t (*ToString_t)(Object_t);

$declareInterface(List);

$declareClass(Vector);

$declareClass(LinkedList);

$declareClass(Scanner);

#include "base/object.h"
