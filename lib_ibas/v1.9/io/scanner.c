//
// Created by Павел on 21.12.2016.
//

#include "scanner.h"

String _nextToken(bool skipPrefix) {
  String buffer = NULL, oldBuffer = NULL;
  int length = 0, allocated = 0;
  char ch;

  while (true) {
    if (length == allocated) {
      allocated += BUFFER_LENGTH;
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

String nextToken() {
  return _nextToken(true);
}

int next(String format, void *dest) {
  String token = nextToken();

  if (!token) {
    return -1;
  }

  size_t tokenLength = strlen(token), formatLength = strlen(format);

  String _format = malloc(formatLength + 3);
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

String nextLine() {
  String delims = Scanner.delimiters;
  Scanner.delimiters = "\n";

  String ret = _nextToken(false);

  Scanner.delimiters = delims;
  return ret;
}

//TODO rewrite
String nextText() {
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

Scanner_t Scanner = {
    NULL,
    " \t\n",
    next,
    nextToken,
    nextInt,
    nextDouble,
    nextLine,
    nextText
};
