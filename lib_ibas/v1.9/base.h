//
// Created by Павел on 19.12.2016.
//

#ifndef LABS_BASE_H
#define LABS_BASE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <ctype.h>
#include <wctype.h>
#include <locale.h>
#include <limits.h>

typedef char* String;
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

#endif //LABS_BASE_H
