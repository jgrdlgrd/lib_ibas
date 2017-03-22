//
// Created by Павел on 17.12.2016.
//

#include "console.h"

Colors_t_ Colors = {
    "\033[0m",
    "\033[1;31m",
    "\033[1;32m"
};

int colored(CString colour, CString format, ...) {
  va_list args;
  va_start (args, format);
  printf(colour);
  int ret = vprintf (format, args);
  printf(Colors.RESET);
  va_end (args);
  return ret;
}

void newLine() {
  putchar('\n');
}

void clearScreen() {
  #ifdef __CYGWIN__
     system("clear");
  #else
    system("cls");
  #endif
}

void flush() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

void pause() {
#ifdef __CYGWIN__
  getchar();
#else
  system("pause");
#endif
}

CString setRusLocale() {
#ifdef __CYGWIN__
  return setlocale(LC_ALL, "ru_RU.utf8");
#else
  return setlocale(LC_ALL, "Russian");
#endif
}

int inputToken(CString format, void *dest, CString prompt, CString errorMessage) {
  FILE *stream = Scanner.stream;

  int err = 0;
  while (true) {
    if (prompt) {
      printf(prompt);
    }

    err = Scanner.next(format, dest);
    if (err <= 0 || (err > 0 && errorMessage == NULL)) {
      break;
    }

    printf(errorMessage);
  }

  Scanner.stream = stream;
  return err;
}

int inputInt(CString prompt, CString errorMessage) {
  int ret = 0;
  inputToken("%d", &ret, prompt, errorMessage);
  return ret;
}


double inputDouble(CString prompt, CString errorMessage) {
  double ret = 0;
  inputToken("%lf", &ret, prompt, errorMessage);
  return ret;
}

int inputAndValidateToken(CString format, void *dest, CString prompt, CString errorMessage, Validator validator, Object context) {
  while (true) {
    int err = inputToken(format, dest, prompt, errorMessage);
    //prompt = NULL;

    if (!err) {
      err = validator(context, dest);
    }

    if (!err || errorMessage == NULL) {
      return err;
    }

    //printf(errorMessage);
  }
}

int intRangeValidator(Triple *ctx, int *val) {
  int min = *((int*) ctx->first), max = *((int*) ctx->second);

  if (*val >= min && *val <= max) {
    return 0;
  }

  printf((CString) ctx->third, min, max);
  return (*val < min) ? -1 : 1;
}

int inputIntFromInterval(CString prompt, CString errorMessage, int min, int max) {
  int ret;
  Triple ctx = {&min, &max, errorMessage};
  inputAndValidateToken("%d", &ret, prompt, errorMessage, (Validator) intRangeValidator, &ctx);
  return ret;
}

int doubleRangeValidator(Triple *ctx, double *val) {
  double min = *((double*) ctx->first), max = *((double*) ctx->second);

  if (*val >= min && *val <= max) {
    return 0;
  }

  printf((CString) ctx->third, min, max);
  return (*val < min) ? -1 : 1;
}

double inputDoubleFromInterval(CString prompt, CString errorMessage, double min, double max) {
  double ret;
  Triple ctx = {&min, &max, errorMessage};
  inputAndValidateToken("%lf", &ret, prompt, errorMessage, (Validator) doubleRangeValidator, &ctx);
  return ret;
}

int showMenu(int count, CString labels[count]) {
  static CString prompt = "Выберите действие: ";
  static CString errorMessage = "Недопустимое действие!\n";

  printf(prompt);
  newLine();

  for (int i = 0; i < count; i++) {
    printf("  %d - %s\n", i + 1, labels[i]);
  }
  newLine();

  errno = 0;
  int option = inputIntFromInterval(prompt, errorMessage, 1, count);
  if (errno) {
    errno = 0;
    return -abs(errno);
  }
  return option;
}

bool prompt(CString question) {
  printf(question);
  CString str = Scanner.nextToken();
  if (!str) {
    return false;
  }
  char ch = *str;
  bool ans = false;
  if (ch == 'Y' || ch == 'y') ans = true;
  else if (ch == -48) {
    ch = *(str + 1);
    ans = ch == -67 || ch == -99;
  };
  free(str);
  return ans;
}

int repeat(int (*f)(), CString question) {
  int err = 0;
  do {
    err = f();
  } while (!err && prompt(question));
  return err;
}

Console_t_ Console = {
    newLine,
    clearScreen,
    flush,
    pause,
    setRusLocale,
    repeat,
    showMenu,
    prompt,
    inputInt,
    inputDouble,
    inputIntFromInterval,
    inputDoubleFromInterval,
    colored
};
