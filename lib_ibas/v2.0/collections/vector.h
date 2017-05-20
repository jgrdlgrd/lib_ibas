//
// Created by Павел on 16.03.2017.
//

#pragma once

#include "../fwd.h"
#include "list.h"

#define VECTOR_GROWTH_FACTOR 1.5

$defineType(Vector) {
  Class_t class;
  size_t size, elemSize, capacity;
  Pointer_t storage;
  bool primitive;
  Class_t elemClass;
};

$declareNamespace(Vector) {
  Class_t class;
  
  Vector_t (*create)(size_t capacity);
  Vector_t (*createPrimitive)(size_t capacity, size_t elemSize, Class_t elemClass);

  $ObjectMethods(Vector);
  
  $ListMethods(Vector, Pointer_t);

  void (*ensureCapacity)(Vector_t self, size_t capacity);
  void (*sort)(Vector_t self, Compare_t comparator);
};
