//
// Created by Павел on 17.12.2016.
//

#include "console.h"

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

String setRusLocale() {
#ifdef __CYGWIN__
  return setlocale(LC_ALL, "ru_RU.utf8");
#else
  return setlocale(LC_ALL, "Russian");
#endif
}

int showMenu(const int count, String labels[count]) {
  static String prompt = "Выберите действие: ";
  static String errorMessage = "Недопустимое действие!\n";

  printf(prompt);
  newLine();

  for (int i = 0; i < count; i++) {
    printf("  %d - %s\n", i + 1, labels[i]);
  }
  newLine();

  errno = 0;
  int option = readIntFromInterval(prompt, errorMessage, 1, count);
  if (errno) {
    errno = 0;
    return -abs(errno);
  }
  return option;
}

bool prompt(String question) {
  printf(question);
  String str = readLine(stdin);
  if (!str) {
    return false;
  }
  char ch = *str;
  free(str);
  return ch == L'Y' || ch == L'y' || ch == L'Н' || ch == L'н';
}
