//
// Created by Павел on 23.12.2016.
//

#pragma once

#define declareType(name) \
    typedef struct name name##_s; \
    typedef name##_s* name##_t;

#define declareInterface(name, members) \
    typedef Object name##_t; \
    typedef struct members *name##_i; \

#define declareClass(name, members) \
    typedef struct members name##_c; \
    extern name##_c name; \
    extern Object name##_class[];

#define implements(className, interfaceName, offset) #interfaceName, (void *) &className + (offset) * sizeof(void *)

//TODO consider other alternatives
#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })
