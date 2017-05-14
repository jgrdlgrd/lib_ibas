//
// Created by Павел on 09.04.2017.
//

#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#include "e4c/e4c.h"

#include "base/macros.h"
#include "base/types.h"

E4C_DECLARE_EXCEPTION(NotImplementedException);
E4C_DECLARE_EXCEPTION(UnsupportedOperationException);
E4C_DECLARE_EXCEPTION(EOFException);
E4C_DECLARE_EXCEPTION(FormatException);
E4C_DECLARE_EXCEPTION(EmptyTokenException);

#define $ObjectMethods(name) \
    void (*destroy)(name##_t self); \
    String_t (*toString)(name##_t self); \
    int (*compare)(name##_t obj1, name##_t obj2)
