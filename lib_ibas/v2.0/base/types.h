//
// Created by Павел on 14.05.2017.
//

#pragma once

#include "../fwd.h"

/*---- BASE ----*/

typedef void *Object_t, *Pointer_t;
typedef char *CString_t;

typedef struct Vector String_s;
typedef String_s* String_t;

$declareType(Class);

typedef void (*Destroy_t)(Pointer_t);
typedef String_t (*ToString_t)(Pointer_t);
typedef int (*Compare_t)(Pointer_t, Pointer_t);

/*---- PRIMITIVES ----*/

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

/*---- EXCEPTION ----*/

/*---- COLLECTIONS ----*/

$declareType(Vector);
$declareType(LinkedList);

/*---- INPUT/OUTPUT ----*/

$declareType(Scanner);
typedef int (*Validator)(Object_t, Object_t);
