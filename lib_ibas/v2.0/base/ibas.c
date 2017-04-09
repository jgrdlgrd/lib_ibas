//
// Created by Павел on 21.03.2017.
//

#include "ibas.h"
#include "../io/scanner.h"

void __Ibas_init() {
  e4c_context_begin(E4C_TRUE);
  Scanner.stream = stdin;
}

void __Ibas_finish() {
  e4c_context_end();
}

Object __Ibas_alloc(size_t size, CString message) {
  if (!message) message = "Could not allocate memory";
  Object ptr = malloc(size);
  if (!ptr) throw(NotEnoughMemoryException, message);
  return ptr;
}

Object __Ibas_getClass(Object obj) {
  return *(Object *) obj;
}

Object __Ibas_getImpl(Object obj, CString interface) {
  Object class = Ibas.getClass(obj);
  if (interface == 0) return class; //"Object" should be always at the beginning

  CString *sPtr = class;
  Object *oPtr;
  while(*sPtr) {
    oPtr = (Object *) (sPtr + 1);
    if (*sPtr == interface || !strcmp(*sPtr, interface)) return *oPtr;

    sPtr = (CString *) (oPtr + 1);
  }

  return NULL;
}

Ibas_c Ibas = {
    __Ibas_init,
    __Ibas_finish,
    __Ibas_alloc,
    __Ibas_getClass,
    __Ibas_getImpl,
};
