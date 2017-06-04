//
// Created by Павел on 28.05.2017.
//

#pragma once

#include "../fwd.h"

#include <time.h>

$defineType(Time) {
  Class_t class;
  struct tm time;
  bool dateOnly;
};

$declareNamespace(Time) {
  Class_t class;

  Time_t (*fromTimestamp)(time_t time);
  Time_t (*fromString)(CString_t str);

  time_t (*toTimestamp)(Time_t self);

  $ObjectMethods(Time);
};
