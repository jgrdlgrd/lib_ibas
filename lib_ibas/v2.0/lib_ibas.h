//
// Created by Павел on 20.03.2017.
//

#pragma once

//TODO put const modifier where necessary
//TODO document everything :D
//TODO test everything :D

#include "lib_ibas/v2.0/base/base.h"
#include "lib_ibas/v2.0/base/string.h"
#include "lib_ibas/v2.0/io/console.h"

//TODO optimize capabilities provided here
//TODO rethink method names
declareClass(Ibas, {
  void (*init)();
  void (*finish)();

  Object (*alloc)(size_t size, CString message);
})