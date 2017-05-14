//
// Created by Павел on 14.05.2017.
//

#include "wrappers.h"
#include "base.h"

//TODO implement

void __Int_destroy(int *ptr) {}

String_t __Int_toString(int *ptr) {
  return String.format("%d", *ptr);
}

int __Int_compare(int *ptr1, int *ptr2) {
  if (*ptr1 == *ptr2) return 0;
  return *ptr1 < *ptr2 ? -1 : 1;
}

$defineWrapper(Int);

void __Double_destroy(double *ptr) {}

String_t __Double_toString(double *ptr) {
  return String.format("%lf", *ptr);
}

int __Double_compare(double *ptr1, double *ptr2) {
  if (*ptr1 == *ptr2) return 0;
  return *ptr1 < *ptr2 ? -1 : 1;
}

$defineWrapper(Double);

void __CString_destroy(CString_t str) {}

String_t __CString_toString(CString_t cstr) {
  String_t str = String.create(0);
  __Vector_insertSlice(str, 0, cstr, strlen(cstr));
  return str;
}

int __CString_compare(CString_t str1, CString_t str2) {
  return strcmp(str1, str2);
}

$defineWrapper(CString);

void __Pair_destroy(Pair *ptr) {}

String_t __Pair_toString(Pair *ptr) {
  return String.format("%lf", *ptr);
}

int __Pair_compare(double *ptr1, double *ptr2) {
  if (*ptr1 == *ptr2) return 0;
  return *ptr1 < *ptr2 ? -1 : 1;
}

$defineWrapper(Pair);

void __IntPair_destroy(double *ptr) {}

String_t __IntPair_toString(IntPair *ptr) {
  return String.format("(%d, %d)", ptr->first, ptr->second);
}

int __IntPair_compare(double *ptr1, double *ptr2) {
  if (*ptr1 == *ptr2) return 0;
  return *ptr1 < *ptr2 ? -1 : 1;
}

$defineWrapper(IntPair);

void __DoublePair_destroy(double *ptr) {}

String_t __DoublePair_toString(DoublePair *ptr) {
  return String.format("(%lf, %lf)", ptr->first, ptr->second);
}

int __DoublePair_compare(DoublePair *ptr1, DoublePair *ptr2) {
  int ret = Double_w->compare(&ptr1->first, &ptr2->first);
  if (ret) return ret;
  return Double_w->compare(&ptr1->second, &ptr2->second);
}

$defineWrapper(DoublePair);

void __Triple_destroy(double *ptr) {}

String_t __Triple_toString(double *ptr) {
  return String.format("%lf", *ptr);
}

int __Triple_compare(double *ptr1, double *ptr2) {
  if (*ptr1 == *ptr2) return 0;
  return *ptr1 < *ptr2 ? -1 : 1;
}

$defineWrapper(Triple);
