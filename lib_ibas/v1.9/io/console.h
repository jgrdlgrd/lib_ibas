//
// Created by Павел on 17.12.2016.
//

#ifndef LABS_CONSOLE_H
#define LABS_CONSOLE_H

#include "lib_ibas/v1.9/base.h"
#include "scanner.h"

typedef struct {
  void (*newLine)();
  void (*clearScreen)();
  void (*flush)();
  void (*pause)();
  String (*setRusLocale)();

  int (*repeat)(int (*)(), String);
  int (*showMenu)(int count, String labels[count]);
  bool (*prompt)(String question);

  int (*inputInt)(String prompt, String errorMessage);
  double (*inputDouble)(String prompt, String errorMessage);
  int (*inputIntFromInterval)(String prompt, String errorMessage, int min, int max);
  double (*inputDoubleFromInterval)(String prompt, String errorMessage, double min, double max);

  int (*coloured)(String colour, String format, ...);
} Console_t;
extern Console_t Console;

typedef struct {
  String RESET, RED, GREEN;
} Colors_t;
extern Colors_t Colors;

#endif
