//
// Created by Павел on 14.05.2017.
//

#include "list.h"
#include "../base/base.h"

static String_t toString(Object_t list, List_i class, ToString_t stringifier) {
  String_t str = NULL;

  //@formatter:off
  $with(str) {
    str = CString_w->toString("[");
  } $use {
    Object_t it = class->begin(list);
    if (it != class->end(list)) {
      while (true) {
        Object_t elem = class->iterGet(list, it);

        $withAuto(String_t, str1) {
          str1 = stringifier(elem);
        } $use{
          String.addAll(str, str1);
        };

        it = class->iterNext(list, it);
        if (it == class->end(list)) break;

        String.appendCStr(str, ", ");
      }
    }

    String.add(str, ']');
    //TODO trim to size
  };
  //@formatter:on

  return str;
}

$defineNamespace(List) {
    toString
};
