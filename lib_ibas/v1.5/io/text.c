//
// Created by Павел on 21.12.2016.
//

#include "text.h"

const int BUFFER_LENGTH = 256;

String readString(FILE *stream, char terminator) {
  String buffer = NULL, oldBuffer = NULL;
  int length = 0, allocated = 0;

  while (true) {
    if (length == allocated) {
      allocated += BUFFER_LENGTH;
      buffer = realloc(buffer, allocated * sizeof(char));
      if (buffer == NULL) {
        free(oldBuffer);
        return NULL;
      }
      oldBuffer = buffer;
    }

    char c = (char) fgetc(stream);
    if (c == terminator || feof(stream)) break;
    buffer[length++] = c;
  }

  if (length == allocated) {
    buffer = realloc(buffer, allocated * sizeof(char) + 1);
    if (buffer == NULL) {
      free(oldBuffer);
      return NULL;
    }
  }

  buffer[length] = 0;
  return buffer;
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
