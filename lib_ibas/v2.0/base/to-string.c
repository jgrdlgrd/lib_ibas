//
// Created by Павел on 07.04.2017.
//

#include "to-string.h"

//TODO implement
String_t __ToString_Object(Object obj) {
  throw(RuntimeException, "Not implemented!");
}

String_t __ToString_CStr(CString cstr) {
  String_t str = String.create(0);
  __Vector_insertSlice(str, 0, cstr, strlen(cstr));
  return str;
}

String_t __ToString_Int(int val) {
  return String.format("%d", val);
}

String_t __ToString_IntPtr(int *val) {
  return ToString.Int(*val);
}

String_t __ToString_Double(double val) {
  return String.format("%lf", val);
}

String_t __ToString_DoublePtr(double *val) {
  return ToString.Double(*val);
}

ToString_c ToString = {
    __ToString_Object,
    __ToString_CStr,
    __ToString_Int,
    __ToString_IntPtr,
    __ToString_Double,
    __ToString_DoublePtr
};
