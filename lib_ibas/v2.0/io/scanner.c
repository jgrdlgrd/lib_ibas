//
// Created by Павел on 21.12.2016.
//

#include "scanner.h"

CString _nextToken(bool skipPrefix) {
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

CString nextToken() {
  return _nextToken(true);
}

int next(CString format, void *dest) {
  CString token = nextToken();

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

int nextInt() {
  int ret = 0;

  int err = next("%d", &ret);
  if (err) {
    errno = err;
  }

  return ret;
}

double nextDouble() {
  double ret = 0;

  int err = next("%lf", &ret);
  if (err) {
    errno = err;
  }

  return ret;
}

CString nextLine() {
  CString delims = Scanner.delimiters;
  Scanner.delimiters = "\n";

  CString ret = _nextToken(false);

  Scanner.delimiters = delims;
  return ret;
}

//TODO rewrite
CString nextText() {
  char *text, *nextL;
  text = nextLine();
  if (*text == '\0')
    return text;
  size_t length = strlen(text) + 2, newLength;
  while ((newLength = strlen(nextL = nextLine()))) {
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
    next,
    nextToken,
    nextInt,
    nextDouble,
    nextLine,
    nextText
};
