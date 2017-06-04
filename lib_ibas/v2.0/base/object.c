//
// Created by Павел on 14.05.2017.
//

#include "object.h"
#include "base.h"

static void destroy(Object_t obj) {
  if (obj) Object.getClass(obj)->destroy(obj);
}

static String_t toString(Object_t obj) {
  return Object.getClass(obj)->toString(obj);
}

static int compare(Object_t obj1, Object_t obj2) {
  return Object.getClass(obj1)->compare(obj1, obj2);
}

static void serialize(Object_t obj, Writer_t writer) {
  Object.getClass(obj)->serialize(obj, writer);
}

static Object_t deserialize(Object_t obj, Scanner_t scanner) {
  return Object.getClass(obj)->deserialize(obj, scanner);
}

static Class_t getClass(Object_t obj) {
  return *(Class_t *) obj;
}

$defineNamespace(Object) {
    (Class_t) &Object.destroy,
    destroy,
    toString,
    compare,
    serialize,
    deserialize,
    getClass
};
