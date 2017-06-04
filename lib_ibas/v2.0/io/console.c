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
#ifdef __unix__
  system("clear");
#else
  system("cls");
#endif
}

static void pause(CString_t message) {
#ifdef __unix__
  if (!message) message = "Для продолжения нажмите любую клавишу...";
  Console.CPrint(message);
  fflush(stdout);
  system("read");
  //Scanner.skipLine(Console.scanner);
#else
  system("pause");
#endif
}

static CString_t setRusLocale() {
#ifdef __unix__
  return setlocale(LC_ALL, "ru_RU.utf8");
#else
  return setlocale(LC_ALL, "Russian");
#endif
}

static void repeat(void (*fn)(int count), CString_t question, bool defaultAnswer) {
  int count = 0;
  do {
    fn(count++);
  } while (Console.confirm(question, defaultAnswer));
}

static int showMenu(CString_t prompt, int count, CString_t labels[count], Callable actions[count]) {
  static CString_t prompt_ = "Выберите действие: ";
  static CString_t errorMessage = "Недопустимое действие!\n";

  if (!prompt) prompt = prompt_;
  Console.CPrintln(prompt);
  for (int i = 0; i < count; i++) {
    Console.format("  %d - %s\n", i + 1, labels[i]);
  }
  Console.newLine();

  int option = Console.inputIntFromInterval(prompt, errorMessage, 1, count);
  if (actions && actions[option - 1]) actions[option - 1]();
  return option;
}

//TODO make it encoding-independent
static bool confirm(CString_t question, bool defaultAnswer) {
  Console.CPrint(question);
  bool ans = defaultAnswer;

  Scanner.skipSpace(Console.scanner);
  char ch = Scanner.nextChar(Console.scanner);
  if (ch == 'Y' || ch == 'y')
    ans = true;
  else if (ch == 'N' || ch == 'n')
    ans = false;
  else if (ch == (char) 208) {
    ch = Scanner.nextChar(Console.scanner);
    if (ch == (char) 189 || ch == (char) 157)
      ans = true;
    else if (ch == (char) 130 || ch == (char) 162)
      ans = false;
  }
  if (ch != '\n') Scanner.skipLine(Console.scanner);

  return ans;
}

static String_t prompt(CString_t question) {
  Console.CPrint(question);
  return Scanner.nextLine(Console.scanner);
}

static void inputToken(CString_t format, Pointer_t dest, CString_t prompt, CString_t errorMessage) {
  bool good = false;

  while (true) {
    if (prompt) {
      Console.CPrint(prompt);
    }

    //@formatter:off
    $try {
      Scanner.nextFormat(Console.scanner, format, dest);
      good = !Scanner.endLine(Console.scanner);
    } $catch (FormatException) {
    }
    //@formatter:on

    if (good) break;

    if (errorMessage) Console.CPrint(errorMessage);
    else
      $throw(FormatException, "Console: invalid token and no errorMessage!");
  }
}

static void
inputAndValidateToken(CString_t format, Pointer_t dest, CString_t prompt, CString_t errorMessage, Validator validator,
                      Object_t context) {
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
  int min = *((int *) ctx->first), max = *((int *) ctx->second);

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
  double min = *((double *) ctx->first), max = *((double *) ctx->second);

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
  puts(str);
}

static void printObj(Object_t obj) {
  String_t str = Object.toString(obj);
  Console.print(str);
  if (!Console.autoDestroyStrings) String.destroy(str);

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
    pause,
    setRusLocale,
    repeat,
    showMenu,
    confirm,
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
