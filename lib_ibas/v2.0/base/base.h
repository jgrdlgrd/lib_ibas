//
// Created by Павел on 19.12.2016.
//

#pragma once

#include "../fwd.h"
#include "object.h"
#include "wrappers.h"
#include "string.h"

$defineType(Class) {
  $ObjectMethods(Object);
};

//TODO optimize capabilities provided here
//TODO rethink method names
$declareNamespace(Ibas) {
  void (*init)();
  void (*finish)();

  Pointer_t (*alloc)(size_t size, CString_t message);
};
