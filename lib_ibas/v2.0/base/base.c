//
// Created by Павел on 21.03.2017.
//

#include "base.h"
#include "../io/console.h"
#include "../io/scanner.h"

static void start() {
  Exception.start();
  Console.scanner = Scanner.fromStream(stdin);
}

static void finish() {
  Exception.finish();
}

static Pointer_t alloc(size_t size, CString_t message) {
  if (!message) message = "Could not allocate memory";
  Pointer_t ptr = malloc(size);
  if (!ptr) $throw(NotEnoughMemoryException, message);
  return ptr;
}

$defineNamespace(Ibas) {
    start,
    finish,
    alloc
};
