//
// Created by Павел on 19.03.2017.
//

#pragma once

#include "lib_ibas/v2.0/lib_ibas.h"
#include "generic-list.h"

declareFields(LinkedList, {
  size_t elemSize;
  int size;
  void *head;
})

declareClass(LinkedList, {
  genericListMethodsDecl(LinkedList_t, list, Object)
})
