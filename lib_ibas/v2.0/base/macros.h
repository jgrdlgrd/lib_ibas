//
// Created by Павел on 23.12.2016.
//

#pragma once

#define declareFields(name, fields) \
    typedef struct fields name##_s; \
    typedef name##_s* name##_t;

#define declareClass(name, members) \
    typedef struct members name##_t_; \
    extern name##_t_ name;

//TODO consider other alternatives
#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })
