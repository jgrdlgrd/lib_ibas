//
// Created by Павел on 21.12.2016.
//

#include "scanner.h"
#include "../base/base.h"

E4C_DEFINE_EXCEPTION(EmptyTokenException, "Scanner: unable to produce next token!", FormatException);

Scanner_t __Scanner_create(FILE *stream, String_t str, Object_t iter) {
  Scanner_t self = Ibas.alloc(sizeof(Scanner_s), NULL);

  self->class = Scanner.class;
  self->multiline = true;
  self->delimiters = " \t\n";
  self->last = 0;

  self->stream = stream;

  if (str && !iter) iter = String.begin(str);
  self->iter = iter;
  self->str = str;

  return self;
}

Scanner_t __Scanner_fromStream(FILE *stream) {
  return __Scanner_create(stream, NULL, NULL);
}

Scanner_t __Scanner_fromString(String_t str, Object_t iter) {
  return __Scanner_create(NULL, str, iter);
}

void __Scanner_destroy(Scanner_t self) {
  free(self);
}

String_t __Scanner_toString(Scanner_t self) {
  return String.format("[[Scanner stream=%p str=%p iter=%p]]", self->stream, self->str, self->iter);
}

int __Scanner_compare(Scanner_t obj1, Scanner_t obj2) {
  throw(NotImplementedException, "Scanner.compare() not implemented!");
}

unsigned __Scanner_read(Scanner_t self, String_t buffer) {
  char ch = 0;
  bool inToken = false, eof = false;
  unsigned count = 0;

  while (true) {
    //@formatter:off
    try {
      ch = Scanner.nextChar(self);
    } catch(EOFException) {
      eof = true;
    }
    //@formatter:on

    if (eof) break;

    if (strchr(self->delimiters, ch)) {
      if (inToken || (ch == '\n' && !self->multiline)) {
        self->last = ch;
        break;
      } else continue;
    }

    inToken = true;
    count++;
    if (buffer) String.add(buffer, ch);
  }

  return count;
}

String_t __Scanner_nextToken(Scanner_t self) {
  String_t buffer = String.create(0);
  __Scanner_read(self, buffer);
  return buffer;
}

void __Scanner_nextFormat(Scanner_t self, CString_t format, Pointer_t dest) {
  //@formatter:off
  $withObj(String_t, token) {
    token = Scanner.nextToken(self);
  } use {
    if (!token->size) {
      throw(EmptyTokenException, NULL);
    }

    String_t _format = CString_w->toString(format);
    String.appendCStr(_format, "%n");

    int count;
    int ret = sscanf(String.CStr(token), String.CStr(_format), dest, &count);

    if (ret < 0) throw(RuntimeException, "Scanner: unknown error!");
    if (ret == 0 || count < token->size) throw(FormatException, NULL);
  };
  //@formatter:on
}

char __Scanner_nextChar(Scanner_t self) {
  char ch = 0;

  if (self->last) {
    ch = self->last;
  } else if (self->stream && !feof(self->stream)) {
    ch = (char) fgetc(self->stream);
  } else if (self->str && self->iter != String.end(self->str)) {
    ch = String.iterGet(self->str, self->iter);
    self->iter = String.iterNext(self->str, self->iter);
  } else {
    throw(EOFException, NULL);
  }

  self->last = 0;
  return ch;
}

int __Scanner_nextInt(Scanner_t self) {
  int ret = 0;
  Scanner.nextFormat(self, "%d", &ret);
  return ret;
}

double __Scanner_nextDouble(Scanner_t self) {
  double ret = 0;
  Scanner.nextFormat(self, "%lf", &ret);
  return ret;
}

String_t __Scanner_nextLine(Scanner_t self) {
  CString_t delims = self->delimiters;
  self->delimiters = "\n";
  bool multi = self->multiline;
  self->multiline = false;

  String_t ret = Scanner.nextToken(self);
  self->last = 0;

  self->delimiters = delims;
  self->multiline = multi;
  return ret;
}

String_t __Scanner_nextText(Scanner_t self) {
  //TODO implement
  return NULL;
}

unsigned __Scanner_skip(Scanner_t self) {
  return __Scanner_read(self, NULL);
}

unsigned __Scanner_skipLine(Scanner_t self) {
  unsigned count = 0;
  while (Scanner.nextChar(self) != '\n') count++;
  return count;
}

$defineNamespace(Scanner) {
    (Class_t) &Scanner.destroy,
    __Scanner_fromStream,
    __Scanner_fromString,
    __Scanner_destroy,
    __Scanner_toString,
    __Scanner_compare,
    __Scanner_nextToken,
    __Scanner_nextFormat,
    __Scanner_nextChar,
    __Scanner_nextInt,
    __Scanner_nextDouble,
    __Scanner_nextLine,
    __Scanner_nextText,
    __Scanner_skip,
    __Scanner_skipLine
};
