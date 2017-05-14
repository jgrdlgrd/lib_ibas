//
// Created by Павел on 19.03.2017.
//

#pragma once

#include "../fwd.h"
#include "list.h"

$defineType(LinkedList) {
  Class_t class;
  size_t elemSize, size;
  Pointer_t head, tail;
  bool primitive;
  Class_t elemClass;
};

$declareNamespace(LinkedList) {
  Class_t class;
  
  LinkedList_t (*create)();
  LinkedList_t (*createPrimitive)(size_t elemSize, Class_t elemClass);

  $ObjectMethods(LinkedList);

  $ListMethods(LinkedList, Pointer_t);

  void (*sort)(LinkedList_t self, Compare_t comparator);
  String_t (*toPrettyString)(LinkedList_t self);
};
