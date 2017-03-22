//
// Created by Павел on 09.11.2016.
//

#include "wide-io.h"

const int WIDE_BUFFER_LENGTH = 256;

wchar_t * inputWideString(wchar_t terminator) {
  wchar_t *buffer = NULL, *oldBuffer = NULL, *end = NULL;
  int length = WIDE_BUFFER_LENGTH, offset = 0;
  while (1) {
    buffer = (wchar_t *) realloc(oldBuffer, length * sizeof(wchar_t));
    if (buffer == NULL) {
      free(oldBuffer);
      return NULL;
    }
    end = buffer + length;
    oldBuffer = buffer;
    *(end - 1) = *(end - 2) = L'a';//TODO may collide with the terminator
    if (fgetws(buffer + offset, length - offset, stdin) == NULL) {
      free(buffer);
      return NULL;
    }
    if ((*(end - 1) == L'\0') && (*(end - 2) != terminator)) {
      length += WIDE_BUFFER_LENGTH;
      offset += WIDE_BUFFER_LENGTH - 1;
      continue;
    }
    *wcschr(buffer + offset, terminator) = L'\0';
    return buffer;
  }
}

wchar_t * inputWideLine() {
  return inputWideString(L'\n');
}
