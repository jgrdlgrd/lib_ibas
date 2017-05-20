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

static Class_t getClass(Object_t obj) {
  return *(Class_t *) obj;
}

$defineNamespace(Object) {
    (Class_t) &Object.destroy,
    destroy,
    toString,
    compare,
    getClass
};
