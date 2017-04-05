//
// Created by Павел on 31.03.2017.
//

#include "int-linked-list.h"

String_t __IntLinkedList_toStringFn(Object ptr) {
  return String.fromInt(*(int *) ptr);
}

genericLinkedListImplementation(IntLinkedList, int, __IntLinkedList_toStringFn);
