//
// Created by Павел on 17.12.2016.
//

#pragma once

#include <stdarg.h>
#include <locale.h>
#include <errno.h>

#include "lib_ibas/v2.0/lib_ibas.h"
#include "scanner.h"

//TODO rewrite a few methods

declareClass(Console, {
  void (*newLine)();
  void (*clearScreen)();
  void (*flush)();
  void (*pause)();
  CString (*setRusLocale)();

  int (*repeat)(int (*)(), CString);
  int (*showMenu)(int count, CString labels[count]);
  bool (*prompt)(CString question);

  int (*inputInt)(CString prompt, CString errorMessage);
  double (*inputDouble)(CString prompt, CString errorMessage);
  int (*inputIntFromInterval)(CString prompt, CString errorMessage, int min, int max);
  double (*inputDoubleFromInterval)(CString prompt, CString errorMessage, double min, double max);

  int (*colored)(CString colour, CString format, ...);
})

//TODO add more colors
declareClass(Colors, {
  CString RESET;
  CString RED;
  CString GREEN;
})
