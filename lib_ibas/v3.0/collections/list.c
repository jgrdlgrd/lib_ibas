//
// Created by Павел on 07.04.2017.
//

#include "list.h"
#include "../base/ibas.h"
#include "../base/string.h"

String_t __List_toString(List_t list, ToString_t stringifier) {
  List_i impl = Ibas.getImpl(list, "List");
  String_t str = ToString.CStr("[");

  Object_t i = impl->begin(list);
  if (i != impl->end(list))
    while (true) {
      String.addAll(str, stringifier(impl->iterGet(list, i)));

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
