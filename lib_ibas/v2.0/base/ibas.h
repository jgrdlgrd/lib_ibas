//
// Created by Павел on 19.12.2016.
//

#pragma once

#include "../fwd.h"

//TODO optimize capabilities provided here
//TODO rethink method names
declareClass(Ibas, {
  void (*init)();
  void (*finish)();

  Pointer (*alloc)(size_t size, CString message);

  Object (*getClass)(Object obj);
  Object (*getImpl)(Object obj, CString interface);
});
