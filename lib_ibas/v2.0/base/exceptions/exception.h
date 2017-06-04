//
// Created by Павел on 23.12.2016.
//

#pragma once

//#define USE_E4C

#include "../../fwd.h"

#define EXCEPTION_MESSAGE_SIZE 128

typedef enum {
  exc_beginning,
  exc_acquiring,
  exc_trying,
  exc_catching,
  exc_disposing,
  exc_finalizing,
  exc_done
} ExceptionStage_t;

typedef enum {
  exc_succeeded,
  exc_recovered,
  exc_failed
} ExceptionStatus_t;

$declareNamespace(Exception) {
  const unsigned MAX_MESSAGE_SIZE;

  void (*start)();
  void (*finish)();

  ExceptionStatus_t (*getStatus)();
};

#ifdef USE_E4C
#include "e4c-adapter.h"
#else

$declareType(Exception);
$declareType(ExceptionType);
#include "exc-impl.h"

#endif
