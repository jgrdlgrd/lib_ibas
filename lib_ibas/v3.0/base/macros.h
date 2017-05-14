//
// Created by Павел on 23.12.2016.
//

#pragma once

#define $str(arg) $str1(arg)
#define $str1(arg) #arg

#define $paste(arg1, arg2) $paste1(arg1, arg2)
#define $paste1(arg1, arg2) arg1 ## arg2
#define $paste3(arg1, arg2, arg3) $paste($paste1(arg1, arg2), arg3)

#define $fnType(ret, args...) typeof(ret (*)(args))
#define $arrType(type, size) typeof(type[size])
#define $ptrType(type) typeof(type*)

#define max(a, b) \
   ({ typeof (a) _a = (a); \
       typeof (b) _b = (b); \
     _a > _b ? _a : _b; })

#define min(a, b) \
   ({ typeof (a) _a = (a); \
       typeof (b) _b = (b); \
     _a < _b ? _a : _b; })
