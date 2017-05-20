//
// Created by Павел on 23.12.2016.
//

#pragma once

/*---- BASIC ----*/

#define $str(arg) $str1(arg)
#define $str1(arg) #arg

#define $paste(arg1, arg2) $paste1(arg1, arg2)
#define $paste1(arg1, arg2) arg1 ## arg2
#define $paste3(arg1, arg2, arg3) $paste($paste1(arg1, arg2), arg3)

#define $fnType(ret, args...) typeof(ret (*)(args))
#define $arrType(type, size) typeof(type[size])
#define $ptrType(type) typeof(type*)

/*---- UTILITY ----*/

#define $max(a, b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define $min(a, b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

/*---- NAMESPACES AND TYPES ----*/

#define $declareType(name) \
    typedef struct name name##_s; \
    typedef name##_s* name##_t;

#define $defineType(name) struct name

#define $declareInterface(name) \
    typedef struct name* name##_i; \
    struct name

#define $declareNamespace(name) \
    extern struct name##_c name; \
    struct name##_c

#define $defineNamespace(name) struct name##_c name =

#define $declareWrapper(name) extern Class_t name##_w

#define $defineWrapper(name) \
    Class_s name##_c = (Class_s) { \
      (Destroy_t) __##name##_destroy, \
      (ToString_t) __##name##_toString, \
      (Compare_t) __##name##_compare \
    }; \
    Class_t name##_w = &name##_c
