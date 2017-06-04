//
// Created by Павел on 21.05.2017.
//

#include "writer.h"
#include "../base/base.h"

static Writer_t create(FILE *stream, String_t str, Pointer_t iter) {
  Writer_t self = Ibas.alloc(sizeof(Writer_s), NULL);

  self->class = Writer.class;
  self->lineSeparator = "\n";
  self->destroySource = false;

  self->stream = stream;

  if (str && !iter) iter = String.begin(str);
  self->iter = iter;
  self->str = str;

  return self;
}

static Writer_t fromStream(FILE *stream) {
  return create(stream, NULL, NULL);
}

static Writer_t fromString(String_t str, Pointer_t iter) {
  return create(NULL, str, iter);
}

static void destroy(Writer_t self) {
  if (!self) return;

  if (self->destroySource) {
    if (self->str) String.destroy(self->str);
    if (self->stream) File_w.destroy(&self->stream);
  }

  free(self);
}

static String_t toString(Writer_t self) {
  return String.format("[[Writer stream=%p str=%p iter=%p]]", self->stream, self->str, self->iter);
}

static int compare(Writer_t obj1, Writer_t obj2) {
  $throw(NotImplementedException, "Writer.compare() is not implemented!");
  return 0;
}

static void serialize(Writer_t self, Writer_t writer) {
  $throw(NotImplementedException, "Writer.serialize() is not implemented!");
}

static Writer_t deserialize(Writer_t self, Scanner_t Writer) {
  $throw(NotImplementedException, "Writer.deserialize() is not implemented!");
  return NULL;
}

static void newLine(Writer_t self) {
  Writer.CPrint(self, self->lineSeparator);
}

static void print(Writer_t self, String_t str) {
  Writer.CPrint(self, String.CStr(str));
}

static void println(Writer_t self, String_t str) {
  Writer.print(self, str);
  Writer.newLine(self);
}

static void CPrint(Writer_t self, CString_t str) {
  if (self->stream) {
    fputs(str, self->stream);
  }

  if (self->str) {
    //String.iterInsertAll(self->str, self->iter, str); //TODO
  }
}

static void CPrintln(Writer_t self, CString_t str) {
  Writer.CPrint(self, str);
  Writer.newLine(self);
}

static void printObj(Writer_t self, Object_t obj) {
  String_t str = Object.toString(obj);
  Writer.print(self, str);
  String.destroy(str);
}

static void format(Writer_t self, CString_t format, ...) {
  va_list args;
  va_start(args, format);

  if (self->stream) {
    vfprintf(self->stream, format, args);
  }

  if (self->str) {
    //TODO
  }

  va_end (args);
}

$defineNamespace(Writer) {
    (Class_t) &Writer.destroy,
    fromStream,
    fromString,
    destroy,
    toString,
    compare,
    serialize,
    deserialize,
    newLine,
    print,
    println,
    CPrint,
    CPrintln,
    printObj,
    format
};
