//
// Created by Павел on 21.12.2016.
//

#include <errno.h>

#include "scanner.h"

CString __Scanner_nextToken_(bool skipPrefix) {
  CString buffer = NULL, oldBuffer = NULL;
  int length = 0, allocated = 0;
  char ch;

  while (true) {
    if (length == allocated) {
      allocated += SCANNER_BUFFER_LENGTH;
      buffer = realloc(buffer, allocated * sizeof(char) + 1);
      if (buffer == NULL) {
        free(oldBuffer);
        return NULL;
      }
      oldBuffer = buffer;
    }

    while (true) {
      if (feof(Scanner.stream)) goto end;
      ch = (char) fgetc(Scanner.stream);
      if (strchr(Scanner.delimiters, ch)) {
        if (!skipPrefix) goto end;
        continue;
      }
      break;
    }

    skipPrefix = false;
    buffer[length++] = ch;
  }

  end:
  buffer[length] = 0;
  return buffer;
}

CString __Scanner_nextToken() {
  return __Scanner_nextToken_(true);
}

int __Scanner_next(CString format, void *dest) {
  CString token = Scanner.nextToken();

  if (!token) {
    return -1;
  }

  size_t tokenLength = strlen(token), formatLength = strlen(format);

  CString _format = malloc(formatLength + 3);
  if (!_format) {
    free(token);
    return -2;
  }

  strcpy(_format, format);
  strcpy(_format + formatLength, "%n");

  int count;
  int ret = sscanf(token, _format, dest, &count);
  free(token);

  if (ret < 0) {
    return ret;
  } else if (ret == 0) {
    return 1;
  } else if (count < tokenLength) {
    return 2;
  }

  return 0;
}

int __Scanner_nextInt() {
  int ret = 0;

  int err = Scanner.next("%d", &ret);
  if (err) {
    errno = err;
  }

  return ret;
}

double __Scanner_nextDouble() {
  double ret = 0;

  int err = Scanner.next("%lf", &ret);
  if (err) {
    errno = err;
  }

  return ret;
}

CString __Scanner_nextLine() {
  CString delims = Scanner.delimiters;
  Scanner.delimiters = "\n";

  CString ret = __Scanner_nextToken_(false);

  Scanner.delimiters = delims;
  return ret;
}

//TODO rewrite
CString __Scanner_nextText() {
  char *text, *nextL;
  text = Scanner.nextLine();
  if (*text == '\0')
    return text;
  size_t length = strlen(text) + 2, newLength;
  while ((newLength = strlen(nextL = Scanner.nextLine()))) {
    *(text + length - 2) = '\n';
    length += newLength + 1;
    realloc(text, length);
    strcpy(text + length - newLength - 2, nextL);
    free(nextL);
  }
  return text;
}

Scanner_c Scanner = {
    NULL,
    " \t\n",
    __Scanner_next,
    __Scanner_nextToken,
    __Scanner_nextInt,
    __Scanner_nextDouble,
    __Scanner_nextLine,
    __Scanner_nextText
};
