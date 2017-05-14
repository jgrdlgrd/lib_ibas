//
// Created by Павел on 17.12.2016.
//

#include <locale.h>

#include "console.h"
#include "scanner.h"
#include "../base/base.h"

$defineNamespace(Colors) {
    "\033[0m",
    "\033[1;31m",
    "\033[1;32m"
};

void __Console_clearScreen() {
#ifdef __CYGWIN__
  system("clear");
#else
  system("cls");
#endif
}

void __Console_flush() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

void __Console_pause() {
#ifdef __CYGWIN__
  getchar();
#else
  system("pause");
#endif
}

CString_t __Console_setRusLocale() {
#ifdef __CYGWIN__
  return setlocale(LC_ALL, "ru_RU.utf8");
#else
  return setlocale(LC_ALL, "Russian");
#endif
}

void __Console_repeat(void (*fn)(int count), CString_t question) {
  int count = 0;
  do {
    fn(count++);
  } while (Console.prompt(question));
}

int __Console_showMenu(int count, CString_t labels[count]) {
  static CString_t prompt = "Выберите действие: ";
  static CString_t errorMessage = "Недопустимое действие!\n";

  printf(prompt);
  Console.newLine();

  for (int i = 0; i < count; i++) {
    printf("  %d - %s\n", i + 1, labels[i]);
  }
  Console.newLine();

  int option = Console.inputIntFromInterval(prompt, errorMessage, 1, count);
  return option;
}

bool __Console_prompt(CString_t question) {
  printf(question);
  bool ans = false;

  //@formatter:off
  $withObj(String_t, str) {
    str = Scanner.nextToken(Console.scanner);
  } use {
    if (str->size) {
      char ch = String.get(str, 0);
      if (ch == 'Y' || ch == 'y') ans = true;
      else if (ch == -48 && str->size > 1) {
        ch = String.get(str, 1);
        ans = ch == -67 || ch == -99;
      }
    }
  };
  //@formatter:off

  return ans;
}

void __Console_inputToken(CString_t format, Pointer_t dest, CString_t prompt, CString_t errorMessage) {
  while (true) {
    if (prompt) {
      printf(prompt);
    }

    //@formatter:off
    try {
      Scanner.nextFormat(Console.scanner, format, dest);
    } catch (FormatException) {
      if (errorMessage) printf(errorMessage);
      else rethrow("Console: invalid token and no errorMessage!");
    }
    //@formatter:on
  }
}

void __Console_inputAndValidateToken(CString_t format, Pointer_t dest, CString_t prompt, CString_t errorMessage, Validator validator, Object_t context) {
  while (true) {
    Console.inputToken(format, dest, prompt, errorMessage);
    //prompt = NULL;

    int err = validator(context, dest);

    if (!err || errorMessage == NULL) {
      return;
    }

    //printf(errorMessage);
  }
}

int __Console_inputInt(CString_t prompt, CString_t errorMessage) {
  int ret = 0;
  Console.inputToken("%d", &ret, prompt, errorMessage);
  return ret;
}

double __Console_inputDouble(CString_t prompt, CString_t errorMessage) {
  double ret = 0;
  Console.inputToken("%lf", &ret, prompt, errorMessage);
  return ret;
}

int __Console_intRangeValidator(Triple *ctx, int *val) {
  int min = *((int*) ctx->first), max = *((int*) ctx->second);

  if (*val >= min && *val <= max) {
    return 0;
  }

  printf((CString_t) ctx->third, min, max);
  return (*val < min) ? -1 : 1;
}

int __Console_inputIntFromInterval(CString_t prompt, CString_t errorMessage, int min, int max) {
  int ret;
  Triple ctx = {&min, &max, errorMessage};
  Console.inputAndValidateToken("%d", &ret, prompt, errorMessage, (Validator) __Console_intRangeValidator, &ctx);
  return ret;
}

int __Console_doubleRangeValidator(Triple *ctx, double *val) {
  double min = *((double*) ctx->first), max = *((double*) ctx->second);

  if (*val >= min && *val <= max) {
    return 0;
  }

  printf((CString_t) ctx->third, min, max);
  return (*val < min) ? -1 : 1;
}

double __Console_inputDoubleFromInterval(CString_t prompt, CString_t errorMessage, double min, double max) {
  double ret;
  Triple ctx = {&min, &max, errorMessage};
  Console.inputAndValidateToken("%lf", &ret, prompt, errorMessage, (Validator) __Console_doubleRangeValidator, &ctx);
  return ret;
}

void __Console_newLine() {
  putchar('\n');
}

void __Console_print(String_t str) {
  printf("%.*s", (int) str->size, (CString_t) str->storage);

  if (Console.autoDestroyStrings) String.destroy(str);
}

void __Console_println(String_t str) {
  Console.print(str);
  Console.newLine();
}

void __Console_CPrint(CString_t str) {
  fputs(str, stdout);
}

void __Console_CPrintln(CString_t str) {
  Console.CPrint(str);
  Console.newLine();
}

void __Console_printObj(Object_t obj) {
  bool tmp = Console.autoDestroyStrings;
  Console.autoDestroyStrings = true;

  Console.print(Object.toString(obj));

  Console.autoDestroyStrings = tmp;

  if (Console.autoDestroyObjects) Object.destroy(obj);
}

void __Console_format(CString_t format, ...) {
  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end (args);
}

void __Console_colored(CString_t color, CString_t format, ...) {
  va_list args;
  va_start(args, format);
  printf(color);
  vprintf(format, args);
  printf(Colors.RESET);
  va_end (args);
}

$defineNamespace(Console) {
    NULL,
    false,
    false,
    __Console_clearScreen,
    __Console_flush,
    __Console_pause,
    __Console_setRusLocale,
    __Console_repeat,
    __Console_showMenu,
    __Console_prompt,
    __Console_inputToken,
    __Console_inputAndValidateToken,
    __Console_inputInt,
    __Console_inputDouble,
    __Console_inputIntFromInterval,
    __Console_inputDoubleFromInterval,
    __Console_newLine,
    __Console_print,
    __Console_println,
    __Console_CPrint,
    __Console_CPrintln,
    __Console_printObj,
    __Console_format,
    __Console_colored
};
