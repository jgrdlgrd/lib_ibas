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

typedef char* CString;
typedef void* Object;

typedef int (*Validator)(Object, Object);

typedef struct {
  Object first, second;
} Pair;

typedef struct {
  int first, second;
} IntPair;

typedef struct {
  double first, second;
} DoublePair;

typedef struct {
  Object first, second, third;
} Triple;

typedef struct Vector String_s;
typedef String_s* String_t;

typedef String_t (*ToString_t)(Object);

declareType(Vector);

declareType(LinkedList);
