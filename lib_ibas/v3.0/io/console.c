//
// Created by Павел on 17.12.2016.
//

#include <locale.h>
#include <errno.h>

#include "console.h"
#include "scanner.h"
#include "../base/ibas.h"
#include "../base/string.h"

Colors_c Colors = {
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
  //getchar();
#else
  system("pause");
#endif
}

CString __Console_setRusLocale() {
#ifdef __CYGWIN__
  return setlocale(LC_ALL, "ru_RU.utf8");
#else
  return setlocale(LC_ALL, "Russian");
#endif
}

int __Console_repeat(int (*f)(), CString question) {
  int err = 0;
  do {
    err = f();
  } while (!err && Console.prompt(question));
  return err;
}

int __Console_showMenu(int count, CString labels[count]) {
  static CString prompt = "Выберите действие: ";
  static CString errorMessage = "Недопустимое действие!\n";

  printf(prompt);
  Console.newLine();

  for (int i = 0; i < count; i++) {
    printf("  %d - %s\n", i + 1, labels[i]);
  }
  Console.newLine();

  errno = 0;
  int option = Console.inputIntFromInterval(prompt, errorMessage, 1, count);
  if (errno) {
    errno = 0;
    return -abs(errno);
  }
  return option;
}

bool __Console_prompt(CString question) {
  printf(question);
  bool ans = false;

  //@formatter:off
  withObj(String_t, str) {
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

void __Console_inputToken(CString format, Pointer dest, CString prompt, CString errorMessage) {
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

void __Console_inputAndValidateToken(CString format, Pointer dest, CString prompt, CString errorMessage, Validator validator, Object_t context) {
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

int __Console_inputInt(CString prompt, CString errorMessage) {
  int ret = 0;
  Console.inputToken("%d", &ret, prompt, errorMessage);
  return ret;
}

double __Console_inputDouble(CString prompt, CString errorMessage) {
  double ret = 0;
  Console.inputToken("%lf", &ret, prompt, errorMessage);
  return ret;
}

int __Console_intRangeValidator(Triple *ctx, int *val) {
  int min = *((int*) ctx->first), max = *((int*) ctx->second);

  if (*val >= min && *val <= max) {
    return 0;
  }

  printf((CString) ctx->third, min, max);
  return (*val < min) ? -1 : 1;
}

int __Console_inputIntFromInterval(CString prompt, CString errorMessage, int min, int max) {
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

  printf((CString) ctx->third, min, max);
  return (*val < min) ? -1 : 1;
}

double __Console_inputDoubleFromInterval(CString prompt, CString errorMessage, double min, double max) {
  double ret;
  Triple ctx = {&min, &max, errorMessage};
  Console.inputAndValidateToken("%lf", &ret, prompt, errorMessage, (Validator) __Console_doubleRangeValidator, &ctx);
  return ret;
}

void __Console_newLine() {
  putchar('\n');
}

void __Console_print(String_t str) {
  printf("%.*s", (int) str->size, (CString) str->storage);

  if (Console.autoDestroyStrings) String.destroy(str);
}

void __Console_printObj(Object_t obj) {
  bool tmp = Console.autoDestroyStrings;
  Console.autoDestroyStrings = true;

  Console.print(ToString.Object(obj)); //TODO WTF??

  Console.autoDestroyStrings = tmp;

  if (Console.autoDestroyObjects) Ibas.destroy(obj);
}

int __Console_colored(CString color, CString format, ...) {
  va_list args;
  va_start (args, format);
  printf(color);
  int ret = vprintf (format, args);
  printf(Colors.RESET);
  va_end (args);
  return ret;
}

Console_c Console = {
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
    __Console_printObj,
    __Console_colored
};
