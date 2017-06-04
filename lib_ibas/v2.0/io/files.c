//
// Created by Павел on 21.05.2017.
//

#include "files.h"
#include "../lib_ibas.h"

$defineException(FileOpenException, "", InputOutputException);
$defineException(FileAlreadyExistsException, "", InputOutputException);

static void createFile(CString_t path, bool rewriteExisting) {
  FILE *stream = fopen(path, rewriteExisting ? "w" : "a");
  if (!stream) $throw(InputOutputException, "Could not create the file!");
  fclose(stream);
}

static String_t readFile(CString_t path) {
  String_t str = NULL;
  //@formatter:off
  $withAuto(Scanner_t, scan) {
    scan = Files.openScanner(path);
  } $use {
    scan->delimiters = "";
    str = Scanner.nextToken(scan);
  };
  //@formatter:on
  return str;
}

static Scanner_t openScanner(CString_t path) {
  FILE *stream = fopen(path, "r");
  if (!stream) $throw(FileOpenException, "Could not open the file!");

  Scanner_t ret = Scanner.fromStream(stream);
  ret->destroySource = true;
  return ret;
}

static Writer_t openWriter(CString_t path, bool append) {
  FILE *stream = fopen(path, append ? "a" : "w");
  if (!stream) $throw(FileOpenException, "Could not open the file!");

  Writer_t ret = Writer.fromStream(stream);
  ret->destroySource = true;
  return ret;
}

$defineNamespace(Files) {
  createFile,
  readFile,
  openScanner,
  openWriter
};
