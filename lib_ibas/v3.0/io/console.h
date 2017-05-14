//
// Created by Павел on 17.12.2016.
//

#pragma once

#include "../fwd.h"

//TODO rewrite a few methods

//TODO add more colors
$declareClass(Colors, {
  CString RESET;
  CString RED;
  CString GREEN;
});

$declareClass(Console, {
  Scanner_t scanner;
  bool autoDestroyStrings;
  bool autoDestroyObjects;

  void (*clearScreen)();
  void (*flush)();
  void (*pause)();
  CString (*setRusLocale)();

  int (*repeat)(int (*)(), CString);
  int (*showMenu)(int count, CString labels[count]);
  bool (*prompt)(CString question);

  void (*inputToken)(CString format, Pointer dest, CString prompt, CString errorMessage);
  void (*inputAndValidateToken)(CString format, Pointer dest, CString prompt, CString errorMessage, Validator validator, Object_t context);

  int (*inputInt)(CString prompt, CString errorMessage);
  double (*inputDouble)(CString prompt, CString errorMessage);
  int (*inputIntFromInterval)(CString prompt, CString errorMessage, int min, int max);
  double (*inputDoubleFromInterval)(CString prompt, CString errorMessage, double min, double max);

  void (*newLine)();
  void (*print)(String_t str);
  void (*printObj)(Object_t obj);
  int (*colored)(CString color, CString format, ...);
});
