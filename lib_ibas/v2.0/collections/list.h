//
// Created by Павел on 07.04.2017.
//

#pragma once

#include "../fwd.h"

#define ListMethods(className, instanceName, elemType) \
    ToString_t (*getToStringFn)(className##_t instanceName); \
     \
    elemType (*get)(className##_t instanceName, int i); \
    void (*set)(className##_t instanceName, int i, elemType val); \
     \
    void (*add)(className##_t instanceName, elemType val); \
    void (*insert)(className##_t instanceName, int i, elemType val); \
    void (*addAll)(className##_t instanceName##1, className##_t instanceName##2); \
    void (*insertAll)(className##_t instanceName##1, int i, className##_t instanceName##2); \
     \
    void (*remove)(className##_t instanceName, int i); \
    void (*clear)(className##_t instanceName); \
     \
    int (*indexOf)(className##_t instanceName, elemType obj); \
     \
    Object (*iter)(className##_t instanceName, int i); \
    Object (*begin)(className##_t instanceName); \
    Object (*end)(className##_t instanceName); \
    Object (*find)(className##_t instanceName, elemType val); \
     \
    Object (*iterNext)(className##_t instanceName, Object iter); \
    Object (*iterPrev)(className##_t instanceName, Object iter); \
    Object (*iterJump)(className##_t instanceName, Object iter, int length); \
     \
    elemType (*iterGet)(className##_t instanceName, Object iter); \
    void (*iterSet)(className##_t instanceName, Object iter, elemType val); \
     \
    void (*iterInsert)(className##_t instanceName, Object iter, elemType val); \
    void (*iterInsertAll)(className##_t instanceName##1, Object iter, className##_t instanceName##2); \
     \
    void (*iterRemove)(className##_t instanceName, Object iter);


declareInterface(List, {
  ListMethods(List, list, Object);
});

declareClass(List, {
  String_t (*toString)(List_t list);
});
