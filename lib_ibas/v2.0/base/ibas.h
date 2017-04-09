//
// Created by Павел on 19.12.2016.
//

#pragma once

#include "../fwd.h"

declareInterface(Object, {
  Object (*create)();
  void (*destroy)(Object obj);
  String_t (*toString)(Object obj);
});

//TODO optimize capabilities provided here
//TODO rethink method names
declareClass(Ibas, {
  void (*init)();
  void (*finish)();

  Pointer (*alloc)(size_t size, CString message);

  Object (*getClass)(Object obj);
  Object (*getImpl)(Object obj, CString interface);

  void (*destroy)(Object obj);
});
