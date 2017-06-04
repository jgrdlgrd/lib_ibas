//
// Created by Павел on 21.05.2017.
//

#pragma once

#include "lib_ibas/v2.0/fwd.h"

$declareInterface(RecordHandler) {
  $ObjectMethods(Object);

  Object_t (*input)();
  void (*edit)(Object_t record);
  LinkedList_t (*process)(LinkedList_t records);
  bool (*sort)();
};

$declareNamespace(RecordProcessor) {
  void (*start)(RecordHandler_i handler);
  void (*finish)();
};
