//
// Created by Павел on 07.04.2017.
//

#include "to-string.h"
#include "ibas.h"

#define $class ToString

String_t $static (Object)(Object_t obj)(
  return $call(obj, toString)();
)

//FIXME
String_t $static (CStr)(CString cstr)(
  String_t str = String.create(0);
  __Vector_insertSlice(str, 0, cstr, strlen(cstr));
  return str;
)

String_t $static (Int)(int val)(
  return String.format("%d", val);
)

String_t $static (IntPtr)(int *val)(
  return ToString.Int(*val);
)

String_t $static (Double)(double val)(
  return String.format("%lf", val);
)

String_t $static (DoublePtr)(double *val)(
  return ToString.Double(*val);
)

String_t $static (IntPair)(IntPair val)(
  return String.format("(%d, %d)", val.first, val.second);
)

String_t $static (IntPairPtr)(IntPair *val)(
  return ToString.IntPair(*val);
)

String_t $static (DoublePair)(DoublePair val)(
  return String.format("(%lf, %lf)", val.first, val.second);
)

String_t $static (DoublePairPtr)(DoublePair *val)(
  return ToString.DoublePair(*val);
)

$defineStatic(
    $ns(Object),
    $ns(CStr),
    $ns(Int),
    $ns(IntPtr),
    $ns(Double),
    $ns(DoublePtr),
    $ns(IntPair),
    $ns(IntPairPtr),
    $ns(DoublePair),
    $ns(DoublePairPtr)
);
