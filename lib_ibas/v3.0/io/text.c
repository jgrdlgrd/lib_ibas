//
// Created by Павел on 21.12.2016.
//

#include "text.h"

const int BUFFER_LENGTH = 256;

String readString(FILE *stream, char terminator) {
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
    if (fgets(buffer + offset, length - offset, stream) == NULL) {
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

String readLine(FILE *stream) {
  return readString(stream, '\n');
}

String readText(FILE *stream) {
  char *text, *nextLine;
  text = readLine(stream);
  if (*text == '\0')
    return text;
  size_t length = strlen(text) + 2, newLength;
  while ((newLength = strlen(nextLine = readLine(stream)))) {
    *(text + length - 2) = '\n';
    length += newLength + 1;
    realloc(text, length);
    strcpy(text + length - newLength - 2, nextLine);
    free(nextLine);
  }
  return text;
}
