//
// Created by Павел on 21.12.2016.
//

#include "primitive.h"

int readToken(String format, void *dest, Validator v) {
  while (true) {
    int ret = v.start(v.context);
    if (ret) return ret;
    String s = readLine(stdin);
    ret = sscanf(s, format, dest);
    //TODO bind to end
    free(s);
    void *ptr = ret == 1 ? dest : NULL;
    ret = v.process(v.context, ptr);
    if (ret <= 0) return ret;
  }
}

int readInt(String prompt, String error) {
  return readIntV(PromptErrorValidator(prompt, error));
}

int readIntV(Validator v) {
  int ret;
  errno = readToken("%i", &ret, v);
  return ret;
}

double readDouble(String prompt, String error) {
  return readDoubleV(PromptErrorValidator(prompt, error));
}

double readDoubleV(Validator v) {
  double ret;
  errno = readToken("%lf", &ret, v);
  return ret;
}
