//
// Created by Павел on 07.11.2016.
//

#include "string.h"

wchar_t *stringToWide(char *string) {
  size_t length = mbstowcs(NULL, string, 0) + 1;
  wchar_t *result = NULL;
  if (length) {
    result = malloc(length * sizeof(wchar_t));
    //printf("%s %d", string, length);
    mbstowcs(result, string, length);
  }
  //free(string);//TODO ?
  return result;
}

wchar_t *wideStringToLower(wchar_t *str) {
  wchar_t *c = str;
  while (*c) {
    *c = (wchar_t) towlower(*c);
    c++;
  }
  return str;
}

char *stringToLower(char *str) {
  char *c = str;
  while (*c) {
    *c = (char) tolower(*c);
    c++;
  }
  return str;
}
