//
// Created by Павел on 23.12.2016.
//

#include "util.h"

bool isValidDate(String date) {
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

bool isBetween(String date1, String date2, String date) {
  int year1 = atoi(date1 + 6), year2 = atoi(date2 + 6), year = atoi(date + 6);
  if (year < year1 || year > year2) return false;
  if (year > year1 && year < year2) return true;

  int month1 = atoi(date1 + 3), month2 = atoi(date2 + 3), month = atoi(date + 3);
  if (year == year1 && month < month1) return false;
  if (year == year2 && month > month2) return false;
  if ((year > year1 || month > month1) && (year < year2 || month < month2)) return true;

  int day1 = atoi(date1), day2 = atoi(date2), day = atoi(date);
  if (year == year1 && month == month1 && day < day1) return false;
  if (year == year2 && month == month2 && day > day2) return false;

  return true;
}
