//
// Created by Павел on 16.03.2017.
//

//TODO add slice, clone, removeRange

#pragma once

#include "../fwd.h"
#include "list.h"

#define VECTOR_GROWTH_FACTOR 1.5

#define $class Vector

#define $Vector_static(_var, _fn) \
_fn(Vector_t, new, size_t elemSize, size_t capacity, ToString_t stringifier)

$declareStatic();

#define $Vector_fields(_var, _fn) \
_var(size_t, size) \
_var(size_t, elemSize) \
_var(size_t, capacity) \
_var(Pointer, storage) \
_var(ToString_t, stringifier)

$declareFields();

#define $Vector_methods(_fn) \
$Object_methods(_fn) \
_fn(void, ensureCapacity, size_t capacity) \
$List_methods(_fn, Pointer)

$declareMethods();

//expose internals
Vector_t __Vector_new(size_t elemSize, size_t capacity, ToString_t stringifier);
void __Vector_destroy(Vector_t vec);
String_t __Vector_toString(Vector_t vec);
void __Vector_ensureCapacity(Vector_t vec, size_t capacity);
Pointer __Vector_get(Vector_t vec, int i);
void __Vector_set(Vector_t vec, int i, Pointer val);
void __Vector_insertSlice(Vector_t vec, int i, Pointer slice, size_t size);
void __Vector_add(Vector_t vec, Pointer val);
void __Vector_insert(Vector_t vec, int i, Pointer val);
void __Vector_addAll(Vector_t vec1, List_t vec2);
void __Vector_insertAll(Vector_t vec1, int i, List_t vec2);
void __Vector_remove(Vector_t vec, int i);
void __Vector_clear(Vector_t vec);
int __Vector_indexOf(Vector_t vec, Pointer val);
Pointer __Vector_iter(Vector_t vec, int i);
Pointer __Vector_begin(Vector_t vec);
Pointer __Vector_end(Vector_t vec);
Pointer __Vector_find(Vector_t vec, Pointer val);
Pointer __Vector_iterNext(Vector_t vec, Pointer iter);
Pointer __Vector_iterPrev(Vector_t vec, Pointer iter);
int __Vector_iterToIndex(Vector_t vec, Pointer iter);
Pointer __Vector_iterJump(Vector_t vec, Pointer iter, int length);
Pointer __Vector_iterGet(Vector_t vec, Pointer iter);
void __Vector_iterSet(Vector_t vec, Pointer iter, Pointer val);
void __Vector_iterInsert(Vector_t vec, Pointer iter, Pointer val);
void __Vector_iterInsertAll(Vector_t vec1, Pointer iter, List_t vec2);
void __Vector_iterRemove(Vector_t vec, Pointer iter);
