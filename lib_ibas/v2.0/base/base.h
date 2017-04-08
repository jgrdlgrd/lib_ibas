//
// Created by Павел on 19.12.2016.
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
#include "macros.h"

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

//TODO optimize capabilities provided here
//TODO rethink method names
declareClass(Ibas, {
  void (*init)();
  void (*finish)();

  Object (*alloc)(size_t size, CString message);

  Object (*getClass)(Object obj);
  Object (*getImpl)(Object obj, CString interface);
});
