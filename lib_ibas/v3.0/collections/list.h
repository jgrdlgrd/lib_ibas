//
// Created by Павел on 07.04.2017.
//

#pragma once

#include "../fwd.h"

#define $class List

#define $List_methods(_fn, elemType) \
    _fn(elemType, get, int i) \
    _fn(void, set, int i, elemType val) \
     \
    _fn(void, add, elemType val) \
    _fn(void, insert, int i, elemType val) \
    _fn(void, addAll, List_t list) \
    _fn(void, insertAll, int i, List_t list) \
     \
    _fn(void, remove, int i) \
    _fn(void, clear) \
     \
    _fn(int, indexOf, elemType obj) \
     \
    _fn(Pointer, iter, int i) \
    _fn(Pointer, begin) \
    _fn(Pointer, end) \
    _fn(Pointer, find, elemType val) \
     \
    _fn(Pointer, iterNext, Pointer iter) \
    _fn(Pointer, iterPrev, Pointer iter) \
    _fn(Pointer, iterJump, Pointer iter, int length) \
     \
    _fn(elemType, iterGet, Pointer iter) \
    _fn(void, iterSet, Pointer iter, elemType val) \
     \
    _fn(void, iterInsert, Pointer iter, elemType val) \
    _fn(void, iterInsertAll, Pointer iter, List_t list) \
     \
    _fn(void, iterRemove, Pointer iter)


$defineInterface(Pointer);

#define $List_static(_var, _fn) \
_fn(String_t, toString, List_t list, ToString_t stringifier)

$declareStatic();
