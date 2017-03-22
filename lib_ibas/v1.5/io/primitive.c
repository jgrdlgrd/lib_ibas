//
// Created by Павел on 21.12.2016.
//

#include "primitive.h"

int inputToken(String format, void *ptr, String prompt, String errorMessage) {
  String str;
  while (1) {
    if (prompt != NULL) {
      printf(prompt);
    }

    str = readLine(stdin);
    if (str == NULL) {
      return -2;
    }

    if (sscanf(str, format, ptr)) {
      free(str);
      return 0;
    }

    free(str);

    if (errorMessage == NULL) {
      return 2;
    }
    printf(errorMessage);
  }
}

double readDouble(String prompt, String errorMessage) {
  double ret = 0;
  int err;
  err = inputToken("%lf", &ret, prompt, errorMessage);
  if (err) {
    errno = err;
    return 0;
  }
  return ret;
}

double readDoubleFromInterval(String prompt, String errorMessage, double min, double max) {
  double ret;
  while (1) {
    errno = 0;
    ret = readDouble(prompt, errorMessage);
    //prompt = NULL;
    if (errno) {
      return 0;
    } else if (ret < min) {
      errno = -1;
    } else if (ret > max) {
      errno = 1;
    } else {
      return ret;
    }
    if (errorMessage == NULL) {
      return 0;
    }
    printf(errorMessage, min, max);
  }
}

int readInt(String prompt, String errorMessage) {
  int err, ret = 0;
  err = inputToken("%d", &ret, prompt, errorMessage);
  if (err) {
    errno = err;
    return 0;
  }
  return ret;
}

int readIntFromInterval(String prompt, String errorMessage, int min, int max) {
  int ret;
  while (1) {
    errno = 0;
    ret = readInt(prompt, errorMessage);
    //prompt = NULL;
    if (errno) {
      return 0;
    } else if (ret < min) {
      errno = -1;
    } else if (ret > max) {
      errno = 1;
    } else {
      return ret;
    }
    if (errorMessage == NULL) {
      return 0;
    }
    printf(errorMessage, min, max);
  }
}
