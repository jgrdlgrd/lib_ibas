//
// Created by Павел on 20.05.2017.
//

#include "exc-impl.h"

#ifndef USE_E4C

#include <errno.h>
#include "../../io/console.h"

$declareType(ExceptionFrame);
$defineType(ExceptionFrame) {
  ExceptionFrame_t previous;
  ExceptionStage_t stage;
  bool uncaught, acquired;
  Exception_t thrownException;
  jmp_buf continuation;
};

static ExceptionFrame_t curFrame = NULL;

static jmp_buf *createFrame(ExceptionStage_t stage) {
  ExceptionFrame_t frame = calloc(1, sizeof(ExceptionFrame_s));
  //TODO check

  frame->previous = curFrame;
  frame->stage = stage;
  frame->uncaught = frame->acquired = false;
  frame->thrownException = NULL;

  curFrame = frame;

  return &frame->continuation;
}

static void destroyFrame(ExceptionFrame_t frame) {
  if (frame) {
    destroyFrame(frame->previous);
    frame->previous = NULL;

    free(frame->thrownException);
    frame->thrownException = NULL;

    free(frame);
  }
}

static int printTypeNode(ExceptionType_t type) {
  int depth = -1;

  if (type->supertype == NULL || type->supertype == type) {
    fprintf(stderr, "    %s\n", type->name);
  } else {
    depth = printTypeNode(type->supertype);
    fprintf(stderr, "    %*s |\n    %*s +--%s\n", depth * 4, "", depth * 4, "", type->name);
  }

  return depth + 1;
}

static void printExcType(ExceptionType_t type) {
  CString_t separator = "________________________________________________________________";

  fprintf(stderr, "Exception hierarchy\n%s\n\n", separator);

  printTypeNode(type);

  fprintf(stderr, "%s\n", separator);
  fflush(stderr);
}

static void printExc(Exception_t exception) {
  fprintf(stderr, "\n\nUncaught %s: %s\n\n", exception->name, exception->message);

  if (exception->file) {
    if (exception->function) {
      fprintf(stderr, "    thrown at %s (%s:%d)\n\n", exception->function, exception->file, exception->line);
    } else {
      fprintf(stderr, "    thrown at %s:%d\n\n", exception->file, exception->line);
    }
  }

  fprintf(stderr, "The value of errno was %d.\n\n", exception->errorNumber);

  if (exception->type) {
    printExcType(exception->type);
  }

  fflush(stderr);
}

static void processUncaught(Exception_t exception) {
  //TODO implement custom
  printExc(exception);
  Console.pause(NULL);
}

static bool isInstanceOf(Exception_t instance, ExceptionType_t type) {
  if (instance == NULL || instance->type == NULL || type == NULL) {
    return false;
  }

  if (instance->type == type) {
    return true;
  }

  ExceptionType_t parent = instance->type;
  for (; parent->supertype != NULL && parent->supertype != parent; parent = parent->supertype) {
    if (parent->supertype == type) return true;
  }

  return false;
}

static bool tryToCatch(ExceptionType_t type) {
  if (curFrame->stage != exc_catching) {
    return false;
  }

  if (isInstanceOf(curFrame->thrownException, type)) {
    curFrame->uncaught = false;
    return true;
  }

  return false;
}

static void propagateExc() {
  if (curFrame->previous == NULL) {
    processUncaught(curFrame->thrownException);
    Exception.finish();
    exit(-1);
  }

  if (curFrame->stage == exc_acquiring) {
    curFrame->stage = exc_trying;
  }

  longjmp(curFrame->continuation, 1);
}

static void throwExc(ExceptionType_t type, CString_t file, int line, CString_t function, CString_t message) {
  int error = errno;

  Exception_t exception = calloc(1, sizeof(Exception_s));
  exception->name = type->name;
  exception->file = file;
  exception->line = line;
  exception->function = function;
  exception->errorNumber = error;
  exception->type = type;

  snprintf(exception->message, EXCEPTION_MESSAGE_SIZE, "%s", message ? message : type->default_message);

  curFrame->uncaught = true;
  free(curFrame->thrownException);
  curFrame->thrownException = exception;

  propagateExc();
}

static void rethrow(CString_t message) {
  if (message && curFrame->thrownException)
    snprintf(curFrame->thrownException->message, EXCEPTION_MESSAGE_SIZE, "%s", message);
  curFrame->uncaught = true;
  propagateExc();
}

static bool nextStage() {
  curFrame->stage++;

  if (curFrame->stage == exc_catching && !curFrame->uncaught) {
    curFrame->stage++;
  }

  if (curFrame->stage == exc_disposing && !curFrame->acquired) {
    curFrame->stage++;
  }

  if (curFrame->stage < exc_done) {
    return true;
  }

  if (curFrame->thrownException != NULL && !curFrame->uncaught) {
    free(curFrame->thrownException);
    curFrame->thrownException = NULL;
  }

  ExceptionFrame_t previous = curFrame->previous;
  curFrame->previous = NULL;
  Exception_t thrown = curFrame->thrownException;
  curFrame->thrownException = NULL;

  destroyFrame(curFrame);
  curFrame = previous;

  if (thrown != NULL) {
    curFrame->uncaught = true;
    free(curFrame->thrownException);
    curFrame->thrownException = thrown;
    propagateExc();
  }

  return false;
}

static ExceptionStage_t currentStage() {
  return curFrame->stage;
}

static void start() {
  createFrame(exc_done);
}

static void finish() {
  destroyFrame(curFrame);
}

static ExceptionStatus_t getStatus() {
  if (curFrame->thrownException == NULL) {
    return exc_succeeded;
  }

  if (curFrame->uncaught) {
    return exc_failed;
  }

  return exc_recovered;
}

static bool setAcquired() {
  return (curFrame->acquired = true);
}

$defineNamespace(Exception) {
    EXCEPTION_MESSAGE_SIZE,
    start,
    finish,
    getStatus
};

$defineNamespace(ExceptionInternals) {
    currentStage,
    createFrame,
    tryToCatch,
    nextStage,
    throwExc,
    rethrow,
    setAcquired
};

$defineException(AssertionException, "Assertion failed.", AssertionException);
$defineException(RuntimeException, "Runtime exception.", RuntimeException);
$defineException(NotEnoughMemoryException, "Not enough memory.", RuntimeException);
$defineException(InputOutputException, "Input/output exception.", RuntimeException);
$defineException(IllegalArgumentException, "Illegal argument.", RuntimeException);
$defineException(NullPointerException, "Null pointer.", RuntimeException);

#endif
