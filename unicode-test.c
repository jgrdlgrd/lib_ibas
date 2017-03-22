//
// Created by Павел on 07.11.2016.
//

#include "lib_ibas/v1.0/io.h"
#include "lib_ibas/v1.0/wide-io.h"
#include "lib_ibas/v1.0/string.h"
#include <windows.h>

bool setLocale(char *locale) {
  char *l = setlocale(LC_ALL, locale);
  if (l) {
    printf("Locale: %s\n", l);
    return true;
  } else {
    printf("Could not set locale \"%s\"!\n\n", locale);
    return false;
  }
}

void test(char *locale, char *str) {
  if (!setLocale(locale)) {
    return;
  }

  printf("Echo:\t\t%s\n", str);

  printf("Plain:\t\t");
  unsigned int d;
  char *c = str, *l;
  while (*c) {
    d = (unsigned int) *c & 0x000000FF;
    printf("[%u]%c", d, *c);
    c++;
  }
  printf("\n");

  printf("Multibyte:\t");
  c = str;
  wchar_t tmp, *w = &tmp;
  int length;
  size_t max = strlen(str);
  mbtowc (NULL, NULL, 0);
  while (max > 0) {
    length = mbtowc(w, c, max);
    if (length < 1) {
      if (length < 0) {
        printf("[invalid sequence]");
      }
      break;
    }
    l = c + length;
    while (c < l) {
      d = (unsigned int) *c & 0x000000FF;
      printf("[%u]", d);
      c++;
    }
    c = l - length;
    while (c < l) {
      putchar(*c++);
    }
    max -= length;
  }
  printf("\n");

  wchar_t *wide = stringToWide(str);
  printf("Wide:\t\t");
  if (wide) {
    w = wide;
    while (*w) {
      printf("[%u]%lc", *w, *w);
      w++;
    }
    free(wide);
  } else {
    printf("[invalid string]");
  }

  printf("\n\n");
}

void testWide(char *locale, wchar_t *str) {
  if (!setLocale(locale)) {
    return;
  }

  printf("Echo:\t\t");
  fputws(str, stdout);
  printf("\n");

  printf("Plain:\t\t");
  while (*str) {
    printf("[%u]", *str);
    putwchar(*str);
    str++;
  }
  printf("\n\n");
}

int main() {
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);

  printf("-----Byte-oriented-----\n");
  printf("Enter a Unicode string: ");
  char *line = inputLine();
  printf("\n");

  test(NULL, line);
  test("ru_RU.koi8r", line);
  test("ru_RU", line);
  test("", line);
  test("ru_RU.utf8", line);
  test("Russian", line);
  test("C.utf-8", line);
  test("C.utf8", line);
  test("ru-RU", line);

  free(line);

  freopen(NULL, "r", stdin);
  printf("-----Wide-oriented-----\n");
  printf("Enter a Unicode string: ");
  wchar_t *wide = inputWideLine();
  printf("\n");

  testWide("C", wide);
  testWide("", wide);

  free(wide);

  getchar();

  return 0;
}
