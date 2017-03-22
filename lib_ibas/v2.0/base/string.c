//
// Created by Павел on 20.03.2017.
//

#include "string.h"

String_t __String_t_create(size_t size) {
  return Vector.create(size, sizeof(char));
}

//CLion shows an error here, but actually there's no error TODO suppress the error
genericListMethodsImplStripped(Vector, String_t, str, char)

String_t __String_t_toString(String_t str) {
  return str;
}

//TODO implement
void __String_concat(String_t str1, String_t str2) {

}

void __String_appendCStr(String_t str1, CString str2) {

}

void __String_prependCStr(String_t str2, CString str1) {

}

String_t_ String = {
  genericListMethodsList(String_t),
  __String_concat,
  __String_appendCStr,
  __String_prependCStr
};
