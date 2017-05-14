//
// Created by Павел on 21.12.2016.
//

#include "scanner.h"
#include "../base/ibas.h"
#include "../base/string.h"

E4C_DEFINE_EXCEPTION(EmptyTokenException, "Scanner: unable to produce next token!", FormatException);

Scanner_t __Scanner_create(FILE *stream, String_t str, Object_t iter) {
  Scanner_t scan = Ibas.alloc(sizeof(Scanner_s), NULL);

  scan->multiline = true;
  scan->stream = stream;
  scan->str = str;
  scan->iter = iter;
  scan->delimiters = " \t\n";
  scan->last = 0;

  return scan;
}

Scanner_t __Scanner_fromStream(FILE *stream) {
  return __Scanner_create(stream, NULL, NULL);
}

Scanner_t __Scanner_fromString(String_t str, Object_t iter) {
  return __Scanner_create(NULL, str, iter);
}

void __Scanner_destroy(Scanner_t scan) {
  free(scan);
}

String_t __Scanner_toString(Scanner_t scan) {
  return String.format("[[Scanner stream=%p str=%p iter=%p]]", scan->stream, scan->str, scan->iter);
}

String_t __Scanner_nextToken(Scanner_t scan) {
  String_t buffer = String.create(0);
  char ch = 0;
  bool inToken = false, eof = false;

  while (true) {
    //@formatter:off
    try {
      ch = Scanner.nextChar(scan);
    } catch(EOFException) {
      eof = true;
    }
    //@formatter:on

    if (eof) break;

    if (strchr(scan->delimiters, ch)) {
      if (inToken || (ch == '\n' && !scan->multiline)) {
        scan->last = ch;
        break;
      } else continue;
    }

    inToken = true;
    String.add(buffer, ch);
  }

  return buffer;
}

void __Scanner_nextFormat(Scanner_t scan, CString format, Pointer dest) {
  //@formatter:off
  withObj(String_t, token) {
    token = Scanner.nextToken(scan);
  } use {
    if (!token->size) {
      throw(EmptyTokenException, NULL);
    }

    String_t _format = ToString.CStr(format);
    String.appendCStr(_format, "%n");

    int count;
    int ret = sscanf(token->storage, _format->storage, dest, &count);

    if (ret < 0) throw(RuntimeException, "Scanner: unknown error!");
    if (ret == 0 || count < token->size) throw(FormatException, NULL);
  };
  //@formatter:on
}

char __Scanner_nextChar(Scanner_t scan) {
  char ch = 0;

  if (scan->last) {
    ch = scan->last;
  } else if (scan->stream && !feof(scan->stream)) {
    ch = (char) fgetc(scan->stream);
  } else if (scan->str && scan->iter != String.end(scan->str)) {
    ch = String.iterGet(scan->str, scan->iter);
    scan->iter = String.iterNext(scan->str, scan->iter);
  } else {
    throw(EOFException, NULL);
  }

  scan->last = 0;
  return ch;
}

int __Scanner_nextInt(Scanner_t scan) {
  int ret = 0;
  Scanner.nextFormat(scan, "%d", &ret);
  return ret;
}

double __Scanner_nextDouble(Scanner_t scan) {
  double ret = 0;
  Scanner.nextFormat(scan, "%lf", &ret);
  return ret;
}

String_t __Scanner_nextLine(Scanner_t scan) {
  CString delims = scan->delimiters;
  scan->delimiters = "\n";
  bool multi = scan->multiline;
  scan->multiline = false;

  String_t ret = Scanner.nextToken(scan);
  scan->last = 0;

  scan->delimiters = delims;
  scan->multiline = multi;
  return ret;
}

String_t __Scanner_nextText(Scanner_t scan) {
  //TODO implement
}

void __Scanner_skipLine(Scanner_t scan) {
  while (Scanner.nextChar(scan) != '\n');
}

Scanner_c Scanner = {
    __Scanner_fromStream,
    __Scanner_fromString,
    __Scanner_destroy,
    __Scanner_toString,
    __Scanner_nextToken,
    __Scanner_nextFormat,
    __Scanner_nextChar,
    __Scanner_nextInt,
    __Scanner_nextDouble,
    __Scanner_nextLine,
    __Scanner_nextText,
    __Scanner_skipLine
};

Pointer Scanner_class[] = {
    implements(Scanner, Object, 2),
    NULL
};
