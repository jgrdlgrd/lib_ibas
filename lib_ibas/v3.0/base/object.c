//
// Created by Павел on 15.04.2017.
//

#include "object.h"
#include "ibas.h"

#define $class Object

$defineClass1(NULL)();

Pointer $static (getClass)(Object_t obj)(
    return *(Pointer *) obj;
)

//FIXME
Pointer $static (getImpl)(Object_t obj, CString interface)(
    Pointer *oPtr = Object.getClass(obj);
    CString *sPtr = (CString *) (oPtr + 1);

    while (*sPtr) {
      oPtr = (Pointer *) (sPtr + 1);
      if (*sPtr == interface || !strcmp(*sPtr, interface)) return *oPtr;

      sPtr = (CString *) (oPtr + 1);
    }

    throw(ClassCastException, NULL);
)

void $static (destroy)(Object_t obj)(
    if (obj) {
      $call(obj, destroy)();
    }
)

$defineStatic();

void $public (destroy)()(
  free(self);
)

String_t $public (toString)()(
  return String.format("");
)

$defineMethods();
