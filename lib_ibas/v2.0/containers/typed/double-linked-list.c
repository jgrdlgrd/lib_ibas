//
// Created by Павел on 31.03.2017.
//

#include "double-linked-list.h"

String_t __DoubleLinkedList_toStringFn(Object ptr) {
  return String.fromDouble(*(double *) ptr);
}

genericLinkedListImplementation(DoubleLinkedList, double, __DoubleLinkedList_toStringFn);
