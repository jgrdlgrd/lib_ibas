//
// Created by Павел on 05.12.2016.
//

#include <stdint.h>
#include "lib_ibas/v1.0/io.h"
#include "lib_ibas/v1.0/string.h"

typedef struct {
    size_t length, size;
} Specifier;

const size_t SIZES[9][6] = {
    {sizeof(int), sizeof(unsigned int), sizeof(float), sizeof(char), sizeof(void*), sizeof(int)},
    {sizeof(signed char), sizeof(unsigned char), 0, 0, 0, sizeof(signed char)},
    {sizeof(short int), sizeof(unsigned short int), 0, 0, 0, sizeof(short int)},
    {sizeof(long int), sizeof(unsigned long int), sizeof(double), sizeof(wchar_t), 0, sizeof(long int)},
    {sizeof(long long int), sizeof(unsigned long long int), 0, 0, 0, sizeof(long long int)},
    {sizeof(intmax_t), sizeof(uintmax_t), 0, 0, 0, sizeof(intmax_t)},
    {sizeof(size_t), sizeof(size_t), 0, 0, 0, sizeof(size_t)},
    {sizeof(ptrdiff_t), sizeof(ptrdiff_t), 0, 0, 0, sizeof(ptrdiff_t)},
    {0, 0, sizeof(long double), 0, 0, 0}
};

Specifier processSpecifier(const char *format) {
  const char *nextChar = format;
  bool asterisk = false;
  size_t size = 0;

  nextChar++;

  if (*nextChar == '%') {
    return (Specifier) {2, 0};
  }

  if (*nextChar == '*') {
    asterisk = true;
    nextChar++;
  }

  size_t width = 0;
  int widthLength = 0;
  sscanf(nextChar, "%zu%n", &width, &widthLength);
  nextChar += widthLength;

  if (!*nextChar) {
    return (Specifier) {0, 0};
  }

  int modifier;
  switch (*nextChar) {
    case 'h':
      if (*(nextChar + 1) == 'h') {
        nextChar++;
        modifier = 1;
      } else {
        modifier = 2;
      }
      break;
    case 'l':
      if (*(nextChar + 1) == 'l') {
        nextChar++;
        modifier = 4;
      } else {
        modifier = 3;
      }
      break;
    case 'j':
      modifier = 5;
      break;
    case 'z':
      modifier = 6;
      break;
    case 't':
      modifier = 7;
      break;
    case 'L':
      modifier = 8;
      break;
    default:
      modifier = 0;
      break;
  }

  if (modifier) {
    nextChar++;
  }

  int specifier;
  switch (*nextChar) {
    case 'd':
    case 'i':
      specifier = 0;
      break;
    case 'u':
    case 'o':
    case 'x':
      specifier = 1;
      break;
    case 'f':
    case 'e':
    case 'g':
    case 'a':
      specifier = 2;
      break;
    case '[':
      nextChar += strcspn(nextChar, "]");
      if (!*nextChar) {
        return (Specifier) {0, 0};
      }
    case 's':
      size = width + 1;
    case 'c':
      specifier = 3;
      break;
    case 'p':
      specifier = 4;
      break;
    case 'n':
      specifier = 5;
      break;
    default:
      return (Specifier) {0, 0};
  }

  if (!SIZES[modifier][specifier]) {
    return (Specifier) {0, 0};
  }

  if (!size) {
    size = SIZES[modifier][specifier];
  }

  if (asterisk) {
    size = 0;
  }

  return (Specifier) {nextChar - format + 1, size};
}

Specifier nextGroup(char *format) {
  char *nextChar = format;
  size_t size = 0;

  while (true) {
    nextChar += strcspn(nextChar, "%");
    if (!*nextChar || size) {
      break;
    }

    Specifier s = processSpecifier(nextChar);
    if (!s.length) {
      return (Specifier) {0, 0};
    }
    nextChar += s.length;
    size = s.size;
  }

  return (Specifier) {nextChar - format, size};
}

size_t computeTotalSize(char *format) {
  size_t total = 0;

  while (*format) {
    Specifier s = nextGroup(format);

    if (!s.length) {
      return (size_t) -1;
    }

    format += s.length;
    total += s.size;
  }

  return total;
}

void *inputStruct(FILE *stream, const char *format) {
  size_t length = strlen(format);
  if (!length) {
    return NULL;
  }
  length += 2;

  char *buffer = malloc(length * sizeof(char));
  if (!buffer) {
    return NULL;
  }
  memcpy(buffer, format, length);

  size_t size = computeTotalSize(buffer);
  if (size == (size_t) -1) {
    return NULL;
  }

  void *memory = NULL;
  if (size) {
    memory = malloc(size);
    if (!memory) {
      return NULL;
    }
  }

  void *ptr = memory;
  int n, N = 0;


  while (*buffer) {
    Specifier s = nextGroup(buffer);
    char tmp[3];
    memcpy(tmp, buffer + s.length, 3);
    memcpy(buffer + s.length, "%n", 3);
    int result = fscanf(stream, buffer, ptr, &n);
    N += n;
    buffer += s.length;
    memcpy(buffer, tmp, 3);
    ptr += s.size;
  }

  return memory;
}

typedef struct {
    int i, j;
    double d;
    char s[5];
    char n;
} MyStruct;

/*int main(int argc, char **argv) {
  MyStruct *s = inputStruct(stdin, "%d %d %lf %4[asd] %n");
  if (!s) printf("ERROR!!!");
  printf("%d %d %lf %s %c", s->i, s->j, s->d, s->s, s->n);
  return 0;
}*/
