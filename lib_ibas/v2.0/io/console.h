//
// Created by Павел on 17.12.2016.
//

#pragma once

#include "../fwd.h"

//TODO rewrite a few methods

//TODO add more colors
$declareNamespace(Colors) {
  CString_t RESET;
  CString_t RED;
  CString_t GREEN;
};

$declareNamespace(Console) {
  Scanner_t scanner;
  bool autoDestroyStrings;
  bool autoDestroyObjects;

  void (*clearScreen)();
  void (*flush)();
  void (*pause)();
  CString_t (*setRusLocale)();

  void (*repeat)(void (*fn)(int count), CString_t question);
  int (*showMenu)(int count, CString_t labels[count]);
  bool (*prompt)(CString_t question);

  void (*inputToken)(CString_t format, Pointer_t dest, CString_t prompt, CString_t errorMessage);
  void (*inputAndValidateToken)(CString_t format, Pointer_t dest, CString_t prompt, CString_t errorMessage, Validator validator, Object_t context);

  int (*inputInt)(CString_t prompt, CString_t errorMessage);
  double (*inputDouble)(CString_t prompt, CString_t errorMessage);
  int (*inputIntFromInterval)(CString_t prompt, CString_t errorMessage, int min, int max);
  double (*inputDoubleFromInterval)(CString_t prompt, CString_t errorMessage, double min, double max);

  void (*newLine)();
  void (*print)(String_t str);
  void (*println)(String_t str);
  void (*CPrint)(CString_t str);
  void (*CPrintln)(CString_t str);
  void (*printObj)(Object_t obj);
  void (*format)(CString_t format, ...);
  void (*colored)(CString_t color, CString_t format, ...);
};
