//
// Created by Павел on 28.10.2016.
//

#include "lib_ibas/v1.0/io.h"
#include "lib_ibas/v1.0/string.h"

bool containEqualWords(wchar_t *str1, wchar_t *str2);

void inputAndCompareTexts();

int main() {
  setRusLocale();

  printf("This program compares two texts and tests if they contain the same sequence of words.\n"
             "Words can contain letters and decimal digits.\n"
             "Lowercase and uppercase letters a treated as equal.\n"
             "Author: Pavel Andreev\n\n");

  while (1) {
    inputAndCompareTexts();
    if (!prompt("Do you want to test another pair of texts? (Y/N): ")) {
      break;
    }
    putchar('\n');
  }

  return EXIT_SUCCESS;
}

void inputAndCompareTexts() {
  printf("Please enter the first text:\n"
             "(you can enter multiple lines, the first blank line signifies the end of the text)\n");
  wchar_t *text1 = wideStringToLower(stringToWide(inputText()));
  printf("Please enter the second text:\n");
  wchar_t *text2 = wideStringToLower(stringToWide(inputText()));
  if (containEqualWords(text1, text2)) {
    printf("Test passed!\n");
  } else {
    printf("Test failed!\n");
  }
  free(text1);
  free(text2);
}

bool containEqualWords(wchar_t *str1, wchar_t *str2) {
  bool insideWord = false;
  while (true) {
    if (!insideWord) {
      while (*str1 && !iswalnum(*str1)) {
        str1++;
      }

      while (*str2 && !iswalnum(*str2)) {
        str2++;
      }
    }

    if (*str1 != *str2) {
      return false;
    }
    if (!*str1) {
      return true;
    }

    str1++;
    str2++;

    if (iswalnum(*str1) || iswalnum(*str2)) {
      insideWord = true;
    } else {
      insideWord = false;
    }
  }
}
