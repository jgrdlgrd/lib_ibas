//
// Created by Павел on 21.03.2017.
//

#include "ibas.h"
#include "../io/console.h"
#include "../io/scanner.h"

#define $class Ibas

E4C_DEFINE_EXCEPTION(EOFException, "Unexpected end of file!", RuntimeException);
E4C_DEFINE_EXCEPTION(FormatException, "Invalid format!", RuntimeException);
E4C_DEFINE_EXCEPTION(ClassCastException, "Supplied object doesn't implement requested interface!", RuntimeException);

void $static (init)()(
    e4c_context_begin(E4C_TRUE);
    Console.scanner = Scanner.fromStream(stdin);
)

void $static (finish)()(
    e4c_context_end();
)

Pointer $static (alloc)(size_t size, CString message)(
    if (!message) message = "Could not allocate memory";
    Pointer ptr = malloc(size);
    if (!ptr) throw(NotEnoughMemoryException, message);
    return ptr;
)

$defineStatic();
