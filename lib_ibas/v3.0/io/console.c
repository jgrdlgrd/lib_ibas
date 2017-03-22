//
// Created by Павел on 17.12.2016.
//

#include "console.h"
#include "lib_ibas/v3.0/functions.h"

void newLine() {
  putchar('\n');
}

int showMenu(String prompt, const int count, String labels[count], BoundRunnable actions[count]) {
  //TODO messages
  Validator validator = chainValidators(
      PromptErrorValidator(prompt, "Недопустимое действие!\n"),
      IntRangeValidator(1, count)
  );
  int option;

  while (true) {
    clearScreen();

    printf(prompt);
    newLine();
    for (int i = 0; i < count; i++) {
      printf("  %d - %s\n", i + 1, labels[i]);
    }
    newLine();

    errno = 0;
    option = readIntV(validator);
    if (errno) {
      option = -abs(errno);
      errno = 0;
      break;
    }

    BoundRunnable action = actions[option - 1];
    if (!action.call || action.call(action.context)) break;
  }

  destroyValidator(validator);
  return option;
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

String setRusLocale() {
  return setlocale(LC_ALL, "ru_RU.utf8");
}

bool prompt(String question) {
  printf(question);
  String str = readLine(stdin);
  if (!str) {
    return false;
  }
  char ch = *str;
  //printf("%ls %d", str, *(str+1));
  free(str);
  return ch == 'Y' || ch == 'y' || ch == 'Н' || ch == 'н';
}

/*

int scanFullLine(BoundRunnable scanner) {
  int tmp = getchar();
  if (tmp == '\n') return -1;
  ungetc(tmp, stdin);
  int ret = scanner.call(scanner.context);
  if (getchar() != '\n') {
    rewind(stdin);
    return -2;
  }
  return ret;
}

typedef struct {
    String format;
    void *dest;
    Validator v;
} SCFL_ctx;

int SCFL_call(SCFL_ctx *ctx) {
  return scanToken(ctx->format, ctx->dest, ctx->v);
}

int scanTokenFullLine(String format, void *dest, Validator v) {
  SCFL_ctx *ctx = malloc(sizeof(SCFL_ctx));
  ctx->format = format;
  ctx->dest = dest;
  ctx->v = v;

  BoundRunnable bound = (BoundRunnable) {(Consumer) SCFL_call, (Consumer) free, ctx};
  int ret = scanFullLine(bound);
  bound.destroy(bound.context);
  return ret;
}

int inputFormat(char *format, void *ptr, char *prompt, char *errorMessage) {
  char *str;
  if (prompt != NULL) {
    printf(prompt);
  }
  while (1) {
    str = readLine();
    if (str == NULL) {
      return -2;
    }
    if (sscanf(str, format, ptr)) {
      free(str);
      return 0;
    }
    free(str);
    if (errorMessage == NULL) {
      return 2;
    }
    printf(errorMessage);
  }
}

*/
