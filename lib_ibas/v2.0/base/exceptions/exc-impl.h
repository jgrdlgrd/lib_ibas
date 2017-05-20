//
// Created by Павел on 20.05.2017.
//

#pragma once

#include "lib_ibas/v2.0/fwd.h"

#ifndef USE_E4C

#include <setjmp.h>

$defineType(Exception) {
  CString_t name;
  char message[EXCEPTION_MESSAGE_SIZE];
  CString_t file;
  int line;
  CString_t function;
  int errorNumber;
  ExceptionType_t type;
};

$defineType(ExceptionType) {
  CString_t name;
  char default_message[EXCEPTION_MESSAGE_SIZE];
  ExceptionType_t supertype;
};

$declareNamespace(ExceptionInternals) {
  ExceptionStage_t (*currentStage)();
  jmp_buf* (*createFrame)(ExceptionStage_t stage);
  bool (*tryToCatch)(ExceptionType_t exception_type);
  bool (*nextStage)();
  void (*throwException)(ExceptionType_t type, CString_t file, int line, CString_t function, CString_t message);
};

#define $assert(condition) \
    ((condition) ? (void) 0 : $throw(AssertionException, "Assertion failed: " #condition))

#define $try \
  if (setjmp(*ExceptionInternals.createFrame(exc_acquiring)) >= 0) \
    while (ExceptionInternals.nextStage()) \
      if (ExceptionInternals.currentStage() == exc_trying && ExceptionInternals.nextStage())

#define $catch(exception_type) \
  else if (ExceptionInternals.tryToCatch(&exception_type))

#define $finally \
  else if (ExceptionInternals.currentStage() == exc_finalizing)

#define $throw(exception_type, message) \
  ExceptionInternals.throwException(&exception_type, __FILE__, __LINE__, (CString_t) __func__, message)

#define $with(resource) \
  if (setjmp(*ExceptionInternals.createFrame(exc_beginning)) >= 0) \
    while (ExceptionInternals.nextStage()) \
      if(ExceptionInternals.currentStage() == exc_disposing && Exception.getStatus() == exc_failed) { \
        Object.destroy(resource); \
      } else if (ExceptionInternals.currentStage() == exc_acquiring) {

#define $withAuto(type, resource) \
  for (bool flag = true; flag; ) \
    for (type resource = NULL; flag; flag = false) \
      if (setjmp(*ExceptionInternals.createFrame(exc_beginning)) >= 0) \
        while (ExceptionInternals.nextStage()) \
          if (ExceptionInternals.currentStage() == exc_disposing) { \
            Object.destroy(resource); \
          } else if (ExceptionInternals.currentStage() == exc_acquiring) {

#define $use \
  } else if (ExceptionInternals.currentStage() == exc_trying)

#define $declareException(name) extern ExceptionType_s name

#define $defineException(name, defaultMessage, supertype) \
  ExceptionType_s name = { \
    #name, \
    defaultMessage, \
    &supertype \
  }

#include "exc-def.h"

#endif
