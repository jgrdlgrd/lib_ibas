//
// Created by Павел on 21.03.2017.
//

#include "base.h"
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

Ibas_c Ibas = {
    __Ibas_init,
    __Ibas_finish,
    __Ibas_alloc
};
