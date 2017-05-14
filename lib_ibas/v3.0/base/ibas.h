//
// Created by Павел on 19.12.2016.
//

#pragma once

#include "../fwd.h"
#include "string.h"

//TODO optimize capabilities provided here
//TODO rethink method names

#define $class Ibas

#define $Ibas_static(_var, _fn) \
_fn(void, init) \
_fn(void, finish) \
_fn(Pointer, alloc, size_t size, CString message)

$declareStatic();
