//
// Created by Павел on 28.05.2017.
//

#include "time.h"
#include "../lib_ibas.h"

#define STR_SIZE 25

static bool isValidDate(CString_t date) {
  if (!isdigit(date[0])) return false;
  if (!isdigit(date[1])) return false;
  if (date[2] != '.') return false;
  if (!isdigit(date[3])) return false;
  if (!isdigit(date[4])) return false;
  if (date[5] != '.') return false;
  if (!isdigit(date[6])) return false;

  int i = 7;
  while (date[i])
    if (!isdigit(date[i++])) return false;

  return true;
}

static void parseDate(CString_t date, struct tm *tm) {
  if (!isValidDate(date)) $throw(FormatException, "Could not parse date!");

  tm->tm_year = atoi(date + 6) - 1900;
  tm->tm_mon = atoi(date + 3) - 1;
  tm->tm_mday = atoi(date);
}

static Time_t fromTimestamp(time_t time) {
  Time_t self = Ibas.allocEmpty(sizeof(Time_s), NULL);
  self->class = Time.class;

  self->time = *localtime(&time);
  self->dateOnly = false;

  return self;
}

static Time_t fromString(CString_t str) {
  Time_t self = Ibas.allocEmpty(sizeof(Time_s), NULL);
  self->class = Time.class;

  /*
  char *end = strptime(str, "%c", &self->time);
  if (end != strchr(str, '\0')) $throw(FormatException, "Could not parse time!");
  */
  parseDate(str, &self->time);
  self->dateOnly = true;

  return self;
}

static time_t toTimestamp(Time_t self) {
  return mktime(&self->time);
}

static void destroy(Time_t self) {
  free(self);
}

static String_t toString(Time_t self) {
  String_t str = String.create(STR_SIZE);
  CString_t format = self->dateOnly ? "%x" : "%c";

  strftime(str->storage, STR_SIZE, format, &self->time);
  str->size = strlen(str->storage);

  return str;
}

static int compare(Time_t time1, Time_t time2) {
  return (int) difftime(Time.toTimestamp(time1), Time.toTimestamp(time2));
}

static void serialize(Time_t self, Writer_t writer) {
  int time = (int) difftime(Time.toTimestamp(self), 0);
  Writer.format(writer, "%d", time);
}

static Time_t deserialize(Time_t self, Scanner_t scanner) {
  unsigned long long time;

  CString_t tmp = scanner->delimiters;
  scanner->delimiters = " ,}\n\t";
  Scanner.nextFormat(scanner, "%lld", &time);
  scanner->delimiters = tmp;

  if (self) self->time = *localtime((time_t *) &time);
  else self = Time.fromTimestamp((time_t) time);

  return self;
}

$defineNamespace(Time) {
    (Class_t) &Time.destroy,
    fromTimestamp,
    fromString,
    toTimestamp,
    destroy,
    toString,
    compare,
    serialize,
    deserialize
};
