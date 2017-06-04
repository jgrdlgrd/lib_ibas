//
// Created by Павел on 14.05.2017.
//

#include "wrappers.h"
#include "base.h"
#include "../io/writer.h"
#include "../io/scanner.h"

//TODO implement

static void noop_destroy(Pointer_t ptr) {}

static String_t noop_toString(Pointer_t ptr) {
  $throw(NotImplementedException, "");
  return NULL;
}

static int noop_compare(Pointer_t ptr1, Pointer_t ptr2) {
  $throw(NotImplementedException, "");
  return 0;
}

// ------

static String_t Int_toString(int *ptr) {
  return String.format("%d", *ptr);
}

static int Int_compare(int *ptr1, int *ptr2) {
  if (*ptr1 == *ptr2) return 0;
  return *ptr1 < *ptr2 ? -1 : 1;
}

static void Int_serialize(int *ptr, Writer_t writer) {
  Writer.format(writer, "%d", *ptr);
}

static int *Int_deserialize(int *ptr, Scanner_t scanner) {
  if (!ptr) $throw(UnsupportedOperationException, "");

  CString_t tmp = scanner->delimiters;
  scanner->delimiters = " ,}\n\t";

  Scanner.nextFormat(scanner, "%d", ptr);
  scanner->delimiters = tmp;
  return ptr;
}

$defineWrapper(Int) {
    (Destroy_t) noop_destroy,
    (ToString_t) Int_toString,
    (Compare_t) Int_compare,
    (Serialize_t) Int_serialize,
    (Deserialize_t) Int_deserialize
};

static String_t Double_toString(double *ptr) {
  return String.format("%lf", *ptr);
}

static int Double_compare(double *ptr1, double *ptr2) {
  if (*ptr1 == *ptr2) return 0;
  return *ptr1 < *ptr2 ? -1 : 1;
}

$defineWrapper(Double) {
    (Destroy_t) noop_destroy,
    (ToString_t) Double_toString,
    (Compare_t) Double_compare
};

void __Vector_insertSlice(Vector_t self, int i, Pointer_t slice, size_t size);

static String_t CString_toString(CString_t cstr) {
  String_t str = String.create(0);
  __Vector_insertSlice(str, 0, cstr, strlen(cstr));
  return str;
}

static int CString_compare(CString_t str1, CString_t str2) {
  return strcmp(str1, str2);
}

$defineWrapper(CString) {
    (Destroy_t) noop_destroy,
    (ToString_t) CString_toString,
    (Compare_t) CString_compare
};

static void File_destroy(FILE **ptr) {
  fclose(*ptr);
}

$defineWrapper(File) {
    (Destroy_t) File_destroy,
    (ToString_t) noop_toString,
    (Compare_t) noop_compare
};

static void Pair_destroy(Pair *ptr) {}

static String_t Pair_toString(Pair *ptr) {
}

static int Pair_compare(Pair *ptr1, Pair *ptr2) {
}

$defineWrapper(Pair) {
    (Destroy_t) Pair_destroy,
    (ToString_t) Double_toString,
    (Compare_t) Double_compare
};

static void __IntPair_destroy(IntPair *ptr) {}

static String_t __IntPair_toString(IntPair *ptr) {
  return String.format("(%d, %d)", ptr->first, ptr->second);
}

static int __IntPair_compare(IntPair *ptr1, IntPair *ptr2) {
  int ret = Int_w.compare(&ptr1->first, &ptr2->first);
  if (ret) return ret;
  return Int_w.compare(&ptr1->second, &ptr2->second);
}

$defineWrapper(IntPair) {
    (Destroy_t) Pair_destroy,
    (ToString_t) Double_toString,
    (Compare_t) Double_compare
};

static void __DoublePair_destroy(DoublePair *ptr) {}

static String_t __DoublePair_toString(DoublePair *ptr) {
  return String.format("(%lf, %lf)", ptr->first, ptr->second);
}

static int __DoublePair_compare(DoublePair *ptr1, DoublePair *ptr2) {
  int ret = Double_w.compare(&ptr1->first, &ptr2->first);
  if (ret) return ret;
  return Double_w.compare(&ptr1->second, &ptr2->second);
}

$defineWrapper(DoublePair) {
    (Destroy_t) Pair_destroy,
    (ToString_t) Double_toString,
    (Compare_t) Double_compare
};

static void __Triple_destroy(Triple *ptr) {}

static String_t __Triple_toString(Triple *ptr) {
}

static int __Triple_compare(Triple *ptr1, Triple *ptr2) {
}

$defineWrapper(Triple) {
    (Destroy_t) Pair_destroy,
    (ToString_t) Double_toString,
    (Compare_t) Double_compare
};
