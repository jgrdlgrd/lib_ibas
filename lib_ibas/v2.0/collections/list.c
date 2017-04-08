//
// Created by Павел on 07.04.2017.
//

#include "list.h"
#include "../base/string.h"

String_t __List_toString(List_t list) {
  List_i impl = Ibas.getImpl(list, "List");
  ToString_t toStringFn = impl->getToStringFn(list);

  String_t str = ToString.CStr("[");

  for (Object i = impl->begin(list); ; ) {
    String.addAll(str, toStringFn(impl->iterGet(list, i)));

    i = impl->iterNext(list, i);
    if (i == impl->end(list)) break;

    String.appendCStr(str, ", ");
  }

  String.add(str, ']');
  /*TODO trim to size*/
  return str;
}

List_c List = {
    __List_toString
};
