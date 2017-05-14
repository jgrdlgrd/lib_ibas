//
// Created by Павел on 21.03.2017.
//

#include "base.h"
#include "../io/console.h"
#include "../io/scanner.h"

E4C_DEFINE_EXCEPTION(UnsupportedOperationException, "Unsupported operation!", RuntimeException);
E4C_DEFINE_EXCEPTION(NotImplementedException, "The feature is not implemented yet!", UnsupportedOperationException);
E4C_DEFINE_EXCEPTION(EOFException, "Unexpected end of file!", RuntimeException);
E4C_DEFINE_EXCEPTION(FormatException, "Invalid format!", RuntimeException);

void __Ibas_init() {
  e4c_context_begin(E4C_FALSE);
  Console.scanner = Scanner.fromStream(stdin);
}

void __Ibas_finish() {
  e4c_context_end();
}

Pointer_t __Ibas_alloc(size_t size, CString_t message) {
  if (!message) message = "Could not allocate memory";
  Pointer_t ptr = malloc(size);
  if (!ptr) throw(NotEnoughMemoryException, message);
  return ptr;
}

$defineNamespace(Ibas) {
    __Ibas_init,
    __Ibas_finish,
    __Ibas_alloc
};
