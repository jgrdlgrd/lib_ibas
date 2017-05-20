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

static void clearScreen() {
#ifdef __CYGWIN__
  system("clear");
#else
  system("cls");
#endif
}

static void flush() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

static void pause() {
#ifdef __CYGWIN__
  getchar();
#else
  system("pause");
#endif
}

static CString_t setRusLocale() {
#ifdef __CYGWIN__
  return setlocale(LC_ALL, "ru_RU.utf8");
#else
  return setlocale(LC_ALL, "Russian");
#endif
}

static void repeat(void (*fn)(int count), CString_t question) {
  int count = 0;
  do {
    fn(count++);
  } while (Console.prompt(question));
}

static int showMenu(int count, CString_t labels[count]) {
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

static bool prompt(CString_t question) {
  printf(question);
  bool ans = false;

  //@formatter:off
  $withAuto(String_t, str) {
    str = Scanner.nextToken(Console.scanner);
  } $use {
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

static void inputToken(CString_t format, Pointer_t dest, CString_t prompt, CString_t errorMessage) {
  bool good = false;

  while (true) {
    if (prompt) {
      printf(prompt);
    }

    //@formatter:off
    $try {
      Scanner.nextFormat(Console.scanner, format, dest);
      good = true;
    } $catch (FormatException) {
      if (errorMessage) printf(errorMessage);
      else $throw(FormatException, "Console: invalid token and no errorMessage!");
    }
    //@formatter:on

    if (good) break;
  }
}

static void inputAndValidateToken(CString_t format, Pointer_t dest, CString_t prompt, CString_t errorMessage, Validator validator, Object_t context) {
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

static int inputInt(CString_t prompt, CString_t errorMessage) {
  int ret = 0;
  Console.inputToken("%d", &ret, prompt, errorMessage);
  return ret;
}

static double inputDouble(CString_t prompt, CString_t errorMessage) {
  double ret = 0;
  Console.inputToken("%lf", &ret, prompt, errorMessage);
  return ret;
}

static int intRangeValidator(Triple *ctx, int *val) {
  int min = *((int*) ctx->first), max = *((int*) ctx->second);

  if (*val >= min && *val <= max) {
    return 0;
  }

  printf((CString_t) ctx->third, min, max);
  return (*val < min) ? -1 : 1;
}

static int inputIntFromInterval(CString_t prompt, CString_t errorMessage, int min, int max) {
  int ret;
  Triple ctx = {&min, &max, errorMessage};
  Console.inputAndValidateToken("%d", &ret, prompt, errorMessage, (Validator) intRangeValidator, &ctx);
  return ret;
}

static int doubleRangeValidator(Triple *ctx, double *val) {
  double min = *((double*) ctx->first), max = *((double*) ctx->second);

  if (*val >= min && *val <= max) {
    return 0;
  }

  printf((CString_t) ctx->third, min, max);
  return (*val < min) ? -1 : 1;
}

static double inputDoubleFromInterval(CString_t prompt, CString_t errorMessage, double min, double max) {
  double ret;
  Triple ctx = {&min, &max, errorMessage};
  Console.inputAndValidateToken("%lf", &ret, prompt, errorMessage, (Validator) doubleRangeValidator, &ctx);
  return ret;
}

static void newLine() {
  putchar('\n');
}

static void print(String_t str) {
  printf("%.*s", (int) str->size, (CString_t) str->storage);

  if (Console.autoDestroyStrings) String.destroy(str);
}

static void println(String_t str) {
  Console.print(str);
  Console.newLine();
}

static void CPrint(CString_t str) {
  fputs(str, stdout);
}

static void CPrintln(CString_t str) {
  Console.CPrint(str);
  Console.newLine();
}

static void printObj(Object_t obj) {
  bool tmp = Console.autoDestroyStrings;
  Console.autoDestroyStrings = true;

  Console.print(Object.toString(obj));

  Console.autoDestroyStrings = tmp;

  if (Console.autoDestroyObjects) Object.destroy(obj);
}

static void format(CString_t format, ...) {
  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end (args);
}

static void colored(CString_t color, CString_t format, ...) {
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
    clearScreen,
    flush,
    pause,
    setRusLocale,
    repeat,
    showMenu,
    prompt,
    inputToken,
    inputAndValidateToken,
    inputInt,
    inputDouble,
    inputIntFromInterval,
    inputDoubleFromInterval,
    newLine,
    print,
    println,
    CPrint,
    CPrintln,
    printObj,
    format,
    colored
};
