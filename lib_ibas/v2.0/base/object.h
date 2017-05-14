//
// Created by Павел on 14.05.2017.
//

#pragma once

#include "../fwd.h"

$declareNamespace(Object) {
  Class_t class;
  
  $ObjectMethods(Object);

  Class_t (*getClass)(Object_t obj);
};
