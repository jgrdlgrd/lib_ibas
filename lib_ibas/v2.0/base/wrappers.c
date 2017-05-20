//
// Created by Павел on 14.05.2017.
//

#include "wrappers.h"
#include "base.h"

//TODO implement

static void __Int_destroy(int *ptr) {}

static String_t __Int_toString(int *ptr) {
  return String.format("%d", *ptr);
}

static int __Int_compare(int *ptr1, int *ptr2) {
  if (*ptr1 == *ptr2) return 0;
  return *ptr1 < *ptr2 ? -1 : 1;
}

$defineWrapper(Int);

static void __Double_destroy(double *ptr) {}

static String_t __Double_toString(double *ptr) {
  return String.format("%lf", *ptr);
}

static int __Double_compare(double *ptr1, double *ptr2) {
  if (*ptr1 == *ptr2) return 0;
  return *ptr1 < *ptr2 ? -1 : 1;
}

$defineWrapper(Double);

static void __CString_destroy(CString_t str) {}

void __Vector_insertSlice(Vector_t self, int i, Pointer_t slice, size_t size);

static String_t __CString_toString(CString_t cstr) {
  String_t str = String.create(0);
  __Vector_insertSlice(str, 0, cstr, strlen(cstr));
  return str;
}

static int __CString_compare(CString_t str1, CString_t str2) {
  return strcmp(str1, str2);
}

$defineWrapper(CString);

static void __Pair_destroy(Pair *ptr) {}

static String_t __Pair_toString(Pair *ptr) {
}

static int __Pair_compare(Pair *ptr1, Pair *ptr2) {
}

$defineWrapper(Pair);

static void __IntPair_destroy(IntPair *ptr) {}

static String_t __IntPair_toString(IntPair *ptr) {
  return String.format("(%d, %d)", ptr->first, ptr->second);
}

static int __IntPair_compare(IntPair *ptr1, IntPair *ptr2) {
  int ret = Int_w->compare(&ptr1->first, &ptr2->first);
  if (ret) return ret;
  return Int_w->compare(&ptr1->second, &ptr2->second);
}

$defineWrapper(IntPair);

static void __DoublePair_destroy(DoublePair *ptr) {}

static String_t __DoublePair_toString(DoublePair *ptr) {
  return String.format("(%lf, %lf)", ptr->first, ptr->second);
}

static int __DoublePair_compare(DoublePair *ptr1, DoublePair *ptr2) {
  int ret = Double_w->compare(&ptr1->first, &ptr2->first);
  if (ret) return ret;
  return Double_w->compare(&ptr1->second, &ptr2->second);
}

$defineWrapper(DoublePair);

static void __Triple_destroy(Triple *ptr) {}

static String_t __Triple_toString(Triple *ptr) {
}

static int __Triple_compare(Triple *ptr1, Triple *ptr2) {
}

$defineWrapper(Triple);
