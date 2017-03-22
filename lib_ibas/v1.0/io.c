#include <errno.h>
#include "io.h"
#include "string.h"

const int BUFFER_LENGTH = 256;

char *inputString(char terminator) {
  char *buffer = NULL, *oldBuffer = NULL, *end = NULL;
  int length = BUFFER_LENGTH, offset = 0;
  while (1) {
    buffer = (char *) realloc((void *) oldBuffer, length * sizeof(char));
    if (buffer == NULL) {
      free((void *) oldBuffer);
      return NULL;
    }
    end = buffer + length;
    oldBuffer = buffer;
    *(end - 1) = *(end - 2) = 'a';//TODO may collide with the terminator
    if (fgets(buffer + offset, length - offset, stdin) == NULL) {
      free(buffer);
      return NULL;
    }
    if ((*(end - 1) == '\0') && (*(end - 2) != terminator)) {
      length += BUFFER_LENGTH;
      offset += BUFFER_LENGTH - 1;
      continue;
    }
    *strchr(buffer + offset, terminator) = '\0';
    return buffer;
  }
}

char *inputLine() {
  return inputString('\n');
}

char *inputText() {
  char *text, *nextLine;
  text = inputLine();
  if (*text == '\0')
    return text;
  size_t length = strlen(text) + 2, newLength;
  while ((newLength = strlen(nextLine = inputLine()))) {
    *(text + length - 2) = '\n';
    length += newLength + 1;
    realloc(text, length);
    strcpy(text + length - newLength - 2, nextLine);
    free(nextLine);
  }
  return text;
}

int inputToken(char *format, void *ptr, char *prompt, char *errorMessage) {
  char *str;
  if (prompt != NULL) {
    printf(prompt);
  }
  while (1) {
    str = inputLine();
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

double readDouble(char *prompt, char *errorMessage) {
  double ret = 0;
  int err;
  err = inputToken("%lf", &ret, prompt, errorMessage);
  if (err) {
    errno = err;
    return 0;
  }
  return ret;
}

double readDoubleFromInterval(char *prompt, char *errorMessage, double min, double max) {
  double ret;
  while (1) {
    errno = 0;
    ret = readDouble(prompt, errorMessage);
    prompt = NULL;
    if (errno) {
      return 0;
    } else if (ret < min) {
      errno = -1;
    } else if (ret > max) {
      errno = 1;
    } else {
      return ret;
    }
    if (errorMessage == NULL) {
      return 0;
    }
    printf(errorMessage, min, max);
  }
}

int readInt(char *prompt, char *errorMessage) {
  int err, ret = 0;
  err = inputToken("%d", &ret, prompt, errorMessage);
  if (err) {
    errno = err;
    return 0;
  }
  return ret;
}

int readIntFromInterval(char *prompt, char *errorMessage, int min, int max) {
  int ret;
  while (1) {
    errno = 0;
    ret = readInt(prompt, errorMessage);
    prompt = NULL;
    if (errno) {
      return 0;
    } else if (ret < min) {
      errno = -1;
    } else if (ret > max) {
      errno = 1;
    } else {
      return ret;
    }
    if (errorMessage == NULL) {
      return 0;
    }
    printf(errorMessage, min, max);
  }
}

void flush() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

char* setRusLocale() {
  return setlocale(LC_ALL, "ru_RU.utf8");
}

bool prompt(char *question) {
  printf(question);
  wchar_t *str = stringToWide(inputLine());
  if (!str) {
    return false;
  }
  wchar_t ch = *str;
  //printf("%ls %d", str, *(str+1));
  free(str);
  return ch == L'Y' || ch == L'y' || ch == L'Н' || ch == L'н';
}
