//
// Created by Павел on 07.04.2017.
//

#pragma once

#include "../fwd.h"

#define $ListMethods(className, elemType) \
    List_i (*toList)(className##_t self); \
     \
    elemType (*get)(className##_t self, int i); \
    void (*set)(className##_t self, int i, elemType val); \
     \
    void (*add)(className##_t self, elemType val); \
    void (*insert)(className##_t self, int i, elemType val); \
    void (*addAll)(className##_t self, className##_t obj); \
    void (*insertAll)(className##_t self, int i, className##_t obj); \
     \
    void (*remove)(className##_t self, int i); \
    void (*clear)(className##_t self); \
     \
    size_t (*size)(className##_t self); \
    int (*indexOf)(className##_t self, elemType obj); \
     \
    Object_t (*iter)(className##_t self, int i); \
    Object_t (*begin)(className##_t self); \
    Object_t (*end)(className##_t self); \
    Object_t (*find)(className##_t self, elemType val); \
     \
    Object_t (*iterNext)(className##_t self, Object_t iter); \
    Object_t (*iterPrev)(className##_t self, Object_t iter); \
    Object_t (*iterJump)(className##_t self, Object_t iter, int length); \
     \
    elemType (*iterGet)(className##_t self, Object_t iter); \
    void (*iterSet)(className##_t self, Object_t iter, elemType val); \
     \
    void (*iterInsert)(className##_t self, Object_t iter, elemType val); \
    void (*iterInsertAll)(className##_t self, Object_t iter, className##_t obj); \
     \
    void (*iterRemove)(className##_t self, Object_t iter)

$declareInterface(List) {
  $ListMethods(Object, Pointer_t);
};

$declareNamespace(List) {
  String_t (*toString)(Object_t list, List_i class, ToString_t stringifier);
};
