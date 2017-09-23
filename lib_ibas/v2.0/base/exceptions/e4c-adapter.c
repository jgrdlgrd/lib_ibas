//
// Created by Павел on 17.05.2017.
//

#ifdef USE_E4C

#include "e4c-adapter.h"

static void start() {
  e4c_context_begin(E4C_FALSE); //or handle SIGCHLD
}

static void finish() {
  e4c_context_end();
}

static ExceptionStatus_t getStatus() {
  return (ExceptionStatus_t) e4c_get_status();
}

$defineNamespace(Exception) {
  EXCEPTION_MESSAGE_SIZE,
  start,
  finish,
  getStatus
};

#endif
