//
// Created by Павел on 21.03.2017.
//

#pragma once

//TODO choose method prefix

#define genericListMethodsDeclStripped(classType, paramName, elemType) \
    void (*destroy)(classType paramName); \
     \
    elemType (*get)(classType paramName, int i); \
    void (*set)(classType paramName, int i, elemType val); \
     \
    void (*add)(classType paramName, elemType val); \
    void (*insert)(classType paramName, int i, elemType val); \
    void (*remove)(classType paramName, int i); \
     \
    void (*forEach)(classType paramName, bool (*func)(classType paramName, elemType val, Object ctx), Object ctx); \
    int (*find)(classType paramName, elemType val); \
     \
    void (*clear)(classType paramName);

#define genericListMethodsDecl(classType, paramName, elemType) \
    classType (*create)(size_t size); \
    genericListMethodsDeclStripped(classType, paramName, elemType) \
    String_t (*toString)(classType paramName);

#define genericListMethodsImplStripped(baseClass, classType, paramName, elemType) \
    void __##classType##_destroy(classType paramName) { \
      baseClass.destroy(paramName); \
    } \
     \
    elemType __##classType##_get(classType paramName, int i) { \
      return *(elemType*)baseClass.get(paramName, i); \
    } \
     \
    void __##classType##_set(classType paramName, int i, elemType val) { \
      baseClass.set(paramName, i, &val); \
    } \
     \
    void __##classType##_add(classType paramName, elemType val) { \
      baseClass.add(paramName, &val); \
    } \
     \
    void __##classType##_insert(classType paramName, int i, elemType val) { \
      baseClass.insert(paramName, i, &val); \
    } \
     \
    void __##classType##_remove(classType paramName, int i) { \
      baseClass.remove(paramName, i); \
    } \
     \
    bool __##classType##_forEachIntermediate(classType paramName, Object element, Object ctx) { \
      Pair *p = (Pair*) ctx; \
      return ((bool(*)(classType, elemType, Object))(p->first))(paramName, *(elemType*)element, p->second); \
    } \
     \
    void __##classType##_forEach(classType paramName, bool (*func)(classType paramName, elemType element, Object ctx), Object ctx) { \
      Pair p = {func, ctx}; \
      baseClass.forEach(paramName, __##classType##_forEachIntermediate, &p); \
    } \
     \
    int __##classType##_find(classType paramName, elemType val) { \
      return baseClass.find(paramName, &val); \
    } \
     \
    void __##classType##_clear(classType paramName) { \
      baseClass.clear(paramName); \
    }

#define genericListMethodsImpl(baseClass, classType, paramName, elemType) \
    classType __##classType##_create(size_t size) { \
      return baseClass.create(size, sizeof(elemType)); \
    } \
    genericListMethodsImplStripped(baseClass, classType, paramName, elemType) \
    //TODO toString

#define genericListMethodsListStripped(classType) \
    __##classType##_destroy, \
    __##classType##_get, \
    __##classType##_set, \
    __##classType##_add, \
    __##classType##_insert, \
    __##classType##_remove, \
    __##classType##_forEach, \
    __##classType##_find, \
    __##classType##_clear

#define genericListMethodsList(classType) \
    __##classType##_create, \
    genericListMethodsListStripped(classType), \
    __##classType##_toString
